#include <iostream>
using std::cout;
using std::endl;
#include "DictProducer.h"
#include "SplitTool.h"
#include "../include/simhash/Simhasher.hpp"
#include "../include/tinyxml/tinyxml2.h"
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

/**
 * 英文词典建立流程
 * 1. 获取所有英文文件
 * 2.获取停用词
 * 3.文件解析导入到容器中（包括去除停用词）
 * 4.保存词典
 */
// void test(){
//     //g++ AAtest.cc DictProducer.cc Configuration.cc SplitTool.cc SplitToolCppJieba.cc ../include/tinyxml/tinyxml2.cpp
//     Configuration &conf =  Configuration::getInstance("/home/du/workSpace/myDev/SearchEngine/conf/myconf.conf");

//     set<string> stop =  conf.getStopWordList();//获取停用词
//     // for(auto & item: stop){
//     //     cout << item << endl;
//     // }cout << endl;

//     SplitToolCppJieba splitTool(conf);//创建分词对象

//     DictProducer dictCn("/home/du/workSpace/myDev/SearchEngine/source/art", stop, &splitTool);
//     dictCn.buildCnDict();
//     dictCn.buildIndex();
//     //dictCn.showDict();
//     dictCn.storeDict("/home/du/workSpace/myDev/SearchEngine/data/dict.dat");
//     dictCn.storeIndex("/home/du/workSpace/myDev/SearchEngine/data/dictIndex.dat");
//     //dictCn.showFiles();

//     DictProducer dictEn("/home/du/workSpace/myDev/SearchEngine/source/eng",stop);    //根据语料库构造对象
//     dictEn.buildEnDict();//建立词典
//     dictEn.buildIndex();
//     //dictEn.showDict();
//     dictEn.storeDict("/home/du/workSpace/myDev/SearchEngine/data/Endict.dat");
//     dictEn.storeIndex("/home/du/workSpace/myDev/SearchEngine/data/EndictIndex.dat");
//     //dictEn.showFiles();
// }

// void test1(){
//     DirScanner dir;
//     dir("/home/du/workSpace/myDev/SearchEngine/bin");
//     //dir.traverse("/home/du/workSpace/myDev/SearchEngine/source/cn");
//     vector<string> files = dir.getFiles();

//     for(auto &file:files){
//         cout << file << endl;
//     }
// }

// 规范化标题（去除空格，转为小写等）
// std::string normalize_title(const std::string& title) {
//     std::string result = title;

//     // 转为小写
//     for (char& c : result) {
//         if (c >= 'A' && c <= 'Z') c |= 0x20;
//     }

//     // 移除多余空格（可选）
//     result.erase(std::remove_if(result.begin(), result.end(),
//         [](char c) { return std::isspace(static_cast<unsigned char>(c)); }),
//         result.end());

//     return result;
// }

// // 生成规范化后的哈希 ID
// std::string generate_normalized_id(const std::string& title) {
//     std::string normalized = normalize_title(title);
//     std::size_t hash = std::hash<std::string>{}(normalized);
//     std::stringstream ss;
//     ss << "news_" << std::hex << hash;
//     return ss.str();
// }
// void test2(){
//     string title = "特斯拉在华召回超3.5万辆Model S和Model X";
//     //std::string normalized = normalize_title(title);
//     std::size_t hash = std::hash<std::string>{}(title);
//     std::stringstream ss;
//     ss << std::hex << hash;
//     cout << hash << endl;
//     cout << ss.str() << endl;
// }

// simhash计算
//  void test3(){

//     simhash::Simhasher simhasher("../include/simhash/dict/jieba.dict.utf8","../include/simhash/dict/hmm_model.utf8",
//         "../include/simhash/dict/idf.utf8","../include/simhash/dict/stop_words.utf8");
//     string s("我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，走上人生巅峰。");
//     size_t topN = 5;
//     uint64_t u64 = 0;
//     vector<pair<string ,double> > res;
//     simhasher.extract(s, res, topN);
//     simhasher.make(s, topN, u64);
//     cout<< "文本：\"" << s << "\"" << endl;
//     cout << "关键词序列是: " << res << endl;
//     cout<< "simhash值是: " << u64<<endl;

//     const char * bin1 = "100010110110";
//     const char * bin2 = "110001110011";
//     uint64_t u1, u2;
//     u1 = simhash::Simhasher::binaryStringToUint64(bin1);
//     u2 = simhash::Simhasher::binaryStringToUint64(bin2);

//     cout<< bin1 << "和" << bin2 << " simhash值的相等判断如下："<<endl;
//     cout<< "海明距离阈值默认设置为3，则isEqual结果为：" << (simhash::Simhasher::isEqual(u1, u2)) << endl;
//     cout<< "海明距离阈值默认设置为5，则isEqual结果为：" << (simhash::Simhasher::isEqual(u1, u2, 5)) << endl;

//     //return simhash.isEqual(u64_bin1, u64_bin2);
// }

void test4()
{
    string file = "/home/du/workSpace/myDev/SearchEngine/source/webpageSource/book.xml";

    tinyxml2::XMLDocument doc;
    doc.LoadFile(file.c_str());
    if (doc.Error())
    {
        cerr << "parse xml error" << "\n";
    }

    tinyxml2::XMLElement *pathElement = doc.FirstChildElement("rss");
    if(pathElement){
        tinyxml2::XMLElement *channelElement = pathElement->FirstChildElement("channel");
        if(channelElement){ 
            tinyxml2::XMLElement *itemElement = channelElement->FirstChildElement("item");
            if(itemElement){
                cout << itemElement->FirstChildElement("title")->GetText() << "\n";
                //itemElement = itemElement->NextSiblingElement("item");
                cout << itemElement->GetDocument() << "\n";
            }
            cout << "channelElement" << "\n";
        }else{
            cerr << "no channel element" << "\n";
        }
    }else{
        cerr << "no path element" << "\n";
    }
}
int main()
{

    test4();

    return 0;
}