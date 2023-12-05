gameFile = open("input.txt")
roundNum = 0
result = 0
cubeAmounts = {"red": 12, "green": 13, "blue": 14}
while True:
    roundNum += 1
    invalidRound = False
    gameRound = gameFile.readline()
    if not gameRound:
        break
    gameRound = gameRound[gameRound.index(":")+1:]
    roundSelections = (gameRound.strip("\n").split(";"))
    for cubesSelection in roundSelections:
        cubeSelection = cubesSelection.split(",")
        for pick in cubeSelection:
            selection = pick.strip(" ").split(" ")
            if cubeAmounts[selection[1]] < int(selection[0]):
                invalidRound = True
    if not invalidRound:
        result += roundNum
gameFile.close()

print(result)

gameFile = open("input.txt")
result = 0
while True:
    minimumCubes = {"red": 0, "green": 0, "blue": 0}
    gameRound = gameFile.readline()
    if not gameRound:
        break
    gameRound = gameRound[gameRound.index(":") + 1:]
    roundSelections = (gameRound.strip("\n").split(";"))
    for cubesSelection in roundSelections:
        cubeSelection = cubesSelection.split(",")
        for pick in cubeSelection:
            selection = pick.strip(" ").split(" ")
            if minimumCubes[selection[1]] < int(selection[0]):
                minimumCubes[selection[1]] = int(selection[0])
    sums = 1
    for value in minimumCubes.values():
        print(value, sums)
        sums *= value
    result += sums

print(result)
