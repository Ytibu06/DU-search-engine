#include "PageLibPreprocessor.h"
#include "DirScanner.h"
#include "WebPage.h"

#include "../include/tinyxml/tinyxml2.h"

#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>

using std::cerr;
using std::ifstream;
using std::ofstream;
using std::cout;

PageLibPreprocessor::PageLibPreprocessor(Configuration &config, SplitToolCppJieba &jieba)
    : _jieba(jieba)
{
    readInfoFromFile(config, _jieba);
}

//预处理
void PageLibPreprocessor::doProcess()
{
    cutRedundantPages();
    buildInvertIndexTable();
    storeOnDisk();
}

// 根据配置信息读取网页库和位置偏移库的内容
void PageLibPreprocessor::readInfoFromFile(Configuration &config, SplitToolCppJieba &_jieba)
{
    string element;
    std::cout << "Reading web page library..." << "\n";
    map<string, string> conf = config.getConfigMap();
    std::string _webPagePath = conf["RE_WEB_PAGE_PATH"]; // 直接获取扫描配置文件的容器

    // 打开网页库文件
    ifstream ifs(_webPagePath);
    if (!ifs)
    {
        cerr << "open file error" << "\n";
    }

    //解析每个doc
    tinyxml2::XMLDocument doc; // 获取所有文档，并生成vector<webpage>。
    doc.LoadFile(_webPagePath.c_str());
    tinyxml2::XMLElement *webDoc = doc.FirstChildElement("doc");

    while (webDoc)
    {
        // 获取doc节点
        tinyxml2::XMLPrinter printer;
        webDoc->Accept(&printer);
        element = string(printer.CStr());

        //根据每个doc节点，生成webpage对象，并存储到vector中
        WebPage webPage(element, config, _jieba);
        _pageLib.push_back(webPage);

        // 获取下一个doc节点
        webDoc = webDoc->NextSiblingElement("doc");
    }
}

// 对冗余的网页进行去重
void PageLibPreprocessor::cutRedundantPages()
{

    std::sort(_pageLib.begin(), _pageLib.end());
    // 排序

    auto last = std::unique(_pageLib.begin(), _pageLib.end());
    // 重复元素排序到容器后端，并返回重复元素在后端的起点迭代器

    _pageLib.erase(last, _pageLib.end());
    // 删除重复元素：将起点迭代器到末尾删除
}

// 创建倒排索引表
void PageLibPreprocessor::buildInvertIndexTable()
{
    for (auto &webPage : _pageLib)
    {
    }
}

// 将经过预处理之后的网页库、位置偏移库和倒排索引表写回到磁盘上
void PageLibPreprocessor::storeOnDisk()
{
}

//SplitToolCppJieba _jieba;    // 分词对象
//vector <WebPage> _pageLib;  // 网页库容器的对象
//unordered_map<int, pair<int, int> > _offsetLib; //网页偏移库对象
//unordered_map<string, vector<pair<int, double>>> _invertIndexTable; //倒排索引表对象