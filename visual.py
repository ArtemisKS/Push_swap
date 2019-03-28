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
oper_a = {'pa' : 'push a', 'sa' : 'swap a', 'ra' : 'rotate a', 'rra' : 'reverse rotate a', 'ra' : 'rotate a', 'rra' : 'reverse rotate a', 'sa' : 'swap a'}
oper_b = {'pb' : 'push b', 'sb' : 'swap b', 'rb' : 'rotate b', 'rrb' : 'reverse rotate b', 'rb' : 'rotate b', 'rrb' : 'reverse rotate b', 'sb' : 'swap b'}
av_len = len(sys.argv)
SCR_WIDTH = 1200
SCR_HEIGHT = 1200
Y_INDENT = 100
MAX_ELEM_WIDTH = SCR_WIDTH / 2 - 100
MAX_STACK_HEIGHT = SCR_HEIGHT - Y_INDENT * 2
INIT_SPACING = 5
INIT_X_A = 50
END_X_A = SCR_WIDTH / 2 - 50
INIT_X_B = SCR_WIDTH / 2 + 50
END_X_B = SCR_WIDTH - 50
LINE_WIDTH = 4
C_LINE_WIDTH = 7
DELAY = 15
ONE_LEN = 0
D_RED = gr.color_rgb(220, 20, 60)
D_BLUE = gr.color_rgb(60, 20, 220)
YELLOW = gr.color_rgb(255, 255, 0)
GREEN = gr.color_rgb(0, 255, 0)
SLOW_MODE = True
MAX_ELEM = 0
max_elem_width = 0

def error_and_quit(mes):
	print('Error:', mes)
	quit()

if av_len <= 1:
	error_and_quit('please, enter at least one parameter')

win = gr.GraphWin('PS visualization', SCR_WIDTH, SCR_HEIGHT)
win.setBackground(gr.color_rgb(0, 0, 0))

def draw_line(x1, y1, x2, y2, color, width):
	line = gr.Line(gr.Point(x1, y1), gr.Point(x2, y2))
	line.setOutline(color)
	line.setWidth(width)
	line.draw(win)
	return line

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

def calc_el_x(elem):
	line_width = ONE_LEN * elem
	indent = 0
	while indent + line_width < max_elem_width - indent:
		indent += 1
	print(f'one_len: {ONE_LEN}; elem: {elem}; indent: {indent}')
	return indent

def draw_stacks(one_len, init_y, line_width, case):
	global ONE_LEN, max_elem_width
	i = 0
	ONE_LEN = one_len
	max_elem_width = MAX_ELEM * ONE_LEN
	if case == 0 or case == 2:
		for num in stack1:
			el_x = calc_el_x(num) + INIT_X_A
			cur_y = init_y + i * INIT_SPACING
			linesA.append(draw_line(el_x, cur_y, el_x + one_len * num, cur_y, D_RED, line_width))
			i += 1
	# i = 0
	# if case == 1 or case == 2:
	# 	for num in stack2:
	# 		cur_y = init_y + i * INIT_SPACING
	# 		linesB.append(draw_line(INIT_X_B, cur_y, INIT_X_B + one_len * num, cur_y))
	# 		linesB[-1].setOutline(gr.color_rgb(255, 0, 0))
	# 		linesB[-1].draw(win)
	# 		linesB[-1].setWidth(line_width)
	# 		i += 1

def cast_to_int(elem):
	if not re.match("^[-]?[0-9]*$", elem):
		error_and_quit(f'{elem} is not an int')
	val = int(elem)
	if val > 2147483647:
		error_and_quit(f'{val} is less than min_int')
	elif val < -2147483648:
		error_and_quit(f'{val} is less than max_int')		
	return val

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

def move_up(lines):
	for line in lines:
		line.move(0, -1.0 * (INIT_SPACING))

def move_down(lines):
	for line in lines:
		line.move(0, INIT_SPACING)


def color_line(*args, color):
	for line in args:
		line.setOutline(color)

