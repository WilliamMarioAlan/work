#include <string.h>
#include "scanner.h"

typedef struct {
    // 一开始它应该指向源代码字符串的起始位置
    // 当开始扫描一个新的Token时，这个指针指向Token的第一个字符。
  	const char* start;
    // Token中下一个要读取的字符
  	const char* current;
    // 当前读取的行
  	int line;
} Scanner;  // 这个Scanner要贴图 然后还要画图演示并贴图

// 全局变量结构体对象
Scanner scanner;

void initScanner(const char* source) { 
	// 初始化全局变量scanner
    scanner.start = source; // 都可以设置指向源代码字符串的起始位置
    scanner.current = source;   
    scanner.line = 1;
}

// 下面我给大家提供了很多会用到的辅助函数,建议使用

// 检查字符c是否是字母或下划线。
static bool isAlpha(char c) {
	return (c >= 'a' && c <= 'z') ||
      	   (c >= 'A' && c <= 'Z') ||
      	    c == '_'; 
}

// 检查字符c是否是数字。
static bool isDigit(char c) {
  	return c >= '0' && c <= '9';
}

// 检查下一个字符位置是不是源代码末尾
static bool isAtEnd() {
  	return *scanner.current == '\0';
}

// 返回下一个字符,curr前进一位
static char advance() {
  	return *scanner.current++;
}

// 查看下一个字符
static char peek() {
  	return *scanner.current;
}

// 如果下一个字符位置不是源代码末尾, 那就返回下下一个字符
static char peekNext() {
  	if (isAtEnd()) return '\0';
  	return *(scanner.current + 1);
}

// 检查下一个字符是否为期望的字符
static bool match(char expected) {
  	if (isAtEnd()) return false;    // 如果下一个字符是文件末尾,返回false
  	if (peek() != expected) return false;   // 瞥一眼下一个字符,如果不是,返回false
  	scanner.current++;  // 在返回true之前, 将curr向后移动一位
  	return true;
}

// 根据传入的TokenType类型来返回一个Token
static Token makeToken(TokenType type) {
  	Token token;
  	token.type = type;
  	token.start = scanner.start;    // sc.start是当前Token的第一个字符
    // 当此Token结束时,也就是处理它最后一个字符时,curr指向该Token的后一个字节,此时指针相减就是Token的字符串长度
  	token.length = (int)(scanner.current - scanner.start);
  	token.line = scanner.line;  // 更新line
  	return token;
}

// 当遇到不可识别的字符时,就返回一个TOKEN_ERROR类型的Token
static Token errorToken(const char* message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}
// 看完这些辅助函数后, 可以先去看另一个.c文件需要实现的核心函数scanToken

static void skipWhitespace() {
  	// 跳过空白字符: ' ', '\r', '\t', '\n'和注释
  	// 注释以'//'开头, 一直到行尾
  	// 注意更新scanner.line！
    /*
    * 思路:
    * 不知道究竟有多少个 所以要死循环
    * 瞥一眼下一个字符然后switch判断
    * 碰到空格,制表,回车就advance前进..
    * 如果碰到换行 那就sc.line++再前进
    * 注释:
    * 如果下一个字符是/,那就再瞥一眼下下个字符,如果还是/,那就是注释
    * 此时要把一整行都要跳过,用while循环
    * 结束:
    * 只要不是下一个字符不是上面提出来的几个,就结束死循环
    */
    for (;;) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                scanner.line++;
                advance();
                break;
            case '/':
                if (peekNext() == '/') {
                    // 跳过一整行注释
                    while (!isAtEnd() && peek() != '\n') advance();
                } else {
                    return ;
                }
                break;
            default:
                return ;
        }
    }
}
// 用于检查当前扫描的Token的类型是不是type 如果是就返回type
static TokenType checkKeyword(int start, int length, const char* rest, TokenType type) {
    /*
    * 不要忘了sc.start指向token的开头
    * start: 待检查的字符序列的起点
    * length: 待检查的字符序列的长度
    * rest: 待检查的Token的剩余部分(因为开头第一个字符总是switch检测，该函数检测的总是剩下的)
    *      比如"break" switch判断了b，该函数就用来检测"reak"
    * type：如果匹配成功，返回的 TokenType。比如如果检测"break"，这里就填TOKEN_BREAK
    */
    // 检查从start位置开始，长度为length的字符串是否与给定的rest字符串相匹配
    // 先判断长度是否一致 再判断内容
    if (scanner.current - scanner.start == start + length &&
        memcmp(scanner.start + start, rest, length) == 0) {
        return type;
    }
    return TOKEN_IDENTIFIER;
}

