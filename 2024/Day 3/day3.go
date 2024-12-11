package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
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
	var answer1, answer2 int = 0, 0
	processCommand := true

	for scanner.Scan() {
		line := scanner.Text()
		mulExpr, _ := regexp.Compile(`mul\(\d{1,3},\d{1,3}\)|do\(\)|don't\(\)`)
		numExp, _ := regexp.Compile(`\d{1,3}`)
		commands := mulExpr.FindAll([]byte(line), -1)
		for _, command := range commands {
			if string(command) == "do()" {
				processCommand = true
			} else if string(command) == "don't()" {
				processCommand = false
			} else {
				var numsInt []int
				nums := numExp.FindAll(command, -1)
				for _, number := range nums {
					num, _ := strconv.Atoi(string(number))
					numsInt = append(numsInt, num)
				}
				answer1 += numsInt[0] * numsInt[1]
				if processCommand {
					answer2 += numsInt[0] * numsInt[1]
				}
			}
		}
	}
	fmt.Println(answer1, "\n", answer2)
}