def anim_sidemove(line, it_shift, it_num):
	for _ in range(it_num):
		line.move(it_shift, 0)

def move_stack(lines1, lines2, ess):
	move_down(lines1)
	# for line in lines1:
	# 	line.move(0, (INIT_SPACING))
	# lines1 = [line.move(0, (INIT_SPACING)) for line in lines1]
	# map(lambda line: line.move(0, (INIT_SPACING)), lines1)
	line = lines2.pop(0)
	lines1.insert(0, line)
	if lines2 == linesA:
		anim_sidemove(line, int(SCR_WIDTH / 24), 12)
		# line.move(SCR_WIDTH / 2, 0)
	else:
		anim_sidemove(line, int(-(SCR_WIDTH / 24)), 12)
		# line.move(-1.0 * (SCR_WIDTH / 2), 0)
	color_line(line, color=YELLOW)
	move_up(lines2)	
	# map(lambda line: line.move(0, -1.0 * (INIT_SPACING)), lines2)
	# lines2 = [line.move(0, -1.0 * (INIT_SPACING)) for line in lines2]		
	# for line in lines2:
	# 	line.move(0, -1.0 * (INIT_SPACING))

def draw_rotate(lines, ess):
	line1 = lines.pop(0)
	len_l = len(lines)
	move_up(lines)
	# for i in range(0, len_l):
	# 	lines[i].move(0, -1.0 * INIT_SPACING)
	line1.move(0, (INIT_SPACING * (len_l)))
	color_line(lines[0], color=YELLOW)
	lines.append(line1)
	color_line(lines[-1], color=GREEN)

def draw_rev_rotate(lines, ess):
	lineE = lines.pop()
	len_l = len(lines)
	# move_down(lines)
	for i in range(len_l - 1, -1, -1):
		lines[i].move(0, INIT_SPACING)
	lineE.move(0, -1.0 * ((INIT_SPACING) * (len_l)))
	# color_line(lineE, color=GREEN)
	color_line(lines[-1], color=YELLOW)
	lines.insert(0, lineE)
	color_line(lines[0], color=GREEN)

def swap_els(lines, ess):
	color_line(lines[0], color=GREEN)
	color_line(lines[1], color=YELLOW)
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

def det_label_pos(op_label, f_size, init_x, end_x):
	label_len = int(len(op_label) * f_size / 8)
	indent = 0
	while int(init_x + indent) < int(end_x - label_len - indent):
		indent += 1
		if indent > SCR_WIDTH/2:
			error_and_quit(f'you stupid fuck!\n init_x: {init_x}, end_x: {end_x}, indent: {indent}, label_len: {label_len}')
	return init_x + indent

def set_text_attr(text, f_size):
	text.setTextColor(GREEN)
	text.setSize(f_size)
	text.draw(win)

def draw_labels(case, op_label, lab_x, op_label1, f_size, text, text1):
	# print('case, op_label, lab_x, op_label1, f_size:\n', case, op_label, lab_x, op_label1, f_size)
	if text:
		text.undraw()
	if text1:
		text1.undraw()
	if case != 2:
		text = gr.Text(gr.Point(lab_x, Y_INDENT/2 - 10), op_label)
		set_text_attr(text, f_size)
	else:
		text = gr.Text(gr.Point(lab_x, Y_INDENT/2 - 10), op_label)
		text1 = gr.Text(gr.Point(lab_x + SCR_WIDTH/2, Y_INDENT/2 - 10), op_label1)
		set_text_attr(text, f_size)
		set_text_attr(text1, f_size)
	return text, text1

