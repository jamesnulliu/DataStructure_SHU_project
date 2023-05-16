#include <sstream>

#include "Search_07.hpp"
#include "Anagrams/word.h"
#include "Anagrams/Anagram.h"

namespace search {
    using namespace std;

    void Task07::solve()
    {
        wordlist word1;               //定义链表
        ifstream infile;
        int n;
        int num = 0;             //用来记忆单词在链表的序号
        cout << "Input File Location: ";
        string file{};
        cin >> file;
        cin.get();

        infile.open(file.data());    //将文件流对象与文件连接起来
        assert(infile.is_open());        //若失败,则输出错误消息,并终止程序运行

        string s1;

        while (getline(infile, s1))   //按行获取
        {
            if (s1[0] >= '0' && s1[0] <= '9') {
                n = s1[0] - '0';
                break;
            }
        }

        while (getline(infile, s1))  //这里个人规定的单词存放格式是一行换一行
        {
            istringstream is(s1);    //此函数用来将英文单词提取出来，但这一步会提取到标点
            string s2;
            while (is >> s2)
            {
                s2.erase(remove_if(s2.begin(), s2.end(), ispunct), s2.end());  //这部分用来去掉提取后的单词的标点
                word1.houcha(s2);      //插入链表
            }
        }

        infile.close();
        infile.open(file.data());
        string s;
        while (getline(infile, s))   //按行获取
        {
            if (s[0] >= '0' && s[0] <= '9') {
                break;
            }
            istringstream is(s);  //此函数用来将英文单词提取出来，但这一步会提取到标点
            string s3;
            while (is >> s3)
            {
                s3.erase(remove_if(s3.begin(), s3.end(), ispunct), s3.end());  //这部分用来去掉提取后的单词的标点
                vector<int> res = word1.compare(s3);
                for (auto it = res.begin(); it != res.end(); ++it) {
                    word1.input(*it, s3);
                }
            }
        }
        word1.show();
        infile.close();             //关闭文件输入流
    }
}