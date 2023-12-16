def problem1():
    file = open("input.txt")
    data = file.readlines()
    raceData = []
    result = 1
    for race in data:
        raceData.append(race.strip().split())
    times = raceData[0][1::]
    distance = raceData[1][1::]
    raceNum = 0
    for raceTime in times:
        victories = 0
        for secondsHeld in range(0, int(raceTime)):
            if secondsHeld * (int(raceTime) - secondsHeld) > int(distance[raceNum]):
                victories += 1
        result *= victories
        raceNum += 1
    print("Part 1 Result:", result)


def problem2():
    file = open("input.txt")
    data = file.readlines()
    raceData = []
    for race in data:
        raceData.append(race.strip().split())
    times = (raceData[0][1::])
    distance = (raceData[1][1::])
    trueTime = ""
    trueDistance = ""
    for race in range(0,len(times)):
        trueTime += times[race]
        trueDistance += distance[race]
    victories = 0
    trueTime = int(trueTime)
    trueDistance = int(trueDistance)
    for secondsHeld in range(0, trueTime):
        if secondsHeld * (trueTime - secondsHeld) > trueDistance:
            victories += 1
    result = victories
    print("Part 2 Result: ", result)


if __name__ == "__main__":
    problem1()
    problem2()
