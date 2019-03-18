import graphics as gr
import os
import re
import sys
import time
import select

stack1 = []
stack2 = []
ops = []
linesA = []
linesB = []
operations = ['pb', 'pa', 'sb', 'sa', 'ra', 'rb', 'rra', 'rrb', 'rr', 'rrr', 'ss']
av_len = len(sys.argv)
SCR_WIDTH = 1200
SCR_HEIGHT = 1311
Y_INDENT = 100
MAX_ELEM_WIDTH = SCR_WIDTH / 2 - 100
MAX_STACK_HEIGHT = SCR_HEIGHT - Y_INDENT * 2
INIT_SPACING = 5
INIT_X_A = 50
END_X_A = SCR_WIDTH / 2 - 50
INIT_X_B = SCR_WIDTH / 2 + 50
END_X_B = SCR_WIDTH - 50
LINE_WIDTH = 4
FREQUENCY = 2
MOD = 0 # if you want quick but not beautiful mode, value should be not 0 else 0
shifts = [[0, 0], [0, 0], [0, 0]]

def error_and_quit(mes):
	print('Error:', mes)
	quit()

if av_len <= 1:
	error_and_quit('please, enter at least one parameter')

win = gr.GraphWin('PS visualization', SCR_WIDTH, SCR_HEIGHT)
win.setBackground(gr.color_rgb(0, 0, 0))

def draw_line(x1, y1, x2, y2):
	return gr.Line(gr.Point(x1, y1), gr.Point(x2, y2))

def store_numbers(argv, stack):
	for num in argv:
		stack.append(num)

def parse_params():
	stack = []
	if av_len == 0:
		error_and_quit(f'please, enter your array as a parameter')
	elif av_len == 1:
		stack = sys.argv[1].split(' ')
	else:
		store_numbers(sys.argv[1:], stack)
	return stack

def calc_one_len(max_elem, min_elem):
	diff = max_elem - min_elem + 1
	one_len = MAX_ELEM_WIDTH / diff
	return one_len

def calc_spacing(stlen):
	global INIT_SPACING, LINE_WIDTH
	while stlen * INIT_SPACING > MAX_STACK_HEIGHT:
		if INIT_SPACING == 1:
			break
		INIT_SPACING -= 1
		LINE_WIDTH -= 1 if INIT_SPACING - LINE_WIDTH < 1 else 0
	return INIT_SPACING, LINE_WIDTH

def	calc_init_y_pos(stlen, init_y):
	i = 0
	while stlen * INIT_SPACING > MAX_STACK_HEIGHT + (Y_INDENT - init_y) * 2 + i:
		if init_y < 10:
			error_and_quit(f'{stlen} operations is too many. Please, enlarge the screen height, which is currently {SCR_HEIGHT} (it must be more than {stlen + 10})')
		init_y -= i
		i += 1
	print(f'init_y: {init_y}, st_len * INIT_SPACING: {stlen * INIT_SPACING}, MAX_STACK_HEIGHT: {MAX_STACK_HEIGHT}, LINE_WIDTH: {LINE_WIDTH}, INIT_SPACING: {INIT_SPACING}')
	return init_y

def calc_init_y(st_len):
	global INIT_SPACING, LINE_WIDTH
	if INIT_SPACING - LINE_WIDTH < 1:
		INIT_SPACING = LINE_WIDTH + 1
	init_y = SCR_HEIGHT / 2 - ((st_len / 2) * INIT_SPACING)
	if st_len * INIT_SPACING > MAX_STACK_HEIGHT:
		INIT_SPACING, LINE_WIDTH = calc_spacing(st_len)
		init_y = SCR_HEIGHT / 2 - ((st_len / 2) * INIT_SPACING)
		if init_y < 0:
			error_and_quit(f'{st_len} operations is too many. Please, enlarge the screen height, which is currently {SCR_HEIGHT} (it must be more than {st_len + 10})')
		print(f'init_y: {init_y}, st_len * INIT_SPACING: {st_len * INIT_SPACING}, MAX_STACK_HEIGHT: {MAX_STACK_HEIGHT}, LINE_WIDTH: {LINE_WIDTH}, INIT_SPACING: {INIT_SPACING}')
		if st_len * INIT_SPACING + Y_INDENT - init_y <= MAX_STACK_HEIGHT:
			return init_y, LINE_WIDTH
		else:
			return calc_init_y_pos(st_len, init_y), LINE_WIDTH
	else:
		return init_y, LINE_WIDTH

