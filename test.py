#!/usr/bin/env python3.7

import sys
import select

operations = ['pb', 'pa', 'sb', 'sa', 'ra', 'rb', 'rra', 'rrb', 'rr', 'rrr', 'ss']
# ops = []

def error_and_quit(mes):
	print('Error:', mes)
	quit()

# if not select.select([sys.stdin,],[],[],0.0)[0]:
# 	error_and_quit('no operations in standard input')
i = 1
toExit = False
for line in sys.stdin:
	el = line[:-1]
	# ops.append(el)
	if el not in operations:
		if toExit:
			error_and_quit(f'your element #{i} \'{el}\' sucks!')
		toExit = True
	i += 1
