#pragma once
#define MAX_ERROR_MESSAGE_LEN 1000
#pragma warning(disable:4996)
#include <cstring>
#include <iostream>

class Error
{
private:
    char message[MAX_ERROR_MESSAGE_LEN];    // �쳣��Ϣ

public:
    Error(const char* mes)
    {
        strcpy(message, mes);				// �����쳣��Ϣ
    }
    ~Error(void) {};				    	// ��������
    inline void Show() const;					// ��ʾ�쳣��Ϣ
};

void Error::Show()const
{
    std::cout << message << std::endl;			// ��ʾ�쳣��Ϣ
}