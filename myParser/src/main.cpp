#include "func.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "scanner.h"

#define SQARE(x) ((x) * (x))

using namespace std;
// 该函数表示对传入的文件路径名的字符串进行处理
static void runFile(const char* path);
// main.c中的核心逻辑
static void run(const char* source);
// repl是"read evaluate print loop"的缩写
// repl 函数定义了一个交互式的读取-求值-打印循环（REPL）逻辑
// 它允许用户输入源代码行，逐行进行词法分析，并打印分析结果
// 也就是说启动时没有主动给出一个命令行参数表示文件路径的话,那么就进行交互式界面进行词法分析
static void repl();
static char* readFile(const char* path);

/*
* 主函数支持操作系统传递命令行参数
* 然后通过判断参数的个数:
* 1.如果没有主动传入参数(argc=1),因为第一个参数总会传入一个当前可执行文件的目录作为命令行参数
* 此时执行repl函数
* 2.如果传递了一个参数(argc=2),说明传递了一个参数,将传递的参数视为某个源代码的路径
* 然后调用runFile函数,传入该源代码文件的路径,处理源文件
*/
int main(int argc, const char* argv[]) {
  	if (argc == 1) {
      	repl();
    } else if (argc == 2) {
      	runFile(argv[1]);
    } else {
        // 如果主动传入超过一个命令行参数.即参数传递有误,错误处理
        // 告诉用户正确的使用函数的方式
      	fprintf(stderr, "Usage: scanner [path]\n");
      	exit(1);
    }
  	return 0;
}


// main.c中的核心逻辑
static void run(const char* source) {
    // 初始化词法分析器，准备对输入的源代码进行词法分析。
    initScanner(source);
    // 下面就把执行结果 贴图 然后再讲解 还需要把结构体贴在一起

    int line = -1;  // 用于记录当前处理的行号,-1表示还未开始解析
    for (;;) {  // 死循环
        Token token = scanToken();  // 获取下一个TOKEN
        
        // 此TOKEN的行数和之前的TOKEN行数不同,也就是读到代码换行了
        // 于是打印效果要更改一下,每一行代码中的第一个TOKEN打印效果就是先打印行数
        if (token.line != line) {   
            printf("%4d ", token.line); // %4d 会打印4个宽度的整数,不够会在前面补空格,这是为了格式美观
            line = token.line;  // 更新line
        } else {
            // 如果TOKEN是同一行代码中的,就打印竖线(替代了line),这同样是为了美观
            printf("   | ");
        }
        // 注意前面始终都没有换行,所以下面的内容还是在同一行
        // 这里一共有74个不同的枚举值,所以用%2d打印是足够的
        /*
        * 不能用%s,因为它会打印整个字符串,也就是碰到空字符才结束打印,这样就会打印到结束
        * 为什么是%.*s
        * 首先"."在这里和"%.2f"当中的"."意思是一样的,浮点数表示小数点后面的保留位数
        * 在非浮点数的情况下,其实表示的是打印的宽度
        * 如果这里写"%.10s" 就表示打印10个长度的字符串
        * 但这里长度很明显不能在编译时期确定 必须运行时期确定
        * 于是就用".*s" 其中"*"表示的含义是从函数后面的传参中读取长度
        * 
        * 所以整体的打印效果是打印从 token.start 开始、长度为 token.length 的字符串。
        * token.start表示这个TOKEN在源代码中的起始位置
        */
        printf("%2d '%.*s'\n", token.type, token.length, token.start);

        if (token.type == TOKEN_EOF) break;     // 读到TOKEN_EOF结束循环
    }
}

// repl是"read evaluate print loop"的缩写
// repl 函数定义了一个交互式的读取-求值-打印循环（REPL）逻辑
// 它允许用户输入源代码行，逐行进行词法分析，并打印分析结果
// 也就是说启动时没有主动给出一个命令行参数表示文件路径的话,那么就进行交互式界面进行词法分析
static void repl() {
    /*
    * 这个过程无非就是从键盘录入接收一整行的数据
    * 而且应该是一个死循环接收键盘录入
    * 只有确定读到了末尾没有下一行了 才会停止接收录入
    * 所以这里应该用fgets函数（不能用fget因为它不安全）
    * repl函数最终要调用run函数
    */
    char line[1024];
    for (;;) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }
        run(line);
    }
}

static char* readFile(const char* path) {
	// 用户输入文件名，将整个文件的内容读入内存，并在末尾添加'\0'
  	// 注意: 这里应该使用动态内存分配，因此应该事先确定文件的大小。

    // 打开文件
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(1);
    }

    // 获取文件大小并倒带
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    // 动态内存分配字符数组,长度是文件大小 + 1
    char* buffer = (char*) malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(1);
    }
    // 利用fread函数一次性将file_size大小的数据读到字符数组中
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(1);
    }
    // 不要忘记末尾加空字符
    buffer[bytesRead] = '\0';
    // 关闭流
    fclose(file);
    return buffer;
}

 
static void runFile(const char* path) {
  	// 处理'.c'文件:用户输入文件名，分析整个文件，并将结果输出
    // 这个代码非常简单，我帮你直接写好
    // 会调用上面的readFile函数，根据文件路径名生成一个包含文件全部字符信息的字符串
    char* source = readFile(path);

    // 调用run函数处理源文件生成的字符串
    run(source);
    // 及时释放资源
    free(source);
    // 下面我们先看一下readFile函数的实现
}
