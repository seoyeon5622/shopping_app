//
// Created by 김서연 on 26. 1. 3.
//
#ifndef DKU_PROJECT_WEATHER_H
#define DKU_PROJECT_WEATHER_H

#include <stddef.h>
#include <string.h>
#include <curl/curl.h>

// API사용을 위해서는 API키를 발급받아야해서
// 발급을 받았습니다 -> 646f9c135815191df9e8fb938382b7c1
#define URL "http://api.openweathermap.org/data/2.5/weather?q=Seoul&appid=646f9c135815191df9e8fb938382b7c1"

size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data);

float get_current_temp_by_api();

#endif