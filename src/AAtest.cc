
#include "../include/tinyxml/tinyxml2.h"
#include "../include/simhash/Simhasher.hpp"
#include "DictProducer.h"
#include "SplitTool.h"
#include "DirScanner.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>
#include <fstream>

using std::cerr;
using std::ifstream;
using std::string;
using std::stringstream;
using std::cout;
using std::endl;

/**
 * 英文词典建立流程
 * 1. 获取所有英文文件
 * 2.获取停用词
 * 3.文件解析导入到容器中（包括去除停用词）
 * 4.保存词典
 */

void test(){
    //g++ AAtest.cc DictProducer.cc Configuration.cc SplitTool.cc SplitToolCppJieba.cc ../include/tinyxml/tinyxml2.cpp
    Configuration &conf =  Configuration::getInstance("/home/du/workSpace/myDev/search-engine/conf/myconf.conf");

    set<string> stop =  conf.getStopWordList();//获取停用词

    SplitToolCppJieba splitTool(conf);//创建分词对象

    DictProducer dictCn("/home/du/workSpace/myDev/search-engine/source/art", stop, &splitTool);
    dictCn.buildCnDict();
    dictCn.buildIndex();
    dictCn.storeDict("/home/du/workSpace/myDev/search-engine/data/dict.dat");
    dictCn.storeIndex("/home/du/workSpace/myDev/search-engine/data/dictIndex.dat");


    DictProducer dictEn("/home/du/workSpace/myDev/search-engine/source/eng",stop);    //根据语料库构造对象
    dictEn.buildEnDict();//建立词典
    dictEn.buildIndex();

    dictEn.storeDict("/home/du/workSpace/myDev/search-engine/data/Endict.dat");
    dictEn.storeIndex("/home/du/workSpace/myDev/search-engine/data/EndictIndex.dat");

}


int main()
{
    test();
    return 0;
}