static TokenType identifierType() {
    // 确定identifier类型主要有两种方式：
    // 1. 将所有的关键字放入哈希表中，然后查表确认 
    // Key-Value 就是"关键字-TokenType" 可以做 但存在额外内存占用且效率不如下一个方式好
    // 2. 将所有的关键字放入Trie树(读踹，字典查找树)中，然后查表确认
    // Trie树的方式不管是空间上还是时间上都优于哈希表的方式
    char c = scanner.start[0];
    // 用switch...switch...if组合构建逻辑上的trie树
    switch (c) {
        // keywords
        case 'b': return checkKeyword(1, 4, "reak", TOKEN_BREAK);
        case 'c': {
            int len = scanner.current - scanner.start;
            if (len > 1) {
                switch (scanner.start[1]) {
                    case 'a': return checkKeyword(2, 2, "se", TOKEN_CASE);
                    case 'h': return checkKeyword(2, 2, "ar", TOKEN_CHAR);
                    case 'o':
                        if (len > 3 && scanner.start[2] =='n') {
                            switch (scanner.start[3]) {
                                case 's': return checkKeyword(4, 1, "t", TOKEN_CONST);
                                case 't': return checkKeyword(4, 4, "inue", TOKEN_CONTINUE);
                            }
                        }
                }
            }
            break;
        }
        case 'd': {
            int len = scanner.current - scanner.start;
            if (len > 1) {
                switch (scanner.start[1]) {
                    case 'e': return checkKeyword(2, 5, "fault", TOKEN_DEFAULT);
                    case 'o': 
                        if (len == 2) return TOKEN_DO;
                        else return checkKeyword(2, 4, "uble", TOKEN_DOUBLE);
                }
            }
            break;
        }
        case 'e': {
            int len = scanner.current - scanner.start;
            if (len > 1) {
                switch (scanner.start[1]) {
                    case 'l': return checkKeyword(2, 2, "se", TOKEN_ELSE);
                    case 'n': return checkKeyword(2, 2, "um", TOKEN_ENUM);
                }
            }
            break;
        }
        case 'f': {
            int len = scanner.current - scanner.start;
            if (len > 1) {
                switch (scanner.start[1]) {
                    case 'l': return checkKeyword(2, 3, "oat", TOKEN_FLOAT);
                    case 'o': return checkKeyword(2, 1, "r", TOKEN_FOR);
                }
            }
            break;
        }
        case 'g': return checkKeyword(1, 3, "oto", TOKEN_GOTO);
        case 'i': {
            int len = scanner.current - scanner.start;
            if (len > 1) {
                switch (scanner.start[1]) {
                    case 'f': return checkKeyword(2, 0, "", TOKEN_IF);
                    case 'n': return checkKeyword(2, 1, "t", TOKEN_INT);
                }
            }
            break;
        }
        case 'l': return checkKeyword(1, 3, "ong", TOKEN_LONG);
        case 'r': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
        case 's': {
            int len = scanner.current - scanner.start;
            if (len > 1) {
                switch (scanner.start[1]) {
                    case 'h': return checkKeyword(2, 3, "ort", TOKEN_SHORT); 
                    case 'i': 
                        if (len > 2) {
                            switch (scanner.start[2]) {
                                case 'g': return checkKeyword(3, 3, "ned", TOKEN_SIGNED);
                                case 'z': return checkKeyword(3, 3, "eof", TOKEN_SIZEOF);
                            }
                        }
                        break;
                    case 't': return checkKeyword(2, 4, "ruct", TOKEN_STRUCT);
                    case 'w': return checkKeyword(2, 4, "itch", TOKEN_SWITCH);
                }
            }
            break;
        }
        case 't': return checkKeyword(1, 6, "ypedef", TOKEN_TYPEDEF);
        case 'u': {
            int len = scanner.current - scanner.start;
            if (len > 2 && scanner.start[1] == 'n') {
                switch (scanner.start[2]) {
                    case 'i': return checkKeyword(3, 2, "on", TOKEN_UNION);
                    case 's': return checkKeyword(3, 5, "igned", TOKEN_UNSIGNED);
                }
            }
            break;
        }
        case 'v': return checkKeyword(1, 3, "oid", TOKEN_VOID);
        case 'w': return checkKeyword(1, 4, "hile", TOKEN_WHILE);
    }

    // 没有在上面switch中返回，那肯定不是关键字，于是就是标识符
    return TOKEN_IDENTIFIER;
}

// 当前Token的开头是下划线或字母判断它是不是标识符Token
static Token identifier() {
    // 判断下一个字符是不是 字母 下划线 数字
    while (isAlpha(peek()) || isDigit(peek())) {
        advance();  // 继续前进看下一个字符 直到碰到下一个字符不是字母 下划线 以及数字 结束Token
    }
    // 这个函数的意思是: 只要读到字母或下划线开头的Token我们就进入标识符模式
    // 然后一直找到此Token的末尾
    // 但代码运行到这里还不确定Token是标识符还是关键字, 因为它可能是break, var, goto, max_val...
    // 于是执行identifierType()函数，它是用来确定Token类型的
    return makeToken(identifierType());
}

