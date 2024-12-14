package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
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

	scanner := bufio.NewScanner(file)
	answer, answer2 := 0, 0

	for scanner.Scan() {
		line := scanner.Text()
		splitLine := strings.Split(line, ":")
		result, _ := strconv.Atoi(splitLine[0])
		nums := []int{}
		for _, number := range strings.Fields(splitLine[1]) {
			integer, _ := strconv.Atoi(number)
			nums = append(nums, integer)
		}
		if testPossibilities(result, nums, 2) {
			answer += result
		}
		if testPossibilities(result, nums, 3) {
			answer2 += result
		}
	}
	fmt.Println(answer)
	fmt.Println(answer2)
}

func testPossibilities(result int, nums []int, opts int) bool {
	instructions := make([]string, len(nums)-1)
	maxPermutations := math.Pow(float64(opts), float64(len(instructions)))
	for i := 0.0; i < maxPermutations; i++ {
		currentStep := strings.Split(strconv.FormatInt(int64(i), opts), "")
		for r := 1; r <= len(currentStep); r++ {
			instructions[len(instructions)-r] = currentStep[len(currentStep)-r]
		}
		currentNum := nums[0]
		for j := 0; j < len(instructions); j++ {
			if instructions[j] == "0" || instructions[j] == "" {
				currentNum += nums[j+1]
			} else if instructions[j] == "1" {
				currentNum *= nums[j+1]
			} else if instructions[j] == "2" {
				newNumStr := strconv.Itoa(currentNum) + strconv.Itoa(nums[j+1])
				currentNum, _ = strconv.Atoi(newNumStr)
			}
		}
		if currentNum == result {
			return true
		}
	}
	return false
}
