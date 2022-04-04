package main

import (
	"encoding/json"
	"fmt"
	"os"
)

type Student struct {
	Id     int    `json:"id"`
	Name   string `json:"name"`
	Age    int    `json:"age"`
	Branch string `json:"branch"`
	Major  string `json:"major"`
}

func initVal() (stu []Student) {

	stu = []Student{
		Student{
			Id:     1,
			Name:   "DD",
			Age:    21,
			Branch: "B.Tech.",
			Major:  "CSE",
		}, Student{
			Id:     2,
			Name:   "DD3 4",
			Age:    11,
			Branch: "M.Tech.",
			Major:  "EEE",
		}}
	return
}

func main() {
	fmt.Println("Hello world!!")
	stu := initVal()
	xyz, err := json.Marshal(stu)
	if err != nil {
		panic("Marshal error")
	}

	err = os.WriteFile("testFiles/demo01.json", xyz, 0744)
	if err != nil {
		panic("Writing Error")
	}
	Editing(stu)

	newDataSet := AccessingData()
	fmt.Println(newDataSet)
	ReadingPdfs()
}
