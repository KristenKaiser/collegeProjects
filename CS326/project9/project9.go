// web scraper by kristen kaiser

package main

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"strings"
	"time"

	"golang.org/x/net/html"
)

const LINKS_FILE string = "foundUrls.txt"
const IMAGE_FILE string = "foundImages.txt"

var imgList []string
var lnkList []string

func getLinks(n *html.Node) string {
	if n.Type == html.ElementNode && n.Data == "a" {
		for _, a := range n.Attr {
			if a.Key == "href" {
				if a.Val[0] == 'h' {
					return a.Val
				}
				break
			}
		}
	}
	return ""
}
func getPics(n *html.Node) string {
	if n.Type == html.ElementNode && n.Data == "img" {
		for _, a := range n.Attr {
			exten := a.Val[len(a.Val)-4:]
			if a.Key == "src" {
				if exten != ".svg" {
					return a.Val
				}
				break
			}
		}
	}
	return ""
}

func printNodeData(n *html.Node) {
	attr := n.Attr
	//if len(n.Attr) > 0 {
	fmt.Printf("attr: %s\n", n.Attr)
	fmt.Printf("attrlen %d\n", len(n.Attr))
	fmt.Printf("data: %s\n", n.Data)
	fmt.Printf("dataAtom: %s\n", n.DataAtom)
	fmt.Printf("Namespace: %s\n", n.Namespace)
	for _, a := range attr {
		fmt.Printf("-> key: %s\n", a.Key)
		fmt.Printf("-> value: %s\n", a.Val)
	}
	fmt.Println()
	return
}

func travelHtml(html_n *html.Node) {
	tLinks := getLinks(html_n)
	tPics := getPics(html_n)
	if tLinks != "" {
		lnkList = append(lnkList, tLinks)
	}
	if tPics != "" {
		imgList = append(imgList, tPics)
	}
	if html_n.NextSibling != nil {
		travelHtml(html_n.NextSibling)
	}
	if html_n.FirstChild != nil {
		travelHtml(html_n.FirstChild)
	}

	return
}

func getHtml(webAddr string) string {
	res, err := http.Get(webAddr)
	if err != nil {
		panic(err)
	}

	body, err := io.ReadAll(res.Body)
	if err != nil {
		panic(err)
	}
	res.Body.Close()
	return string(body)
}

func main() {
	urlList := []string{
		"https://www.unlv.edu/cs",
		"https://www.unlv.edu/engineering",
		"https://www.unlv.edu/engineering/advising-center",
		"https://www.unlv.edu/engineering/about",
		"https://www.unlv.edu/engineering/academic-programs",
		"https://www.unlv.edu/ceec",
		"https://ece.unlv.edu/",
		"https://www.unlv.edu/me",
		"https://www.unlv.edu/rotc",
		"https://www.unlv.edu/afrotc",
		"https://www.unlv.edu/eed",
		"https://www.unlv.edu/engineering/mendenhall",
		"https://www.unlv.edu/engineering/uas",
		"https://www.unlv.edu/engineering/solar",
		"https://www.unlv.edu/engineering/techcommercialization",
		"https://www.unlv.edu/engineering/railroad",
		"https://www.unlv.edu/engineering/future-students",
		"https://www.physics.unlv.edu/",
	}
	start := time.Now()

	f_img, err := os.Create(IMAGE_FILE)
	if err != nil {
		panic(err)
	}
	f_lnk, err := os.Create(LINKS_FILE)
	if err != nil {
		panic(err)
	}
	for _, currUrl := range urlList {
		body := getHtml(currUrl)
		html_reader, err := html.Parse(strings.NewReader(body))
		if err != nil {
			panic(err)
		}
		travelHtml(html_reader)

		for _, a := range imgList {
			_, err := f_img.WriteString(a)
			if err != nil {
				panic(err)
			}
			_, err = f_img.WriteString("\n")
			if err != nil {
				panic(err)
			}
		}
		for _, a := range lnkList {
			_, err := f_lnk.WriteString(a)
			if err != nil {
				panic(err)
			}
			_, err = f_lnk.WriteString("\n")
			if err != nil {
				panic(err)
			}
		}
	}
	f_img.Close()
	f_lnk.Close()
	elapsed := time.Since(start)
	fmt.Printf("Downloads completed in %s \n", elapsed)
}
