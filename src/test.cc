#include "SplitToolCppJieba.h"
#include "Configuration.h"
#include <iostream>
using std::cout;
using std::endl;

void SplitToolCppJiebaTest(){
    string confPath = "../conf/CppJieba.conf";
    cout << "Loading config from: " << confPath << endl;
    
    Configuration conf(confPath);
    auto configMap = conf.getConfigMap();
    
    // 打印配置信息用于调试
    for (const auto& pair : configMap) {
        cout << pair.first << " = " << pair.second << endl;
    }
    
    SplitToolCppJieba jieba(conf); 
    vector<string> words = jieba.cut("这是一个正常的行为");
    for(auto &word : words)
    {
        cout << word << endl;
    }
    
}

int main(int argc, char **argv)
{
    
}