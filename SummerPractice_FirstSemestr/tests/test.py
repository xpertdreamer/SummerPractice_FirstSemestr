with open("input3.txt", "w") as f:
    f.write("1000\n")
    f.write(" ".join(str(i) for i in range(1000, 0, -1)))
