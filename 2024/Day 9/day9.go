package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
	"strconv"
)

func main() {
	file, err := os.Open("./input.txt")
	if err != nil {
		fmt.Println("Error opening File")
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	fileSystem := []string{}
	fileBlockSystem := [][]string{}

	scanner.Scan()
	id := 0
	data := true
	line := scanner.Text()
	for _, char := range line {
		space, _ := strconv.Atoi(string(char))
		dataBlock := []string{}
		for i := 0; i < space; i++ {
			if data {
				fileSystem = append(fileSystem, strconv.Itoa(id))
				dataBlock = append(dataBlock, strconv.Itoa(id))
			} else {
				fileSystem = append(fileSystem, ".")
				dataBlock = append(dataBlock, ".")
			}
		}
		if data {
			id++
		}
		data = !data
		if len(dataBlock) != 0 {
			fileBlockSystem = append(fileBlockSystem, dataBlock)
		}
	}
	part1(fileSystem)
	part2(fileBlockSystem)

}

func part1(fileSystem []string) {
	reverseIndex := len(fileSystem) - 1
	for i := 0; i < len(fileSystem); i++ {
		if i >= reverseIndex {
			break
		}
		if fileSystem[i] == "." {
			fileSystem[i] = fileSystem[reverseIndex]
			fileSystem[reverseIndex] = "."
		}
		for fileSystem[reverseIndex] == "." {
			reverseIndex--
		}
	}
	answer := 0
	for i := 0; fileSystem[i] != "."; i++ {
		value, _ := strconv.Atoi(fileSystem[i])
		answer += i * value
	}
	fmt.Println(answer)
}

func part2(blockSystem [][]string) {
	for reverseIndex := len(blockSystem) - 1; reverseIndex >= 0; reverseIndex-- {
		if blockSystem[reverseIndex][0] == "." {
			continue
		}
		for i := 0; i < len(blockSystem) && i < reverseIndex; i++ {
			if blockSystem[i][0] == "." {
				if spaceLeft := len(blockSystem[i]) - len(blockSystem[reverseIndex]); spaceLeft >= 0 {
					arr1 := blockSystem[reverseIndex]
					arr2 := []string{}
					arr3 := []string{}
					for i := 0; i < spaceLeft; i++ {
						arr2 = append(arr2, ".")
					}
					for i := 0; i < len(blockSystem[reverseIndex]); i++ {
						arr3 = append(arr3, ".")
					}
					blockSystem[i] = arr1
					blockSystem[reverseIndex] = arr3
					if len(arr2) > 0 {
						if blockSystem[i+1][0] == "." {
							blockSystem[i+1] = append(blockSystem[i+1], arr2...)
						} else {
							blockSystem = slices.Insert(blockSystem, i+1, arr2)
							reverseIndex++
						}
					}
					break
				}
			}
		}
	}
	answer := 0

	var compactSystem []string
	for _, a := range blockSystem {
		compactSystem = append(compactSystem, a...)
	}
	for i := 0; i < len(compactSystem); i++ {
		if compactSystem[i] != "." {
			value, _ := strconv.Atoi(compactSystem[i])
			answer += i * value
		}
	}
	fmt.Println(answer)
}
