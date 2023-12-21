from graph import MyGraph


def read_graph(filepath):  # парсинг
    with open(filepath, 'r') as file:
        lines = file.readlines()
    vertices = lines[0].split()
    vertices = [vertex.strip() for vertex in vertices]
    matrix = []
    for line in lines[1:]: #сдвиг на 1 ибо первая строчка -  вершины
        row = [int(x) for x in line.split()]
        matrix.append(row)

    return MyGraph(vertices, matrix)


"""
A B C D E
0 3 6 8 2
3 0 4 5 9
6 4 0 4 2
8 5 4 0 6
2 9 2 6 0
"""

if __name__ == '__main__':
    path = "test.txt"
    graph = read_graph(path)
    print("Матрица смежности:", graph.matrix)
    print("Список ребёр:  ", graph.convert_to_edges_list())
    print("Список смежности:", graph.convert_to_adjacency_list())
    print("Матрица инциндентности", graph.convert_to_incidence_matrix())
    print("результат работы алгоритма крускала: ")
    graph.kruskal()

    print("Обход в ширину:")
    graph.bfs('A')
    print("Обход в глубину:")
    graph.dfs('A')

