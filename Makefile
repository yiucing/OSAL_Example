#----------------------------------------------指定编译工具链---------------------------------------------------
CROSS_COMPILE =                        #指定编译器种类
AS        = $(CROSS_COMPILE)as         #
LD        = $(CROSS_COMPILE)ld         #链接工具
CC        = $(CROSS_COMPILE)gcc        #编译工具
CPP       = $(CC) -E                   #
AR        = $(CROSS_COMPILE)ar         #打包工具
NM        = $(CROSS_COMPILE)nm         #
 
STRIP     = $(CROSS_COMPILE)strip      #优化工具
OBJCOPY   = $(CROSS_COMPILE)objcopy    #
OBJDUMP   = $(CROSS_COMPILE)objdump    #
 
export AS LD CC CPP AR NM               #将定义的变量导出，方便其他makefile使用
export STRIP OBJCOPY OBJDUMP            #将定义的变量导出，方便其他makefile使用
 
CFLAGS := -Wall -O2 -g                  #编译器参数
CFLAGS += -I $(shell pwd)/hal/include   #指定编译器头文件(根据实际项目手动修改)
CFLAGS += -I $(shell pwd)/hal/target/template
CFLAGS += -I $(shell pwd)/OSAL/inc
CFLAGS += -I $(shell pwd)/User/inc
LDFLAGS :=                              #指定编译器链接库(根据实际项目手动修改)
export CFLAGS LDFLAGS                   #将定义的变量导出，方便其他makefile使用
TOPDIR := $(shell pwd)                  #获得当前程序的顶层目录
export TOPDIR                           #输出顶层目录
TARGET := OSAL_Example                     #编译后的程序名(根据实际项目手动修改)
#-------------------------顶层要生成的.o文件以及顶层文件夹(根据实际项目手动修改)------------------
objs-y += hal/
objs-y += OSAL/
objs-y += User/
#--------------------------------------------顶层的第一个规则(默认规则)-----------------------------------------
all :
	make -C ./ -f $(join $(TOPDIR), /Makefile.build) #进入当前目录，使用顶层的makefile.build进行编译
	$(CC) $(LDFLAGS) -o $(TARGET) built-in.o         #将编译好的built-in.o文件链接生成我们的目标文件
#------------------------------------------------顶层的清除规则-------------------------------------------------------
clean:
	rm -f $(shell find -name "*.o")              #删除所有的.o文件
	rm -f $(shell find -name "*.d")              #删除所有的.d文件
	rm -f $(TARGET)                              #删除目标文件
.PHONY:all clean
