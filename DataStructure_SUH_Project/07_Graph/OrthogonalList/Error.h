#pragma once
#define MAX_ERROR_MESSAGE_LEN 1000
#pragma warning(disable:4996)
#include <cstring>
#include <iostream>

class Error
{
private:
    char message[MAX_ERROR_MESSAGE_LEN];    // 异常信息

public:
    Error(const char* mes)
    {
        strcpy(message, mes);				// 复制异常信息
    }
    ~Error(void) {};				    	// 析构函数
    inline void Show() const;					// 显示异常信息
};

void Error::Show()const
{
    std::cout << message << std::endl;			// 显示异常信息
}