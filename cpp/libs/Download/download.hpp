#ifndef YAHOO_DOWNLOAD_H
#define YAHOO_DOWNLOAD_H
#include <curl/curl.h>
#include <string>
#include <ctime>
#include <chrono>
#include <iostream>
std::string DownloadStock(std::string_view symbol,std::tm& start,std::tm& end);
#endif