#include "PageLibPreprocessor.h"
#include "DirScanner.h"
#include "WebPage.h"

#include "../include/tinyxml/tinyxml2.h"

#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

#include <sys/param.h>

using std::cerr;
using std::cout;
using std::ifstream;
using std::ofstream;

PageLibPreprocessor::PageLibPreprocessor(Configuration &config, SplitToolCppJieba &jieba)
    : _jieba(jieba)
{
    readInfoFromFile(config, _jieba);
}

// 预处理
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
    map<string, string> conf = config.getConfigMap();
    std::string _webPagePath = conf["RI_PAGE_DAT"]; // 直接获取扫描配置文件的容器
    string _offsetPath = conf["OFFSET_DAT"];

    ifstream ifsOFF(_offsetPath);
    if (!ifsOFF)
    {
        perror("PageLibPreprocessor::readInfoFromFile: open offset file error");
        return;
    }

    // 以二进制模式打开网页库文件
    ifstream ifsWeb(_webPagePath, std::ios::binary);
    if (!ifsWeb)
    {
        perror("PageLibPreprocessor::readInfoFromFile: open ripage file error");
        return;
    }

    string line;
    while (getline(ifsOFF, line))
    {
        int id, start, length; // 使用streamsize存储长度

        std::stringstream ss(line);
        if (!(ss >> id >> start >> length))
        {
            perror("PageLibPreprocessor::readInfoFromFile: parse offset file error");
            continue; // 跳过错误行
        }

        // 定位到指定位置
        ifsWeb.seekg(start, std::ios::beg);
        if (!ifsWeb)
        {
            perror("PageLibPreprocessor::readInfoFromFile: seek to position error");
            continue;
        }

        // 分配缓冲区并读取指定长度的数据
        vector<char> buffer(length + 1); // +1 for null terminator
        ifsWeb.read(buffer.data(), length);

        // 检查实际读取的字节数
        size_t bytesRead = ifsWeb.gcount();
        if (bytesRead != length)
        {
            perror("Error: Failed to read from file");
        }
        // 确保字符串以null结尾
        buffer[MIN(bytesRead, length)] = '\0';
        // 转换为string
        string info(buffer.data(), bytesRead);

        cout << "Reading file: " << info << "\n";

        WebPage webPage(info, config, _jieba);
        _pageLib.push_back(webPage);
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
        perror("docid");
        cout << "正在处理网页：" << webPage.getDocId() << "\n";

    }
}

// 将经过预处理之后的网页库、位置偏移库和倒排索引表写回到磁盘上
void PageLibPreprocessor::storeOnDisk()
{
}

// SplitToolCppJieba _jieba;    // 分词对象
// vector <WebPage> _pageLib;  // 网页库容器的对象
// unordered_map<int, pair<int, int> > _offsetLib; //网页偏移库对象
// unordered_map<string, vector<pair<int, double>>> _invertIndexTable; //倒排索引表对象