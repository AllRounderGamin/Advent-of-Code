def problem1():
    file = open("input.txt")
    result = 0
    for line in file.readlines():
        result += extrapolateLineForward(line.split(" "))
    file.close()
    print("Part 1 Result: ", result)


def extrapolateLineForward(line):
    total = 0
    line = list(map(int, line))
    for num in line:
        total += num
    if total == 0:
        return 0

    newLine = []
    for i in range(0, len(line) - 1):
        newLine.append(line[i + 1] - line[i])
    return line[-1] + extrapolateLineForward(newLine)


def problem2():
    file = open("input.txt")
    result = 0
    for line in file.readlines():
        result += extrapolateLineBackward(line.split(" "))
    file.close()
    print("Part 2 Result: ", result)


def extrapolateLineBackward(line):
    total = 0
    line = list(map(int, line))
    for num in line:
        total += num
    if total == 0:
        return 0

    newLine = []
    for i in range(0, len(line) - 1):
        newLine.append(line[i + 1] - line[i])
    return line[0] - extrapolateLineBackward(newLine)



if __name__ == "__main__":
    problem1()
    problem2()
