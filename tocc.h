#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 可変長ベクタの構造体
// len == capacityのときにバッファが一杯
typedef struct {
    void **data;
    int capacity;
    int len;
} Vector;

void error(char *fmt, ...);
Vector *new_vector(void);
void vec_push(Vector *vec, void *elem);


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


Node *new_node(int ty, Node *lhs, Node *rhs);
Node *new_node_num(int val);
int consume(int ty);
Node *add();
Node *mul();
Node *term();
Node *parse(Vector *v);


void gen(Node *node);

// マップ型
typedef struct {
    Vector *keys;
    Vector *vals;
} Map;

Map *new_map();
void map_put(Map *map, char *key, void *val);
void *map_get(Map *map, char *key);


void expect(int line, int expected, int actual);
void runtest();



