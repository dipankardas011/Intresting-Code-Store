package main

import (
	"fmt"
	"os"
)

func ReadingPdfs() {
	fmt.Println("-------------------")
	rawData, err := os.ReadFile("01.pdf")

	if err != nil {
		panic(err)
	}

	fmt.Println(string(rawData))
	fmt.Println("-------------------")
}
