#include "tocc.h"

// トークナイザ

// トークナイズした結果のトークン列はこの配列に保存する。
// 100個以上のトークンは来ないものとする
//Token tokens[100];

Token *add_token(Vector *v, int ty, char *input) {
    Token *t = malloc(sizeof(Token));
    t->ty = ty;
    t->input = input;
    vec_push(v, t);
    return(t);
}

// pが指している文字列をトークンに分割してtokensに保存する
Vector *tokenize(char *p) {
    Vector *v = new_vector();

    int i = 0;
    while (*p) {
        // 空白文字をスキップ
        if (isspace(*p)) {
            p++;
            continue;
        }

        // + or -
        if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' || *p == ')') {
            add_token(v, *p, p);
            i++;
            p++;
            continue;
        }

        // 数
        if (isdigit(*p)) {
            Token *t = add_token(v, TK_NUM, p);
            t->val = strtol(p, &p, 10);
            i++;
            continue;
        }

        fprintf(stderr, "トークナイズできません: %s\n", p);
        exit(1);
    }

    add_token(v, TK_EOF, p);
    return v;
}