static Token number() {
    // 简单起见，我们将NUMBER的规则定义如下:
    // 1. NUMBER可以包含数字和最多一个'.'号
    // 2. '.'号前面要有数字
    // 3. '.'号后面也要有数字
    // 这些都是合法的NUMBER: 123, 3.14
    // 这些都是不合法的NUMBER: 123., .14(虽然在C语言中合法)
    // 这个过程要不断的前进跳过所有的数字,
    // 比如数字123.456 最终要保证sc.start指向1,curr指向6后面第一个非数字字符
    while (isDigit(peek())) advance();

    // 查找有无小数部分
    if (peek() == '.' && isDigit(peekNext())) {
        // 跳过小数点
        advance();
        while (isDigit(peek())) advance();
    }
    
    return makeToken(TOKEN_NUMBER);
}

static Token string() {
 	// 字符串以"开头，以"结尾，而且不能跨行
    // 为了简化工作量
    // 如果下一个字符不是末尾也不是双引号，全部跳过(curr可以记录长度，不用担心)
    while (!isAtEnd() && peek() != '"') {
        if (peek() == '\n') {
            return errorToken("Not support multi-line string.");
        }
        advance();
    }

    if (isAtEnd()) return errorToken("Unterminated string.");

    // The closing quote.
    advance();
    return makeToken(TOKEN_STRING);
}

static Token character() {
    // 字符'开头，以'结尾，而且不能跨行
    // 如果下一个字符不是末尾也不是单引号，全部跳过(curr可以记录长度，不用担心)
    // 这两个函数不能说一模一样，也是几乎一样
    while (!isAtEnd() && peek() != '\'') {
        if (peek() == '\n') {
            return errorToken("Not support multi-line character.");
        }
        advance();
    }
    if (isAtEnd()) return errorToken("Unterminated character.");

    // The closing single-quote.
    advance();
    return makeToken(TOKEN_CHARACTER);
}

Token scanToken() {
  	// 跳过前置空白字符和注释
  	skipWhitespace();
  	// 记录下一个Token的起始位置
  	scanner.start = scanner.current;    // 在skipWhitespace中,瞥到下一个字符非空白和注释内容,就返回了
  	
    // 如果下一个字符就是末尾,那就返回TOKEN_EOF,TOKEN_EOF打印的效果就是空字符
  	if (isAtEnd()) return makeToken(TOKEN_EOF); 
  	
    // 如果下一个字符还不是末尾,那就返回下一个字符,此字符就是当前Token的首字符
    // 并且此时curr向前移动一个字节
  	char c = advance();

    // 如果当前字符是字母或下划线 就执行identifier 判断是不是标识符
  	if (isAlpha(c)) return identifier();
    // 如果当前字符是数字 就执行number判断是不是数字(字面值)
  	if (isDigit(c)) return number();
  	
    // 如果当前字符不是字母或下划线以及数字,那就判断switch判断它
  	switch (c) {
        // 处理单字符Token 非常简单 我虽然只给你写了一个 但还有啥区别呢？
      	case '(': return makeToken(TOKEN_LEFT_PAREN);
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case '[': return makeToken(TOKEN_LEFT_BRACKET);
        case ']': return makeToken(TOKEN_RIGHT_BRACKET);
        case '{': return makeToken(TOKEN_LEFT_BRACE);
        case '}': return makeToken(TOKEN_RIGHT_BRACE);
        case ',': return makeToken(TOKEN_COMMA);
        case '.': return makeToken(TOKEN_DOT);
        case ';': return makeToken(TOKEN_SEMICOLON);
        case '~': return makeToken(TOKEN_TILDE);

        // 可单可双字符的Token处理会稍微复杂一点,但不多
        // 如果当前字符是+号
    	case '+':
            // 如果下一个字符也是+,那就生产++双字符Token返回
            if (match('+')) return makeToken(TOKEN_PLUS_PLUS);
            // 如果下一个字符是=,那就生产+=双字符Token返回
            else if (match('=')) return makeToken(TOKEN_PLUS_EQUAL);
            // 如果上面都不是,说明就是单字符+ Token
            else return makeToken(TOKEN_PLUS);
        case '-':
            // ......

        // 多字符Token处理,上面已经处理过标识符和数字了 
       	case '"': return string();  // 如果当前字符是双引号,那就解析出字符串Token返回
        case '\'': return character();  // 如果当前字符是单引号,那就解析出字符Token返回
    }
    
    // 如果读到的字符不在上面的所有之列,那就无法失败,制造一个errorToken
    // 比如代码中的#(预处理阶段就没了) $(C语言不用该字符) 注释中的中文
    return errorToken("Unexpected character.");

    // 接下来看一下 string和character两个函数
}
