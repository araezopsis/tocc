#include "tocc.h"

// 再帰下降パーザ

//int pos = 0;

int pos;
Token *t;
Vector *tokens;

Node *new_node(int ty, Node *lhs, Node *rhs) {
    Node *node = malloc(sizeof(Node));
    node->ty = ty;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node *new_node_num(int val) {
    Node *node = malloc(sizeof(Node));
    node->ty = ND_NUM;
    node->val = val;
    return node;
}

int consume(int ty) {
    Token *t = tokens->data[pos];
    if (t->ty != ty)
        return 0;
    pos++;
    return 1;
}

Node *add() {
    Node *node = mul();

    for (;;) {
        if (consume('+'))
            node = new_node('+', node, mul());
        else if (consume('-'))
            node = new_node('-', node, mul());
        else
            return node;
    }
}

Node *mul() {
    Node *node = term();

    for (;;) {
        if (consume('*'))
            node = new_node('*', node, term());
        else if (consume('/'))
            node = new_node('/', node, term());
        else
            return node;
    }
}

Node *term() {
    Token *t = tokens->data[pos];
    if (consume('(')) {
        Node *node = add();
        if (!consume(')'))
            error("開きカッコに対応する閉じカッコがありません: %s", t->input);
        return node;
    }

    //if (t->ty == TK_NUM){
    if (consume(TK_NUM)){
        //pos++;
        return new_node_num(t->val);
        //printf("im here\n");
    }

    error("数値でも開きカッコでもないトークンです: %s", t->input);
}

Node *parse(Vector *v) {
    tokens = v;
    pos = 0;
    return add();
    //return new_node_num(1);
}
