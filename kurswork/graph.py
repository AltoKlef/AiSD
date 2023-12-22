from collections import deque


class MyGraph:
    def __init__(self, vertices, matrix):
        self.vertices = vertices
        self.matrix = matrix
        self.ufc = {}


    def convert_to_edges_list(self): #я использовал именно этот способ хранения представления графа для работы алгоритма крускала
        edges = []

        for i in range(len(self.vertices)):
            for j in range(i + 1, len(self.vertices)):
                weight = self.matrix[i][j]
                if weight > 0:
                    edges.append((self.vertices[i], self.vertices[j], weight))

        return edges

    def convert_to_adjacency_list(self):
        adjacency_list = {}

        for i in range(len(self.vertices)):
            vertex = self.vertices[i]
            neighbors = []

            for j in range(len(self.vertices)):
                if self.matrix[i][j] > 0:
                    neighbors.append((self.vertices[j], self.matrix[i][j]))

            adjacency_list[vertex] = neighbors

        return adjacency_list

    def convert_to_incidence_matrix(self):
        num_vertices = len(self.matrix)
        num_edges = sum(sum(1 for weight in row if weight > 0) for row in self.matrix) // 2

        incidence_matrix = [[0] * num_edges for _ in range(num_vertices)]

        edge_index = 0
        for i in range(num_vertices):
            for j in range(i + 1, num_vertices):
                if self.matrix[i][j] > 0:
                    incidence_matrix[i][edge_index] = self.matrix[i][j]
                    incidence_matrix[j][edge_index] = -self.matrix[i][j]
                    edge_index += 1

        return incidence_matrix



    def insertion_sort(self, edges): #сортировка вставками ребер из списка
        for i in range(1, len(edges)):
            current_edge = edges[i]
            j = i - 1
            while j >= 0 and current_edge[2] < edges[j][2]:
                edges[j + 1] = edges[j]
                j -= 1
            edges[j + 1] = current_edge

        return edges
    #длаее три функции отвечающие за множество непересекающихся подмножеств
    def init_ufc(self):
        for vertex in self.vertices:
            self.ufc[vertex] = vertex

    def find(self, vertex):
        if self.ufc[vertex] != vertex:
            self.ufc[vertex] = self.find(self.ufc[vertex])
        return self.ufc[vertex]

    def union(self, vertex1, vertex2):
        x1 = self.find(vertex1)
        x2 = self.find(vertex2)
        self.ufc[x1] = x2

    def kruskal(self):
        edges = self.convert_to_edges_list() #получаем список ребер
        sorted_edges = self.insertion_sort(edges)  #сортируем список ребер
        result = []                      #создаем пустой список для ответа

        self.init_ufc()                     #инициализируем множество
        full_weight = 0

        for edge in sorted_edges:
            vertex1, vertex2, weight = edge
            if self.find(vertex1) != self.find(vertex2):   #вся лаба?
                result.append(edge)
                full_weight += weight
                self.union(vertex1, vertex2)

        for edge in sorted(result):  #вывод
            print(f"{edge[0]} {edge[1]}")

        print(full_weight)

    def dfs(self, start, visited=None): #обход в глубину
        adjacency_list = self.convert_to_adjacency_list()
        if visited is None:
            visited = set()

        print(start)
        visited.add(start)

        for neighbor, _ in adjacency_list[start]:
            if neighbor not in visited:
                self.dfs(neighbor, visited)

    def bfs(self, start):  #обход в ширину
        adjacency_list = self.convert_to_adjacency_list()
        visited = set()
        queue = deque([start]) #тут используется дека (двусторонняяя очередь)
        visited.add(start)

        while queue:
            current = queue.popleft()
            print(current)

            for neighbor, _ in adjacency_list[current]:
                if neighbor not in visited:
                    queue.append(neighbor)
                    visited.add(neighbor)
