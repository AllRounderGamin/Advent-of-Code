package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"slices"
	"strconv"
	"strings"
)

func main() {
	file, err := os.Open("./input.txt")
	if err != nil {
		fmt.Println("Error opening File")
		return
	}
	defer file.Close()

	var list1 []int
	var list2 []int

	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		line := scanner.Text()
		splitLine := strings.Fields(line)
		num1, _ := strconv.Atoi(splitLine[0])
		num2, _ := strconv.Atoi(splitLine[1])
		list1 = append(list1, num1)
		list2 = append(list2, num2)
	}
	slices.Sort(list1)
	slices.Sort(list2)

	answer1 := 0

	for i := 0; i < len(list1); i++ {
		answer1 += int(math.Abs(float64(list1[i] - list2[i])))
	}

	fmt.Println(answer1)

	var answer2, list2Pointer, currentNumber, answerAddition int = 0, 0, 0, 0
	dupe := false

	for i := 0; i < len(list1); i++ {
		if currentNumber != list1[i] {
			currentNumber = list1[i]
			dupe = false
		} else if currentNumber == list1[i] && dupe {
			answer2 += answerAddition
		}
		copies := 0
		for currentNumber >= list2[list2Pointer] {
			if currentNumber == list2[list2Pointer] {
				copies++
				dupe = true
			}
			list2Pointer++
			if list2Pointer > len(list2)-1 {
				list2Pointer = len(list2) - 1
				break
			}
		}
		answerAddition = currentNumber * copies
		answer2 += answerAddition
	}
	fmt.Println(answer2)
}
