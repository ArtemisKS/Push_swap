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
SCR_HEIGHT = 1200
Y_INDENT = 100
MAX_ELEM_WIDTH = SCR_WIDTH / 2 - 100
MAX_STACK_HEIGHT = SCR_HEIGHT - Y_INDENT * 2
INIT_SPACING = 5
INIT_X_A = 50
END_X_A = SCR_WIDTH / 2 - 50
INIT_X_B = SCR_WIDTH / 2 + 50
END_X_B = SCR_WIDTH - 50
LINE_WIDTH = 3
FREQUENCY = 1

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

def calc_init_y(st_len):
	init_y = 0
	if st_len * INIT_SPACING > MAX_STACK_HEIGHT:
		# calc_spacing()
		return init_y, 0
	else:
		return SCR_HEIGHT / 2 - ((st_len / 2) * INIT_SPACING), LINE_WIDTH

def draw_stacks(one_len, init_y, line_width, case):
	i = 0
	if case == 0 or case == 2:
		for num in stack1:
			cur_y = init_y + i * INIT_SPACING
			linesA.append(draw_line(INIT_X_A, cur_y, INIT_X_A + one_len * num, cur_y))
			linesA[-1].setOutline(gr.color_rgb(255, 0, 0))
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
	if not re.match("^[0-9]*$", elem):
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
	if op not in operations:
		error_and_quit(f'wrong operation')
	index = operations.index(op)
	op_funcs = [pb, pa, sb, sa, ra, rb, rra, rrb, rr, rrr, ss]
	op_funcs[index]()
	return index

def move_stack(lines1, lines2, ess):
	for line in lines1:
		line.move(0, 1.0 * (INIT_SPACING))
	line = lines2.pop(0)
	lines1.insert(0, line)
	if lines2 == linesA:
		line.move(1.0 * SCR_WIDTH / 2, 0)
	else:
		line.move(-1.0 * (SCR_WIDTH / 2), 0)
	for line in lines2:
		line.move(0, -1.0 * (INIT_SPACING))

def draw_rotate(lines, ess):
	line1 = lines.pop(0)
	len_l = len(lines)
	for i in range(0, len_l):
		lines[i].move(0, -1.0 * INIT_SPACING)
	line1.move(0, 1.0 * (INIT_SPACING * (len_l)))
	lines.append(line1)

def draw_rev_rotate(lines, ess):
	lineE = lines.pop()
	len_l = len(lines)
	for i in range(len_l - 1, -1, -1):
		lines[i].move(0, 1.0 * INIT_SPACING)
	lineE.move(0, -1.0 * ((INIT_SPACING) * (len_l)))
	lines.insert(0, lineE)

def swap_els(lines, ess):
	lines[0].move(0, 1.0 * INIT_SPACING)
	lines[1].move(0, -1.0 * INIT_SPACING)
	lines[0], lines[1] = lines[1], lines[0]

def redraw_all(case, index, ess):
	if case == 0 or case == 2:
		if index < 2:
			move_stack(linesA, linesB, ess)
		elif index < 4 or index == 10:
			swap_els(linesA, ess)
		elif index < 6 or index == 8:
			draw_rotate(linesA, ess)
		elif index < 8 or index == 9:
			draw_rev_rotate(linesA, ess)
	if case == 1 or case == 2:
		if index < 2:
			move_stack(linesB, linesA, ess)
		elif index < 4 or index == 10:
			swap_els(linesB, ess)
		elif index < 6 or index == 8:
			draw_rotate(linesB, ess)
		elif index < 8 or index == 9:
			draw_rev_rotate(linesB, ess)

def do_animation(ess, tf, i):
	# time.sleep(1)
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
	time.sleep(tf)

def start_animation(ess):
	i = 0
	tf = 1/(ess['init_st_len'] * FREQUENCY)
	# tf = 1/(ess['init_st_len'])
	draw_stacks(ess['one_len'], ess['init_y'], ess['line_width'], 2)
	while ops:
		do_animation(ess, tf, i)
		# print_stacks(stack1, stack2)
		i += 1
	# redraw_all(2, 0, ess)
	# draw_stacks(ess['one_len'], ess['init_y'], ess['line_width'], 0)

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
	print('ops: ', ops)
	start_animation(ess_vars)

def main():
	global stack1, stack2
	stack = parse_params()
	# print_stacks(stack, stack2)
	stack1 = list(map(cast_to_int, stack))
	line = draw_line(SCR_WIDTH / 2, Y_INDENT, SCR_WIDTH / 2, SCR_HEIGHT - Y_INDENT)
	line.setOutline(gr.color_rgb(0, 255, 255))
	line.setWidth(7)
	line.draw(win)
	if any(num <= 0 for num in stack1):
		pass
		# process_for_neg_num
		# sorted_stack = sorted(stack1)...
	else:
		process_for_pos_num()

	win.getMouse()
	win.close()

main()