def problem1():
    file = open("input.txt", "r")
    fileLines = file.readlines()
    rockLayout = list(map(lambda line: list(line.strip()), fileLines))
    for rowIndex in range(len(rockLayout)):
        for rockIndex in range(len(rockLayout[rowIndex])):
            if rockLayout[rowIndex][rockIndex] == "O":
                newIndex = rowIndex - 1
                while newIndex >= 0:
                    if rockLayout[newIndex][rockIndex] == ".":
                        rockLayout[newIndex][rockIndex] = "O"
                        rockLayout[newIndex+1][rockIndex] = "."
                        newIndex -= 1
                    else:
                        break
    value = len(rockLayout)
    result = 0
    for row in rockLayout:
        for rock in row:
            if rock == "O":
                result += value
        value -= 1
    print("Part 1 Result: ", result)


if __name__ == "__main__":
    problem1()
