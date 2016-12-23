import re
sum = 0

with open('data.txt','r') as data:
	for i in data:
		print int(re.findall(r' [1-9]', i)[0])
print sum
