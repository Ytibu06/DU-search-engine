#include "PageLib.h"

#include "Configuration.h"
#include "DirScanner.h"

#include "../include/tinyxml/tinyxml2.h"

#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using std::cerr;
using std::cout;
using std::hash;
using std::ifstream;
using std::ofstream;
using std::regex;
using std::string;
using std::to_string;

PageLib::PageLib(Configuration &config, DirScanner &dirScanner)
    : _dirScanner(dirScanner)
{
    //获取配置，输出webpage存储路径
    map<string, string> conf = config.getConfigMap();
    std::string _webPagePath = conf["WEB_PAGE_PATH"];

    //遍历webpage目录,并存储
    dirScanner(_webPagePath);
    vector<string> pageFiles = dirScanner.getFiles();

    //将配置中读取的路径交给网页库处理函数，生成网页库容器
    create(pageFiles);

}

void PageLib::create(vector<string> &fileNameList) // 创建网页库
{
    _pages.clear();//为网页库容器添加内容前确保容器为空

    for (auto &fileName : fileNameList)
    {
        tinyxml2::XMLDocument doc;
        doc.LoadFile(fileName.c_str());
        if (doc.Error())
        {
            cerr << "PageLib::create: Error parsing file " << fileName << " " << doc.ErrorIDToName(doc.ErrorID()) << "\n";
            continue;
        }

        size_t i = 0;
        tinyxml2::XMLElement *item = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
        if(!item){
            cout << "PageLib::create: item is null" << "\n";
        }

        //若有item元素，读取内部元素内容，拼接成字符串，加入格式化容器中
        while (item)
        {
            std::regex pattern(R"(<!\[CDATA\[(.*?)\]\]>)"); // 正则

            tinyxml2::XMLElement *titleElement = item->FirstChildElement("title");
            tinyxml2::XMLElement *linkElement = item->FirstChildElement("link");
            tinyxml2::XMLElement *descElement = item->FirstChildElement("description");

            string title = regex_replace(titleElement->GetText() ? titleElement->GetText() : "", pattern, "");
            string url = linkElement->GetText() ? linkElement->GetText() : "";
            string content = descElement->GetText() ? descElement->GetText() : "";
            string docid = to_string(++i);

            string fmtTxt = string("<doc>\n") +
                            "<docid>" + docid + "</docid>\n" +
                            "<url>" + url + "</url>\n" +
                            "<title>" + title + "</title>\n" +
                            "<content>" + content + "</text>\n" +
                            "</doc>\n";

            _pages.push_back(fmtTxt);//将格式化后的网页加入容器

            // 移动到下一个item元素，避免无限循环
            item = item->NextSiblingElement("item");
        }
    }
}

// 存储网页库和网页偏移库
void PageLib::store(const string &pathName)
{
    std::ofstream ofs(pathName);
    if (!ofs)
    {
        std::cerr << "PageLib::store: opendir " << pathName  << " error" << "\n";
        return;
    }

    for (const auto &page : _pages)
    {
        ofs << page;
    }

    ofs.close();
}

// DirScanner & _dirScanner;   // 扫描目录对象的引用
// vector<string> _pages;  //存放格式化网页的容器
// map<int, std::pair<int, int> > _offsetLib;   //存放网页的偏移量（每篇文档在网页库的位置）