with open("expected3.txt", "w") as f:
    f.write("Отсортированный массив:\n")
    f.write(" ".join(str(i) for i in range(1, 1001)) + " \n")
