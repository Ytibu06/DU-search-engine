# Makefile for SearchEngine project
# 这是一个简单的 Makefile 示例，用于编译 C++ 程序
# 它定义了如何编译和链接源代码文件

# 指定编译器
CXX = g++

# 编译选项
# -std=c++11 启用 C++11 标准支持
# -Wall 开启所有常见的警告信息
# -O2 优化级别2，提高执行效率
CXXFLAGS = -std=c++11 -Wall -O2

# 目标1: jieba 测试程序
# 输入命令 'make jieba' 将会编译 Testjieba.cc 并生成可执行文件 jieba
Jieba: Testjieba.cc
	$(CXX) $(CXXFLAGS) Testjieba.cc -o Jieba

# 目标2: simhash 测试程序
# 输入命令 'make simhash' 将会编译 Testsimhash.cc 并生成可执行文件 simhash
Simhash: Testsimhash.cc
	$(CXX) $(CXXFLAGS) Testsimhash.cc -o Simhash

# 清理目标，输入 'make clean' 可以删除编译生成的文件
clean:
	rm -f Jieba Simhash

# 默认目标，输入 'make' 或 'make all' 将会构建所有程序
all: Jieba Simhash