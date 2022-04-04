package main

import (
	"encoding/json"
	"os"
)

type video struct {
	Id          string
	Title       string
	Description string
	Imageurl    string
	Url         string
}

func getVideos() (videos []video) {

	fileBytes, err := os.ReadFile("./videos.json")
	if err != nil {
		panic(err)
	}
	err = json.Unmarshal(fileBytes, &videos)
	if err != nil {
		panic(err)
	}
	return videos
}

func getVideosUpdated() (videos []video) {

	fileBytes, err := os.ReadFile("./videos-updated.json")
	if err != nil {
		panic(err)
	}
	err = json.Unmarshal(fileBytes, &videos)
	if err != nil {
		panic(err)
	}
	return videos
}

func saveVideos(videos []video) {

	videoBytes, err := json.Marshal(videos)
	if err != nil {
		panic(err)
	}

	err = os.WriteFile("./videos-updated.json", videoBytes, 0644)
	if err != nil {
		panic(err)
	}

}
