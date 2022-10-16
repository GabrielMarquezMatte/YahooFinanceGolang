add_library(YahooFinanceDownload download.cpp download.hpp)
target_link_libraries(YahooFinanceDownload PRIVATE ${CURL_LIBRARIES})
target_include_directories(YahooFinanceDownload PRIVATE ${CURL_INCLUDE_DIRS})