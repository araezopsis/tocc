#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




// トークンの型を表す値
enum {
    TK_NUM = 256, // 整数トークン
    TK_EOF,       // 入力の終わりを表すトークン
};

// トークンの型
typedef struct {
    int ty;       // トークンの型
    int val;      // tyがTK_NUMの場合，その数値
    char *input;  // トークン文字列（エラーメッセージ用）
} Token;




enum {
    ND_NUM = 256,  // 整数のノードの型
};

// 抽象構文木のノードの型
typedef struct Node {
    int ty;           // 演算子かND_NUM
    struct Node *lhs; // 左辺 (left-hand side)
    struct Node *rhs; // 右辺 (right-hand side)
    int val;          // tyがND_NUMの場合のみ使う
} Node;



void gen(Node *node);
