package main

import (
	"encoding/json"
	"fmt"
	"os"
)

type arrStudent []Student

func Editing(s arrStudent) {
	for idx, _ := range s {
		s[idx].Age += 1
	}
	fmt.Println(s)
}

func AccessingData() (s []Student) {

	rawData, err := os.ReadFile("testFiles/demo02.json")
	if err != nil {
		panic("ReadFile")
	}
	err = json.Unmarshal(rawData, &s)
	if err != nil {
		panic("Unmarshal")
	}
	return
}
