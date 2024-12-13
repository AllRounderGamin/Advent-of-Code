package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"slices"
	"strings"
)

type Location struct {
	Row int
	Col int
}

type CardinalLocation struct {
	Row       int
	Col       int
	Direction [2]int
}

func main() {
	file, err := os.Open("./input.txt")
	if err != nil {
		fmt.Println("Error opening File")
		return
	}
	defer file.Close()

	var room [][]string

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		splitLine := strings.Split(line, "")
		room = append(room, splitLine)
	}
	currentPos := [2]int{-1, -1}

	for i, line := range room {
		if index := slices.Index(line, "^"); index != -1 {
			currentPos[0] = i
			currentPos[1] = index
		}
	}
	if currentPos == [2]int{-1, -1} {
		fmt.Println("No starting point found")
		return
	}

	visitedLocations := part1(currentPos, room)
	delete(visitedLocations, Location{Row: currentPos[0], Col: currentPos[1]})
	part2(currentPos, room, visitedLocations)
}

func part1(currentPos [2]int, room [][]string) map[Location]bool {
	var directions = [4][2]int{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}
	currentDirection := directions[0]
	turns := 0.0
	var visitedLocations map[Location]bool = map[Location]bool{}

	for currentPos[0] >= 0 && currentPos[0] < len(room) && currentPos[1] >= 0 && currentPos[1] < len(room[currentPos[0]]) {
		position := Location{Row: currentPos[0], Col: currentPos[1]}
		if !visitedLocations[position] {
			visitedLocations[position] = true
		}
		for counter := 0; counter < 4; counter++ {
			newPos := [2]int{currentPos[0] + currentDirection[0], currentPos[1] + currentDirection[1]}
			if newPos[0] >= 0 && newPos[0] < len(room) && newPos[1] >= 0 && newPos[1] < len(room[newPos[0]]) {
				if room[newPos[0]][newPos[1]] != "#" {
					break
				}
				turns++
				currentDirection = directions[int(math.Mod(turns, 4.0))]
			}
		}
		currentPos[0] += currentDirection[0]
		currentPos[1] += currentDirection[1]
	}

	fmt.Println(len(visitedLocations))
	return visitedLocations
}

func part2(currentPos [2]int, room [][]string, visitedLocations map[Location]bool) {
	answer := 0
	newRoom := make([][]string, len(room))
	for key := range visitedLocations {
		for i := range room {
			newRoom[i] = make([]string, len(room[i]))
			copy(newRoom[i], room[i])
		}
		newRoom[key.Row][key.Col] = "#"
		if part2Traverse(currentPos, newRoom) {
			answer++
		}
	}
	fmt.Println(answer)
}

func part2Traverse(currentPos [2]int, room [][]string) bool {
	var directions = [4][2]int{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}
	currentDirection := directions[0]
	turns := 0.0
	routeTaken := map[CardinalLocation]bool{}

	for currentPos[0] >= 0 && currentPos[0] < len(room) && currentPos[1] >= 0 && currentPos[1] < len(room[currentPos[0]]) {
		position := CardinalLocation{Row: currentPos[0], Col: currentPos[1], Direction: currentDirection}
		if !routeTaken[position] {
			routeTaken[position] = true
		} else {
			return true
		}
		for counter := 0; counter < 4; counter++ {
			newPos := [2]int{currentPos[0] + currentDirection[0], currentPos[1] + currentDirection[1]}
			if newPos[0] >= 0 && newPos[0] < len(room) && newPos[1] >= 0 && newPos[1] < len(room[newPos[0]]) {
				if room[newPos[0]][newPos[1]] != "#" {
					break
				}
				turns++
				currentDirection = directions[int(math.Mod(turns, 4.0))]
			}
		}
		currentPos[0] += currentDirection[0]
		currentPos[1] += currentDirection[1]

	}
	return false
}
