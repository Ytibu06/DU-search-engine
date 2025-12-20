#include <iostream>
#include <chrono>


#include "PageLib.h"
#include "Configuration.h"
#include "PageLibPreprocessor.h"
#include "SplitTool.h"
using namespace std;

// void test()
// {
//     Configuration &conf =  Configuration::getInstance("/root/workSpace/myDev/search-engine/conf/myconf.conf");
//     DirScanner scanner;

//     PageLib lib(conf,scanner);
//     lib.create();
//     lib.store();
// }
// g++ ABtest.cc Configuration.cc ../include/tinyxml/tinyxml2.cpp  DirScanner.cc PageLib.cc


/* jieba测试*/
// void jiebaTest(){
//     Configuration &conf =  Configuration::getInstance("/root/workSpace/myDev/search-engine/conf/myconf.conf");
//     SplitToolCppJieba jieba(conf);
//     const int test_count = 1000; // 测试轮数
//     int count = 0;

//     auto start_time = std::chrono::high_resolution_clock::now();

//     while (count < test_count)
//     {
//         vector<string> result;
//         jieba.cut(" "
//             ); // 添加了result参数以接收分词结果 "
//             ++count;
//     }

//     auto end_time = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

//     cout << "Total time for " << test_count << " cuts: " << duration.count() << " microseconds" << endl;
//     cout << "Average time per cut: " << (double)duration.count() / test_count << " microseconds" << endl;
// }

void test2()
{
    Configuration &conf =  Configuration::getInstance("/root/workSpace/myDev/search-engine/conf/myconf.conf");
    SplitToolCppJieba jieba(conf);
    PageLibPreprocessor preprocessor(conf, jieba); // 修改为引用传递
    preprocessor.doProcess();
}

int main()
{
    //test();
    //jiebaTest();
    test2();
    return 0;
}