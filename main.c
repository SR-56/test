#include <stdio.h>
#include <string.h>

#define MAX_NUM (16+1)  // 登録文字上限
#define LIST_NUM 10 // 登録データ上限
typedef struct
{
    int id;
    unsigned char name[MAX_NUM];
    unsigned char mail[MAX_NUM];
    unsigned char call[MAX_NUM];

} ST_ADDRESS;

typedef enum
{
    E_MENU_ADD = 1,
    E_MENU_VIEW,
    E_MENU_DELETE,
    E_MENU_END
} E_MENU;

//プロトタイプ宣言
E_MENU MainMenu(void);
void Add(void);
void View(void);
void Delete(void);
int CharCheck(int);

ST_ADDRESS list[LIST_NUM];
unsigned char global_data_count = 0; // 登録データ数

void main()
{
    E_MENU select = E_MENU_ADD; // 選択番号

    while (select != E_MENU_END)
    {
        select = MainMenu();
        switch (select)
        {
        case E_MENU_ADD:
            Add();
            break;

        case E_MENU_VIEW:
            View();
            break;

        case E_MENU_DELETE:
            Delete();
            break;

        case E_MENU_END:
            break;
        }
    }
    return;
}

// ---------------MainMenu関数--------------
E_MENU MainMenu(void)
{
    E_MENU select = E_MENU_ADD;

    printf("------------------------------\n");
    printf("1.ADD\n2.VIEW\n3.DELETE\n4.END\n");
    printf("------------------------------\n");

    scanf("%d", &select);

    return select;
}

// ---------------Add関数--------------
void Add()
{
    unsigned char check[2] = {"y\n"};
    unsigned int i = 0;
    ST_ADDRESS tmp_list;
    memset(&tmp_list,0,sizeof(ST_ADDRESS));
    
    while (check[0] != 'n') // 「n」が入力されるまで継続
    {
        if (global_data_count == LIST_NUM)
        {
            printf("registration limit...!\n");
            break;
        }
        else
        {
            for (i = 0; i < LIST_NUM; i++)
            {
                if (list[i].id == 0) // 0なら空。データ入力可能
                {
                    list[i].id = i + 1;
                    break;
                }
                else
                {
                    continue;
                }
            }
            printf("name?(max16)-->");
            scanf("%s", list[i].name);
            if (CharCheck(strlen(list[i].name)) == 0)
                continue;
            printf("mail?(max16)-->");
            scanf("%s", list[i].mail);
            if (CharCheck(strlen(list[i].mail)) == 0)
                continue;
            printf("phonenumber?(max16)-->");
            scanf("%s", list[i].call);
            if (CharCheck(strlen(list[i].call)) == 0)
                continue;
            // 登録データ数が入っている
            global_data_count++;
            printf("continue?(y/n):");
            scanf("%1s", check);
            printf("\n");
        }
    }
}

// ---------------View関数--------------
void View()
{
    unsigned int i = 0;
    if (global_data_count == 0)
        printf("there is no data...\n\n");
    for (i = 0; i < 10; i++)
    { // 登録データ数分表示する
        if (list[i].id == 0)
            continue;
        printf(
            "-----\nid:%d:\nname:%s\nmail:%s\nphonenumber:%s\n",
            list[i].id, list[i].name, list[i].mail, list[i].call);
    }
}

// ---------------Delete関数--------------

void Delete()
{
    unsigned char check[2] = {'y'};
    unsigned int i = 0;
    unsigned int del = 1;

    while (check[0] != 'n')
    {
        if (global_data_count == 0)
        {
            printf("there is no data...\n\n");
            break;
        }
        else
        {
            printf("delete data id?(1～10)-->");
            scanf("%d", &del);
            if (list[del - 1].id == 0)
            {
                printf("there is no data...\n\n");
                break;
            }
            list[del - 1].id = 0;
            global_data_count--;
            printf("continue?(y/n):");
            scanf("%1s", check);
        }
    }
}

// ---------------Charcheck関数--------------(文字数超を検知する)
//(分割した時static付ける？)
int CharCheck(int char_num)
{
    unsigned int i = 0;
    if (char_num > MAX_NUM - 1)
    {
        printf("characters over...(max16)\n");
        list[i].id = '\0';
        list[i].name[0] = '\0';
        return 0;
    }
    else
    {
        return 1;
    }
}

/*
雑メモ

★コメント以外は全て英語
→ファイル名や変数、printf内も。
→環境により文字化けしてしまう。
▼一般的な命名規則を覚え、変数名や構造体名を付ける。
▼型付、修飾子は必ずつけよう。
unsigned ＝　符号無し
signed ＝　符号有り

int 4バイト
char メモリでは1バイト
符号無し＝0～255までの数値
符号有り＝－127～128までの数値
→文字というルールはない。数値も入れられる(数字じゃないよ)
→unsigned修飾子付けること。全てのコンパイラで同じ動作をさせるため。

255に1を加えると...
0になる。xは8ビットしかなく、オーバーフローし、8ビット分0になる為。
→オーバーフローした分は他の変数領域に保存されてしまう。
→予期しない書き換えが発生する。

▼マジックナンバーを減らしたい。同じ値は定数で使いまわしたい。
消費税の例。同じ数値を書き換えるなら、定数を変えるだけにしたい。
可読性にもつながる。

▼何故配列は、必要数+１？
printfの仕様として「null文字」まで読み込む。(scanfも同様)
またenterを押すと、必ず「null文字」が格納される

▼配列内の文字の判定について
文字列の場合「””」
文字(単体)の場合「’’」でくくる。

▼listは定数化しよう
配列の0の初期化は「list = {}」でもできる

▼変数は初期値を入れよう
→enter等予期せぬ操作の時、予期せぬ動作をさせないため。

▼整数値を扱う際、255以下の値を扱う時はchar型でいいよ。

▼scanfの仕様
%dで受け取っても「文字」として受け取られる。数字としては受け取ってくれない。
%sで受け取る。

▼次の課題
現在の処理を全て関数化する。　済
マジックナンバーを消す。　済

ADD処理が正しく動いていない？　済
VIEW処理が正しく動いていない？　済

命名規則に従っていない箇所　済
定数値を分かりやすく　済
関数の型　済
構造体の型定義(命名規則？)　済
グローバル変数　済
→様々な関数で使いまわす変数をグローバル変数にした。
そうすると、いちいちローカル変数として定義しなくていいと思った。
しかし推奨されないらしいので、データカウント数のみグローバル変数にした。

入出力機能とデータ管理機能とで、関数をファイル分割。
→関数をファイルで分ければいい？
→ファイル間のデータの受け渡し方法がわからない
→各定義をどこですればいいか分からない。(同じ定義を2つのファイルでする？)
・ヘッダファイルとソースファイルの2つを用意する
・メインのファイルにて、サブのヘッダファイルをインクルードすると、
メインにてサブのソースファイル内の関数が使用できる。
・ヘッダファイルはマクロ定義→型定義→プロトタイプ宣言の順に記述。
・ソースファイルはヘッダインクルード→マクロ定義→型定義→プロトタイプ宣言
→グローバル変数定義→関数定義の順に記述。

*/