def draw_stacks(one_len, init_y, line_width, case):
	i = 0
	if case == 0 or case == 2:
		for num in stack1:
			cur_y = init_y + i * INIT_SPACING
			linesA.append(draw_line(INIT_X_A, cur_y, INIT_X_A + one_len * num, cur_y))
			linesA[-1].setOutline(gr.color_rgb(220, 20, 60))
			linesA[-1].draw(win)
			linesA[-1].setWidth(line_width)
			i += 1
	i = 0
	if case == 1 or case == 2:
		for num in stack2:
			cur_y = init_y + i * INIT_SPACING
			linesB.append(draw_line(INIT_X_B, cur_y, INIT_X_B + one_len * num, cur_y))
			linesB[-1].setOutline(gr.color_rgb(255, 0, 0))
			linesB[-1].draw(win)
			linesB[-1].setWidth(line_width)
			i += 1

def cast_to_int(elem):
	if not re.match("^[-]?[0-9]*$", elem):
		error_and_quit(f'{elem} is not an int')
	return int(elem)

def print_stacks(stack1, stack2):
	print(f'Stack A:\n {stack1}')
	print(f'Stack B:\n {stack2}')

def pb():
	stack2.insert(0, stack1.pop(0))

def pa():
	stack1.insert(0, stack2.pop(0))

def sb():
	stack2[0], stack2[1] = stack2[1], stack2[0]

def sa():
	stack1[0], stack1[1] = stack1[1], stack1[0]

def ra():
	stack1.append(stack1.pop(0))

def rra():
	stack1.insert(0, stack1.pop())

def rrb():
	stack2.insert(0, stack2.pop())

def rb():
	stack2.append(stack2.pop(0))

def rr():
	ra()
	rb()

def rrr():
	rra()
	rrb()

def ss():
	sa()
	sb()

def append_op(op):
	index = operations.index(op)
	op_funcs = [pb, pa, sb, sa, ra, rb, rra, rrb, rr, rrr, ss]
	op_funcs[index]()
	return index

def move_stack(lines1, lines2, ess):
	for line in lines1:
		line.move(0, (INIT_SPACING))
	line = lines2.pop(0)
	lines1.insert(0, line)
	if lines2 == linesA:
		line.move(SCR_WIDTH / 2, 0)
	else:
		line.move(-1.0 * (SCR_WIDTH / 2), 0)
	if not MOD:
		for line in lines2:
			line.move(0, -1.0 * (INIT_SPACING))
	else:
		if lines2 == linesA:
			shifts[0][0] -= 1
		else: 
			shifts[0][1] -= 1

def draw_rotate(lines, ess):
	line1 = lines.pop(0)
	len_l = len(lines)
	if not MOD:
		for i in range(0, len_l):
			lines[i].move(0, -1.0 * INIT_SPACING)
	if not MOD:
		line1.move(0, (INIT_SPACING * (len_l)))
	else:
		line1.move(0, (INIT_SPACING * (len_l + 1)))
		if lines == linesA:
			shifts[1][0] -= 1
		else: 
			shifts[1][1] -= 1
	lines.append(line1)

def draw_rev_rotate(lines, ess):
	lineE = lines.pop()
	len_l = len(lines)
	if not MOD:
		for i in range(len_l - 1, -1, -1):
			lines[i].move(0, INIT_SPACING)
	if not MOD:
		lineE.move(0, -1.0 * ((INIT_SPACING) * (len_l)))
	else:
		lineE.move(0, -1.0 * ((INIT_SPACING) * (len_l + 1)))
		if lines == linesA:
			shifts[2][0] += 1
		else: 
			shifts[2][1] += 1		
	lines.insert(0, lineE)

def swap_els(lines, ess):
	lines[0].move(0, INIT_SPACING)
	lines[1].move(0, -1.0 * INIT_SPACING)
	lines[0], lines[1] = lines[1], lines[0]

draw_funcs_lst = [None, None, swap_els, swap_els, draw_rotate, draw_rotate, draw_rev_rotate, draw_rev_rotate, draw_rotate, draw_rev_rotate, swap_els]

def case_both(index, ess):
	if index < 2:
		move_stack(linesA, linesB, ess)
		move_stack(linesB, linesA, ess)
	else:
		draw_funcs_lst[index](linesA, ess)
		draw_funcs_lst[index](linesB, ess)

def case_left_stack(index, ess):
	if index < 2:
		move_stack(linesA, linesB, ess)
	else:
		draw_funcs_lst[index](linesA, ess)

def case_right_stack(index, ess):
	if index < 2:
		move_stack(linesB, linesA, ess)
	else:
		draw_funcs_lst[index](linesB, ess)

def redraw_all(case, index, ess):
	if case == 2:
		case_both(index, ess)
		return
	if case == 0:
		case_left_stack(index, ess)
		return
	if case == 1:
		case_right_stack(index, ess)

