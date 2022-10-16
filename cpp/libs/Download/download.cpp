#include "download.hpp"
void CallBackFunction(char* ptr, size_t size, size_t nmemb, std::string* data){
    data->append(ptr, size * nmemb);
}
std::time_t SecondsSinceEpoch(std::tm& date){
    std::tm epoch{0};
    epoch.tm_year = 70;
    epoch.tm_mday = 1;
    std::time_t epoch_seconds = std::mktime(&epoch);
    std::time_t date_seconds = std::mktime(&date);
    return date_seconds - epoch_seconds;
}
std::string DownloadStock(std::string_view symbol,std::tm& start,std::tm& end){
    std::string buffer;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://query1.finance.yahoo.com/v7/finance/download/";
        url += symbol;
        url += "?period1=";
        url += std::to_string(SecondsSinceEpoch(start));
        url += "&period2=";
        url += std::to_string(SecondsSinceEpoch(end));
        url += "&interval=1d&events=history&includeAdjustedClose=true";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CallBackFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return buffer;
}