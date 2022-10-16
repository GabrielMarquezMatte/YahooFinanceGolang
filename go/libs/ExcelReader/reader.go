package excelreader

import (
	"bytes"
	"encoding/csv"
	"os"
	"strconv"
	"time"
)

type YahooData struct {
	Date   time.Time
	Open   float64
	High   float64
	Low    float64
	Close  float64
	Adj    float64
	Volume int64
	Symbol string
}

func ReadCSV(data []byte, symbol string) ([]YahooData, error) {
	r := csv.NewReader(bytes.NewReader(data))
	records, err := r.ReadAll()
	if err != nil {
		return nil, err
	}
	result := make([]YahooData, 0)
	for _, record := range records[1:] {
		date, err := time.Parse("2006-01-02", record[0])
		if err != nil {
			return nil, err
		}
		open, err := strconv.ParseFloat(record[1], 64)
		if err != nil {
			return nil, err
		}
		high, err := strconv.ParseFloat(record[2], 64)
		if err != nil {
			return nil, err
		}
		low, err := strconv.ParseFloat(record[3], 64)
		if err != nil {
			return nil, err
		}
		close, err := strconv.ParseFloat(record[4], 64)
		if err != nil {
			return nil, err
		}
		adj, err := strconv.ParseFloat(record[5], 64)
		if err != nil {
			return nil, err
		}
		volume, err := strconv.ParseInt(record[6], 10, 64)
		if err != nil {
			return nil, err
		}
		result = append(result, YahooData{
			Date:   date,
			Open:   open,
			High:   high,
			Low:    low,
			Close:  close,
			Adj:    adj,
			Volume: volume,
			Symbol: symbol,
		})
	}
	return result, nil
}

// Function to save the data to a file
func CreateCSV(data []byte, symbol string) (int, error) {
	//Create the file
	file, err := os.Create(symbol + ".csv")
	if err != nil {
		return 0, err
	}
	defer file.Close()
	//Write the data to the file
	n, err := file.Write(data)
	if err != nil {
		return 0, err
	}
	return n, nil
}
