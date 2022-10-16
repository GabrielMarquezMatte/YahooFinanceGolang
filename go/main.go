package main

import (
	"YahooFinance/libs/Download"
	ExcelReader "YahooFinance/libs/ExcelReader"
	"flag"
	"fmt"
	"strings"
	"sync"
	"time"
)

func ReadSymbol(symbol string, start time.Time, end time.Time) ([]ExcelReader.YahooData, error) {
	data, err := Download.DownloadStock(symbol, start, end)
	if err != nil {
		return nil, err
	}
	result, err := ExcelReader.ReadCSV(data, symbol)
	if err != nil {
		return nil, err
	}
	return result, nil
}

func CreateFile(symbol string, start time.Time, end time.Time) (int, error) {
	data, err := Download.DownloadStock(symbol, start, end)
	if err != nil {
		return 0, err
	}
	lines, err := ExcelReader.CreateCSV(data, symbol)
	if err != nil {
		return 0, err
	}
	return lines, nil
}

func main() {
	create_csv := flag.Bool("create_csv", false, "Create a CSV file")
	symbols_flag := flag.String("symbols", "AAPL", "Stock symbols (separated by commas)")
	start_flag := flag.String("start", "2018-01-01", "Start date")
	end_flag := flag.String("end", "2018-12-31", "End date")
	help := flag.Bool("help", false, "Show help")
	if *help {
		flag.PrintDefaults()
		return
	}
	flag.Parse()
	symbols := strings.Split(*symbols_flag, ",")
	start, err := time.Parse("2006-01-02", *start_flag)
	if err != nil {
		fmt.Println(err)
		return
	}
	end, err := time.Parse("2006-01-02", *end_flag)
	if err != nil {
		fmt.Println(err)
		return
	}
	//Create a variable to store the results, append to it and print it
	var results []ExcelReader.YahooData
	//Create a wait group to wait for all the goroutines to finish
	var wg sync.WaitGroup
	wg.Add(len(symbols))
	for _, symbol := range symbols {
		go func(symbol string) {
			defer wg.Done()
			if *create_csv {
				lines, err := CreateFile(symbol, start, end)
				if err != nil {
					fmt.Println(err)
					return
				}
				fmt.Printf("Created %s.csv with %d bytes\n", symbol, lines)
			} else {
				result, err := ReadSymbol(symbol, start, end)
				if err != nil {
					fmt.Println(err)
					return
				}
				results = append(results, result...)
			}
		}(symbol)
	}
	wg.Wait()
	if !*create_csv {
		fmt.Println(results)
	}
}