def do_animation(ess, tf):
	# time.sleep(1)
	init_len = len(stack1)
	while True:
		if not ops:
			return
		op = ops.pop(0)
		if op[-1] == 'a':
			case = 0
		elif op[-1] == 'b':
			case = 1
		else:
			case = 2
		index = append_op(op)
		# print(f'cur_op: {op}, case: {case}')
		redraw_all(case, index, ess)
		# print(f'linesA: {linesA};\n\n linesB: {linesB}')
		# draw_stacks(ess['one_len'], ess['init_y'], ess['line_width'], case, index)	
		if init_len < 30:
			time.sleep(tf)

def start_animation(ess, oplen):
	# tf = 1/(ess['init_st_len'] * FREQUENCY)
	tf = 1/(oplen / FREQUENCY)
	draw_stacks(ess['one_len'], ess['init_y'], ess['line_width'], 2)
	win.getMouse()
	do_animation(ess, tf)
		# print_stacks(stack1, stack2)
	# redraw_all(2, 0, ess)
	# draw_stacks(ess['one_len'], ess['init_y'], ess['line_width'], 0)

def extra_validate(ops):
	for op in ops:
		if op not in operations:
			error_and_quit(f'wrong operation: {op}')
	set_stack = set(stack1)
	if len(stack1) != len(set_stack):
		error_and_quit(f'found duplicates in your initial array')

def process_for_pos_num():
	init_st_len = len(stack1)
	# print_stacks(stack1, stack2)
	max_elem = max(stack1)
	min_elem = min(stack1)
	one_len = calc_one_len(max_elem, min_elem)
	init_y, line_width = calc_init_y(init_st_len)
	ess_vars = {'one_len' : one_len, 'init_y' : init_y, 'line_width' : line_width, 'init_st_len' : init_st_len, 'max_elem' : max_elem, 'min_elem' : min_elem}
	if not select.select([sys.stdin,],[],[],0.0)[0]:
		error_and_quit('no operations in standard input')
	for line in sys.stdin:
		ops.append(line[:-1])
	# print('ops: ', ops)
	op_len = len(ops)
	extra_validate(ops)
	start_animation(ess_vars, op_len)
	return op_len

def increment(elem, val):
	res = elem + val
	return res

def globalize(sorted_stack):
	global stack1
	val = sorted_stack[0]
	if val < 0:
		val = val * -1 + 1
		arr = [increment(num, val) for num in stack1]
		del stack1
		stack1 = arr
	else:
		val = 1
		arr = [increment(num, val) for num in stack1]
		del stack1
		stack1 = arr

# def bn_equalize(st_stack):
# 	min_val = st_stack[0], max_val = st_stack[-1]
# 	pass

def main():
	global stack1, stack2
	op_len = 0
	stack = parse_params()
	# print_stacks(stack, stack2)
	stack1 = list(map(cast_to_int, stack))
	in_len = len(stack1)
	line = draw_line(SCR_WIDTH / 2, Y_INDENT, SCR_WIDTH / 2, SCR_HEIGHT - Y_INDENT)
	line.setOutline(gr.color_rgb(64, 224, 208))
	line.setWidth(7)
	line.draw(win)
	st_stack = sorted(stack1)
	# bn_equalize(st_stack)
	if any(num <= 0 for num in stack1):
		globalize(st_stack)
		op_len = process_for_pos_num()
	else:
		op_len = process_for_pos_num()
	if stack1 == st_stack:
		line.undraw()
		text = gr.Text(gr.Point(win.getWidth()/2 - 30, win.getHeight()/2 - 75), f'Array of {in_len} elems is sorted!')
		text.setOutline(gr.color_rgb(0, 127, 255))
		text.setTextColor(gr.color_rgb(0, 255, 0))
		text.setSize(20)
		text.draw(win)
		line = gr.Line(gr.Point(win.getWidth()/2 - 155, win.getHeight()/2 - 60), gr.Point(win.getWidth()/2 + 90, win.getHeight()/2 - 60))
		line.setOutline(gr.color_rgb(64, 224, 208))
		line.setWidth(0.5)
		line.draw(win)
		text = gr.Text(gr.Point(win.getWidth()/2 - 30, win.getHeight()/2 - 48), f'Number of operations: {op_len}')
		text.setOutline(gr.color_rgb(0, 127, 255))
		text.setTextColor(gr.color_rgb(0, 255, 0))
		text.setSize(20)
		text.draw(win)
		text = gr.Text(gr.Point(win.getWidth()/2 - 30, SCR_HEIGHT - Y_INDENT), 'Click on the screen to quit')
		text.setOutline(gr.color_rgb(0, 127, 255))
		text.setTextColor(gr.color_rgb(255, 255, 0))
		text.setSize(15)
		text.setStyle('italic')
		text.draw(win)
	win.getMouse()
	win.close()

main()