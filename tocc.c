#include "tocc.h"


int main(int argc, char **argv) {
    if (argc == 1 || argc > 3) {
        fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    if (argc == 2 && !strcmp(argv[1], "-test")) {
        runtest();
        return 0;
    }

    if (argc == 3 && !strcmp(argv[1], "-token")) {
        Vector *tokens = tokenize(argv[2]);
        Token *t = tokens->data[0];
        printf("first token ty: %d\n", (t->ty));
        printf("first token val: %d\n", (t->val));
        return 0;
    }

    // トークナイズしてパースする
    Vector *tokens = tokenize(argv[1]);
    Node *node = parse(tokens);

    // アセンブリの前半部分を出力
    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    // 抽象構文木を下りながらコード生成
    gen(node);

    // スタックトップに式全体の値が残っているはずなので，
    // それをRAXにロードして関数からの返り値とする
    printf("  pop rax\n");
    printf("  ret\n");
    return 0;
}
