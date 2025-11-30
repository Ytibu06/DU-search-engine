#include <iostream>
#include "PageLib.h"
#include "Configuration.h"
#include "FileProcessor.h"

using namespace std;

void test()
{
    Configuration &conf =  Configuration::getInstance("/home/du/workSpace/myDev/SearchEngine/conf/myconf.conf");
    DirScanner scanner;
    FileProcessor processor("sdd");

    PageLib lib(conf,scanner,processor);
    lib.store("/home/du/workSpace/myDev/SearchEngine/data/page.txt");
}

int main()
{
    test();
    return 0;
}