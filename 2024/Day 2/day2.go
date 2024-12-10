package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	file, err := os.Open("./message(2).txt")
	if err != nil {
		fmt.Println("Error opening File")
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	answer1 := 0
	answer2 := 0

	for scanner.Scan() {
		line := scanner.Text()
		splitLine := strings.Fields(line)
		if ascCheck(splitLine) || descCheck(splitLine) {
			answer1++
		}
		if ascCheck2(splitLine) || descCheck2(splitLine) {
			answer2++
		}
	}

	fmt.Println(answer1)
	fmt.Println(answer2)

}

func descCheck(line []string) bool {
	num1, _ := strconv.Atoi(line[0])
	for i := 1; i < len(line); i++ {
		num2, _ := strconv.Atoi(line[i])
		if num1-num2 <= 0 {
			return false
		} else if num1-num2 < 1 || num1-num2 > 3 {
			return false
		}
		num1 = num2
	}
	return true
}

func ascCheck(line []string) bool {
	num1, _ := strconv.Atoi(line[0])
	for i := 1; i < len(line); i++ {
		num2, _ := strconv.Atoi(line[i])
		if num1-num2 >= 0 {
			return false
		} else if num1-num2 > -1 || num1-num2 < -3 {
			return false
		}
		num1 = num2
	}
	return true
}

func descCheck2(line []string) bool {
	num1, _ := strconv.Atoi(line[0])
	lineCopy := make([]string, len(line))
	lineCopy2 := make([]string, len(line))
	copy(lineCopy, line)
	copy(lineCopy2, line)
	for i := 1; i < len(lineCopy); i++ {
		num2, _ := strconv.Atoi(lineCopy[i])
		if num1-num2 < 1 || num1-num2 > 3 {
			lineCopy = append(lineCopy[:i-1], lineCopy[i:]...)
			lineCopy2 = append(lineCopy2[:i], lineCopy2[i+1:]...)
			return (descCheck(lineCopy) || descCheck(lineCopy2))
		} else {
			num1 = num2
		}
	}
	return true
}

func ascCheck2(line []string) bool {
	num1, _ := strconv.Atoi(line[0])
	lineCopy := make([]string, len(line))
	lineCopy2 := make([]string, len(line))
	copy(lineCopy, line)
	copy(lineCopy2, line)
	for i := 1; i < len(lineCopy); i++ {
		num2, _ := strconv.Atoi(lineCopy[i])
		if num1-num2 > -1 || num1-num2 < -3 {
			lineCopy = append(lineCopy[:i-1], lineCopy[i:]...)
			lineCopy2 = append(lineCopy2[:i], lineCopy2[i+1:]...)
			return (ascCheck(lineCopy) || ascCheck(lineCopy2))
		} else {
			num1 = num2
		}
	}
	return true
}
