package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
)

func greet(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Hello GOLANG HTTP server!\n")
	for headerTag, values := range r.Header {
		fmt.Printf("[%v] -> %v\n", headerTag, values)
	}
	w.Header().Add("TestDatata", "Dipankar das")
	// fmt.Println("w.Header\t", w.Header())
}

func ToPrintJson(w http.ResponseWriter, r *http.Request) {
	// w.Write([]byte("Nice sd"))
	Video := getVideos()
	fmt.Fprintf(w, "Video data -> %v\n", Video)
}

func ToPrintJson2(w http.ResponseWriter, r *http.Request) {
	if r.Method == "GET" {
		Video := getVideosUpdated()
		fmt.Fprintf(w, "Video data -> %v\n", Video)
	} else {
		w.WriteHeader(405)
		fmt.Fprintf(w, "⚠️ INvalid Request")
	}
}

func ToPostJson(w http.ResponseWriter, r *http.Request) {
	if r.Method == "POST" {
		// Video[0].Id = "111111"
		body, err := ioutil.ReadAll(r.Body)
		if err != nil {
			panic(err)
		}
		w.Write(body)
		var videos []video
		err = json.Unmarshal(body, &videos)
		if err != nil {
			panic(err)
		}
		videos[1].Description = "\nDipankar Edited"
		saveVideos(videos)

	} else {
		w.WriteHeader(405)
		fmt.Fprintf(w, "⚠️ INvalid Request")
	}
}

func html(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "index.html")
}

func main() {
	http.HandleFunc("/", greet)
	http.HandleFunc("/view1", ToPrintJson)
	http.HandleFunc("/update", ToPostJson)
	http.HandleFunc("/view2", ToPrintJson2)
	http.HandleFunc("/html", html)

	http.ListenAndServe(":8080", nil)
}
