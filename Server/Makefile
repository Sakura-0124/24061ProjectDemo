# 编译器设置
CXX = g++
CXXFLAGS = -std=c++11 

# 链接器标志
LDFLAGS = -pthread -lsqlite3 -ljsoncpp

# 目标文件
TARGET = server

# 源文件
SOURCES = main.cpp \
          UserManager.cpp \
          EpollServer.cpp \
          JsonHandler.cpp

# 目标文件
OBJECTS = $(SOURCES:.cpp=.o)

# 默认目标
all: $(TARGET)

# 链接规则
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# 编译规则
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理规则
clean:
	rm -f $(OBJECTS) $(TARGET)

# 重新编译
rebuild: clean all

# 伪目标
.PHONY: all clean rebuild