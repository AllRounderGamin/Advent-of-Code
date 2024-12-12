package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	file, err := os.Open("./input.txt")
	if err != nil {
		fmt.Println("Error opening File")
		return
	}
	defer file.Close()

	var wordSearch [][]string

	scanner := bufio.NewScanner(file)
	var answer, answer2 int = 0, 0
	for scanner.Scan() {
		line := scanner.Text()
		splitLine := strings.Split(line, "")
		wordSearch = append(wordSearch, splitLine)
	}
	for i, searchLine := range wordSearch {
		for j, character := range searchLine {
			if character == "X" {
				answer += searchArea([2]int{i, j}, wordSearch)
			} else if character == "A" {
				if searchCross([2]int{i, j}, wordSearch) {
					answer2++
				}
			}
		}
	}
	fmt.Println(answer)
	fmt.Println(answer2)
}

func searchArea(pos [2]int, wordSearch [][]string) int {
	adjustments := [8][2]int{{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1}}
	found := 0
	for _, adjust := range adjustments {
		newPos := [2]int{pos[0] + adjust[0], pos[1] + adjust[1]}
		if searchLine(newPos, adjust, []string{"M", "A", "S"}, wordSearch) {
			found++
		}
	}
	return found
}

func searchLine(pos [2]int, direction [2]int, search []string, wordSearch [][]string) bool {
	if pos[0] < 0 || pos[1] < 0 || pos[0] > len(wordSearch)-1 || pos[1] > len(wordSearch[pos[0]])-1 {
		return false
	} else {
		if wordSearch[pos[0]][pos[1]] == search[0] {
			newPos := [2]int{pos[0] + direction[0], pos[1] + direction[1]}
			search = search[1:]
			if len(search) == 0 {
				return true
			}
			return searchLine(newPos, direction, search, wordSearch)
		}
	}
	return false
}

func searchCross(pos [2]int, wordSearch [][]string) bool {
	directions := [4][2]int{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}}
	line := false
	for _, direction := range directions {
		newPos := [2]int{pos[0] + direction[0], pos[1] + direction[1]}
		if searchChar(newPos, "M", wordSearch) {
			newPos = [2]int{pos[0] + direction[0]*-1, pos[1] + direction[1]*-1}
			if searchChar(newPos, "S", wordSearch) {
				if line {
					return true
				} else {
					line = true
				}
			}
		}
	}
	return false
}

func searchChar(pos [2]int, search string, wordSearch [][]string) bool {
	if pos[0] < 0 || pos[1] < 0 || pos[0] > len(wordSearch)-1 || pos[1] > len(wordSearch[pos[0]])-1 {
		return false
	} else {
		if wordSearch[pos[0]][pos[1]] == search {
			return true
		}
	}
	return false
}
