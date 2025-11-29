#include <iostream>
using std::cout;
using std::endl;
#include "DictProducer.h"
#include "SplitTool.h"

/**
 * 英文词典建立流程
 * 1. 获取所有英文文件
 * 2.获取停用词
 * 3.文件解析导入到容器中（包括去除停用词）
 * 4.保存词典
 */
void test(){

    Configuration &conf =  Configuration::getInstance("/home/du/workSpace/myDev/SearchEngine/conf/myconf.conf");

    set<string> stop =  conf.getStopWordList();//获取停用词
    // for(auto & item: stop){
    //     cout << item << endl;
    // }cout << endl;

    SplitToolCppJieba splitTool(conf);//创建分词对象

    DictProducer dictCn("/home/du/workSpace/myDev/SearchEngine/source/art", stop, &splitTool);
    dictCn.buildCnDict();
    dictCn.buildIndex();
    //dictCn.showDict();
    dictCn.storeDict("/home/du/workSpace/myDev/SearchEngine/data/dict.dat");
    dictCn.storeIndex("/home/du/workSpace/myDev/SearchEngine/data/dictIndex.dat");
    //dictCn.showFiles();

    DictProducer dictEn("/home/du/workSpace/myDev/SearchEngine/source/eng",stop);    //根据语料库构造对象
    dictEn.buildEnDict();//建立词典
    dictEn.buildIndex();
    //dictEn.showDict();
    dictEn.storeDict("/home/du/workSpace/myDev/SearchEngine/data/Endict.dat");
    dictEn.storeIndex("/home/du/workSpace/myDev/SearchEngine/data/EndictIndex.dat");
    //dictEn.showFiles();
}

int main(){

    test();

    return 0;
}