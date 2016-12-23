def priority(x):
    if x == '+': return 1
    if x == '-': return 1
    if x == '*': return 2
    if x == '/': return 3
    if x == '^': return 4
    if x == '(': return -1

infix = '1 - 2 ^ 3 ^ 3 - ( 4 + 5 * 6 ) * 7'
postfix = []
stack = []
for item in infix.split():
	if item.isdigit():
		postfix.append(item)
	else:
		if item == '(':
			stack.append(item)
		
		elif item == '^':
			stack.append(item)

		elif item == ')':
			while 1:
				t = stack.pop()
				if t == '(':
					break
				postfix.append(t)
		else:
			while stack:
				t = stack.pop()
				if priority(item) > priority(t):
					stack.append(t)
					break
				postfix.append(t)
			stack.append(item)

while stack:
	postfix.append(stack.pop())

#calculate

res = []
for item in postfix:
	if item.isdigit():
		res.append(int(item))
	else:
		if item == '+':
			t2 = res.pop()
			t1 = res.pop()
			res.append(t1+t2)
		elif item == '-':
			t2 = res.pop()
			t1 = res.pop()
			res.append(t1-t2)
		elif item == '*':
			t2 = res.pop()
			t1 = res.pop()
			res.append(t1*t2)
		elif item == '/':
			t2 = res.pop()
			t1 = res.pop()
			res.append(t1/t2)
		elif item == '^':
			t2 = res.pop()
			t1 = res.pop()
			res.append(t1**t2)
		else:
			continue

print infix + ' =', res.pop()