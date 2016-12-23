from random import randint
graph = {
	'A': ['B', 'C'],
	'B': ['A', 'D', 'E'],
	'C': ['A', 'F'],
	'D': ['B'],
	'E': ['B'],
	'F': ['C']
}

def DFS(graph, start):
	visited = []
	stack = [start]
	while stack:
		vertex = stack.pop(0)
		if vertex not in visited:
			visited.append(vertex)
			for i in graph[vertex]:
				if not i in stack and (i not in visited):
					stack.append(i)
	return visited

tmp = [chr(i) for i in range(65,91)]
print DFS(graph, 'B')
print ' '.join(tmp)
	
print randint(0,9)