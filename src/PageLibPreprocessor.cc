#include "PageLibPreprocessor.h"
#include "DirScanner.h"
#include "WebPage.h"

#include "../include/tinyxml/tinyxml2.h"

#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>

using std::ofstream;
using std::ifstream;
using std::cerr;



PageLibPreprocessor::PageLibPreprocessor(Configuration &config, SplitToolCppJieba &jieba)
: _jieba(jieba)
{
    readInfoFromFile(config, _jieba);
    
}

void PageLibPreprocessor::doProcess()
{
    cutRedundantPages();
    buildInvertIndexTable();
    storeOnDisk();
}

//根据配置信息读取网页库和位置偏移库的内容
void PageLibPreprocessor::readInfoFromFile(Configuration &config, SplitToolCppJieba &_jieba)
{
    string element;

    map<string,string> conf = config.getConfigMap();
    std::string _webPagePath = conf["WEB_PAGE_PATH"];//直接获取扫描配置文件的容器

    DirScanner dirScanner;
    dirScanner(_webPagePath);
    vector<string> pageFiles = dirScanner.getFiles();//直接获取文件路径

    for(auto& file : pageFiles){//遍历文件
        ifstream ifs(file);
        if(!ifs){
            cerr<<"open file error"<< "\n";
            continue;
        }
        
        tinyxml2::XMLDocument doc;  //获取所有文档，并生成vector<webpage>。
        doc.LoadFile(file.c_str());
        tinyxml2::XMLElement* item = doc.RootElement()
            ->FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
        if(item){
            string element = item->GetText();
            WebPage webPage(element, config,_jieba);
            _pageLib.push_back(webPage);
        }
        
    }
}  

//对冗余的网页进行去重
void PageLibPreprocessor::cutRedundantPages()
{

    std::sort(_pageLib.begin(), _pageLib.end());    
    //排序

    auto last = std::unique(_pageLib.begin(), _pageLib.end());
    //重复元素排序到容器后端，并返回重复元素在后端的起点迭代器

    _pageLib.erase(last, _pageLib.end());
    //删除重复元素：将起点迭代器到末尾删除
}

//创建倒排索引表
void PageLibPreprocessor::buildInvertIndexTable()
{
    for (auto& webPage : _pageLib)
    { 
    }
}

//将经过预处理之后的网页库、位置偏移库和倒排索引表写回到磁盘上
void PageLibPreprocessor::storeOnDisk()
{
    

}

// SplitToolCppJieba _jieba;    // 分词对象
//     vector <WebPage> _pageLib;  // 网页库容器的对象
//     unordered_map<int, pair<int, int> > _offsetLib; //网页偏移库对象
//     unordered_map<string, vector<pair<int, double>>> _invertIndexTable; //倒排索引表对象