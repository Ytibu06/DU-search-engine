#ifndef __DIRSCANNER_H__
#define __DIRSCANNER_H__ 

#include <vector>
#include <string>
using std::string;
using std::vector;

class DirScanner{
public:
    DirScanner();
    void operator()();  //重载函数调用运算符，调用 traverse函数
    vector<string> files(); //返回_vecFilesfiles 的引用
    void traverse(const string &dirname);   //获取某一目录下的所有文件

private:
    vector<string> _files;  //存放每个语料的绝对路径

};

#endif