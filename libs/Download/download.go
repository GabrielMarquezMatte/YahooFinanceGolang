package Download

import (
	"fmt"
	"net/http"
	"time"
)

const BASE_URL string = "https://query1.finance.yahoo.com/v7/finance/download/%s?period1=%d&period2=%d&interval=1d&events=history"

func DownloadStock(symbol string, start time.Time, end time.Time) ([]byte, error) {
	url := fmt.Sprintf(BASE_URL, symbol, start.Unix(), end.Unix())
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()
	data := make([]byte, 0)
	for {
		buf := make([]byte, 1024)
		n, err := resp.Body.Read(buf)
		if err != nil {
			break
		}
		data = append(data, buf[:n]...)
	}
	return data, nil
}
