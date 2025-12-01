#ifndef __PAGELIB_H__
#define __PAGELIB_H__ 

#include "Configuration.h"
#include "DirScanner.h"

#include <vector>
#include <string>
#include <map>
using std::string;
using std::vector;
using std::map;

/**
 * 网页库类
 */

class PageLib {
public:
    PageLib(Configuration& conf, DirScanner& dirScanner);
    void store() const;   // 存储网页库和网页偏移库

private:
    void create(vector<string> &fileNameList);  // 创建网页库，初始化时直接处理加载


private:
    string _ripageDat;
    string _offsetDat;
    DirScanner & _dirScanner;   // 扫描目录对象的引用
    vector<string> _pages;  //存放格式化网页的容器
    map<int, std::pair<int, int> > _offsetLib;   //存放网页的偏移量（每篇文档在网页库的位置）
};

#endif