def do_animation(ess, tf):
	global SLOW_MODE
	f_size = 25
	text = None
	text1 = None
	while ops:
		op = ops.pop(0)
		if op[-1] == 'a':
			case = 0
			op_label = oper_a.get(op, 'Unexisting operation')
			lab_x = det_label_pos(op_label, f_size, 0, int(SCR_WIDTH/2 - C_LINE_WIDTH/2 - 1))
		elif op[-1] == 'b':
			case = 1
			op_label = oper_b.get(op, 'Unexisting operation')
			lab_x = det_label_pos(op_label, f_size, int(SCR_WIDTH/2 + C_LINE_WIDTH/2 + 1), SCR_WIDTH)
		else:
			case = 2
			op_label = oper_a.get(op, 'Unexisting operation')
			op_label1 = oper_b.get(op, 'Unexisting operation')
			lab_x = det_label_pos(op_label, f_size, 0, int(SCR_WIDTH/2 - C_LINE_WIDTH/2 - 1))
		index = append_op(op)
		# print(f'cur_op: {op}, case: {case}')
		if LINE_WIDTH > 0:
			text, text1 = draw_labels(case, op_label, lab_x, op_label1 if case == 2 else None, f_size, text, text1)
		redraw_all(case, index, ess)
		# print(f'linesA: {linesA};\n\n linesB: {linesB}')
		# draw_stacks(ess['one_len'], ess['init_y'], ess['line_width'], case, index)
		if not win.checkMouse() and SLOW_MODE:
			time.sleep(tf)
		key = win.checkKey()
		# print(f'win.checkKey(): {key}')
		if key == 'q':
			SLOW_MODE = False
		elif key == 's':
			SLOW_MODE = True
		elif key == 'p':
			while(win.checkKey() != 'p'):
				pass
		if op == 'pa':
			color_line(linesA[0], color=D_RED)
		elif op == 'pb':
			color_line(linesB[0], color=D_BLUE)
		elif op == 'sa':
			color_line(linesA[0], linesA[1], color=D_RED)
		elif op == 'sb':
			color_line(linesB[0], linesB[1], color=D_BLUE)
		elif op == 'rra' or op == 'ra':
			color_line(linesA[0], linesA[-1], color=D_RED)
		elif op == 'rb' or op == 'rrb':
			color_line(linesB[0], linesB[-1], color=D_BLUE)
		elif op == 'rrr' or op == 'rr':
			color_line(linesA[0], linesA[-1], color=D_RED)
			color_line(linesB[0], linesB[-1], color=D_BLUE)
		elif op == 'ss':
			color_line(linesA[0], linesA[1], color=D_RED)
			color_line(linesB[0], linesB[1], color=D_BLUE)
	return text, text1

def move_elem_pyramid(line, max_el_width):
	# line_width = line.p2.x - line.p1.x
	# indent = 0
	# while indent + line_width < max_el_width - indent:
	# 	indent += 1
	# print(f'line: {line}; indent: {indent}')
	# line.move(indent + (SCR_WIDTH/2 - max_el_width/2 - ONE_LEN), 0)
	line.move(SCR_WIDTH/2 - max_el_width/2 - ONE_LEN * 2, 0)

def make_pyramid(max_el_width):
	[move_elem_pyramid(line, max_el_width) for line in linesA]

def animate(ess, oplen):
	# tf = 1/(ess['init_st_len'] * DELAY)
	tf = 1/(oplen / DELAY)
	draw_stacks(ess['one_len'], ess['init_y'], ess['line_width'], 2)
	text = gr.Text(gr.Point(win.getWidth()/2 - 30, SCR_HEIGHT - Y_INDENT), 'Click on the screen to start')
	text.setTextColor(YELLOW)
	text.setSize(15)
	text.setStyle('italic')
	text.draw(win)
	win.getMouse()
	text.undraw()
	line = draw_line(SCR_WIDTH / 2, Y_INDENT, SCR_WIDTH / 2, SCR_HEIGHT - Y_INDENT, gr.color_rgb(64, 224, 208), C_LINE_WIDTH)
	text, text1 = do_animation(ess, tf)
	if text:
		text.undraw()
	if text1:
		text1.undraw()
	line.undraw()
	max_elem_width = ONE_LEN * stack1[-1]
	make_pyramid(max_elem_width)
		# print_stacks(stack1, stack2)
	# redraw_all(2, 0, ess)
	# draw_stacks(ess['one_len'], ess['init_y'], ess['line_width'], 0)

