//
// Created by 김서연 on 26. 1. 3.
//
#include "weather.h"

size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    strcat(data, ptr);
    return size * nmemb;
}

float get_current_temp_by_api()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();

    if (curl) {
        char response_data_buffer[10000] = "";

        // URL 설정하기
        curl_easy_setopt(curl, CURLOPT_URL, URL);

        // 응답 데이터를 저장할 콜백 함수 설정
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_data_buffer);

        // 요청 실행
        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            // 받은 데이터에서 온도 부분만 파싱 (예: "temp": 294.25)
            char *temp_str = strstr(response_data_buffer, "\"temp\":");
            if (temp_str) {
                float temp;
                sscanf(temp_str, "\"temp\":%f", &temp);
                return (temp - 273.15);
            }
        }

        curl_easy_cleanup(curl);

    }
    curl_global_cleanup();

    return 0;
}
