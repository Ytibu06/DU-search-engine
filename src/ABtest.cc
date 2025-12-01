#include <iostream>
#include "PageLib.h"
#include "Configuration.h"
#include "PageLibPreprocessor.h"
using namespace std;

void test()
{
    Configuration &conf =  Configuration::getInstance("/home/du/workSpace/myDev/search-engine/conf/myconf.conf");
    DirScanner scanner;

    PageLib lib(conf,scanner);
    lib.store();
}
// g++ ABtest.cc Configuration.cc ../include/tinyxml/tinyxml2.cpp  DirScanner.cc PageLib.cc

void test1(){
//g++ ABtest.cc PageLibPreprocessor.cc WebPage.cc 
//../include/tinyxml/tinyxml2.cpp Configuration.cc SplitTool.cc SplitToolCppJieba.cc PageLib.cc DirScanner.cc 
    Configuration &conf =  Configuration::getInstance("/home/du/workSpace/myDev/search-engine/conf/myconf.conf");
    SplitToolCppJieba splitTool(conf);
    PageLibPreprocessor preprocessor(conf, splitTool);
    preprocessor.doProcess();
}

int main()
{
    //test();
    test1();
    return 0;
}