def extra_validate(ops):
	for op in ops:
		if op not in operations:
			error_and_quit(f'wrong operation: {op}')
	set_stack = set(stack1)
	if len(stack1) != len(set_stack):
		print(f'stack1: {stack1}, set_stack: {set_stack}')
		error_and_quit(f'found duplicates in your initial array')

def process_for_pos_num(st_stack, in_len):
	print(f'stack1: {stack1}')
	# bn_scale(st_stack, in_len)
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
	if not ops:
		error_and_quit('no operations, some error occured')
	op_len = len(ops)
	extra_validate(ops)
	animate(ess_vars, op_len)
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

# def convert(elem, val):
# 	return float(elem/val)

# def convert_to_i(fl_arr, mult):
# 	pass

# def filterLessAvVal(num, av_val):
# 	if num < av_val:
# 		return num
# 	return None

# def filterMoreAvVal(num, av_val):
# 	if num > av_val:
# 		return num
# 	return None

# def filterNoneVals(val):
# 	return val != None

# def convert(mtav_stack, last_ltav_el, av_val):
# 	if av_val / last_ltav_el > 50:
# 		av_val = last_ltav_el + 1
# 	i = 1	
# 	for num in mtav_stack:
# 		num = av_val + i
# 		i += 2

# def bn_scale(st_stack, in_len):
# 	global stack1
# 	min_val = st_stack[0]
# 	av_val = sum(st_stack)/in_len
# 	# print(f'av_val: {av_val}')
# 	fl_arr = []
# 	# if av_val > min_val * in_len:
# 	# 	fl_arr = [convert(num, av_val) for num in stack1]
# 	# 	print(f'fl_arr: {fl_arr}')
# 	# 	mval = min(fl_arr)
# 	# 	print(f'mval: {mval}')
# 	# 	mult = float(1.01)/mval
# 	# 	print(f'mult: {mult}')
# 	# 	del stack1
# 	# 	stack1 = convert_to_i(fl_arr, mult)
# 	add_stack = [filterLessAvVal(num, av_val) for num in stack1]
# 	ltav_stack = filter(filterNoneVals, add_stack)
# 	add_stack = [filterMoreAvVal(num, av_val) for num in stack1]
# 	mtav_stack = filter(filterNoneVals, add_stack)
# 	mtav_stack = convert(mtav_stack, ltav_stack[-1], av_val)
# 	# print(f'stack1: {stack1}')

def make_label(x, y, text, color, size, style='italic'):
	label = gr.Text(gr.Point(x, y), text)
	label.setTextColor(color)
	label.setSize(size)
	label.setStyle(style)
	return label

def main():
	global stack1, stack2, MAX_ELEM
	op_len = 0
	stack = parse_params()
	# print_stacks(stack, stack2)
	stack1 = list(map(cast_to_int, stack))
	in_len = len(stack1)
	st_stack = sorted(stack1)
	MAX_ELEM = st_stack[-1]
	if any(num <= 0 for num in stack1):
		globalize(st_stack)
		st_stack = sorted(stack1)
		op_len = process_for_pos_num(st_stack, in_len)
	else:
		op_len = process_for_pos_num(st_stack, in_len)
	if stack1 == st_stack:
		text = make_label(win.getWidth()/2 - 30, win.getHeight()/2 - 275, f'Array of {in_len} elems is sorted!', GREEN, 20)
		text.draw(win)
		draw_line(win.getWidth()/2 - 155, win.getHeight()/2 - 260, win.getWidth()/2 + 90, win.getHeight()/2 - 260, gr.color_rgb(64, 224, 208), 0.4)
		text = make_label(win.getWidth()/2 - 30, win.getHeight()/2 - 248, f'Number of operations: {op_len}', GREEN, 20)
		text.draw(win)
		text = make_label(win.getWidth()/2 - 30, SCR_HEIGHT - Y_INDENT, 'Click on the screen to quit', YELLOW, 15)
		text.draw(win)
	win.getMouse()
	win.close()

main()