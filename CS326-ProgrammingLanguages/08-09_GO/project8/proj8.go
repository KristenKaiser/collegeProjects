package main

import (
	"bufio"
	"fmt"
	"math"
	"math/rand"

	//"math/rand"
	"os"

	//"io"
	"strconv"
	"strings"
	//"reflect"
)

const MAXCOUNT int = 1000
const MINCOUNT int = 10
const MAXVALUE int = 1000
const PRINTPERLINE int = 10

func getData() []int {
	//numRands := 0
	//err = 0
	var numbers []int
	reader := bufio.NewReader(os.Stdin)

	fmt.Println("number of random numbers to generate:")
	fmt.Print("-> ")
	text, _ := reader.ReadString('\n')
	text = strings.Replace(text, "\n", "", -1)
	text = strings.Replace(text, " ", "", -1)
	count, err := strconv.Atoi(text)

	if err != nil || MINCOUNT > count || count > MAXCOUNT { // check if num is valid
		fmt.Println("ERROR: number ouside of bounds")
	}

	for i := 0; i < count; i++ {
		numbers = append(numbers, rand.Intn(MAXVALUE))
	}

	return numbers
}

func displayNums(count int, numbers []int) {
	for i := 0; i < count; i += PRINTPERLINE {
		for j := 0; j < PRINTPERLINE && ((i + j) < count); j++ {
			print(numbers[i+j], " ")
		}
		print("\n")
	}
	return
}

func quickSort(a []int, lo int, hi int) {
	i, j, h := lo, hi, 0
	x := a[(i+j)/2]
	didOnce := 0

	for i <= j || didOnce == 0 {
		for a[i] < x {
			i++
		}
		for a[j] > x {
			j--
		}
		if i <= j {
			h = a[i]
			a[i] = a[j]
			a[j] = h
			i++
			j--
		}
		didOnce = 1
	}

	if lo < j {
		quickSort(a, lo, j)
	}
	if i < hi {
		quickSort(a, i, hi)
	}
	return
}

func stats(a []int) (float64, float64, float64) {
	ave := 0.0
	varience := 0.0
	stdDev := 0.0
	//calcualte average
	for i := 0; i < len(a); i++ {
		ave += float64(a[i])
	}
	ave = ave / float64(len(a))

	//calculate standard deviation
	for i := 0; i < len(a); i++ {
		h := float64(a[i]) - ave
		varience += (h * h)
	}
	varience = varience / (float64(len(a) - 1))
	stdDev = math.Sqrt(varience)

	return ave, varience, stdDev
}

func displayData(a []int) {
	displayNums(len(a), a)
	ave, varience, stdDev := stats(a)
	println("\nSTATS:")
	println("average = ", ave)
	println("varience = ", varience)
	println("average = ", stdDev)

}

func main() {
	numbers := getData()
	println("UNORDERED SET:")
	displayNums(len(numbers), numbers)
	quickSort(numbers, 0, len(numbers)-1)
	println("\nORDERED SET:")
	displayData(numbers)
}
