
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Client_tag{
    char *name;
    int zankou;
    struct Client_tag *next;
}Client;

Client *client_top;
void init(void){
    client_top = NULL;//初期化
}
void chop(char *str){//ナル文字の前に改行文字が入ってるので取り除く
    int i;
    for(i = 0; str[i] != '\n'; i++){
    ;
    }
    str[i] = '\0';
}
char *my_strdup(char *str){//strの値をretにコピーする
    char *ret;
    ret = malloc(strlen(str)+1);
    if(ret == NULL){
   	 fprintf(stderr,"my_strdup:メモリがいっぱいです");
    return ret;
    }
    strcpy(ret, str);
    return ret;
}
int y_strdup(int str){//strの値をretにコピーする
    int ret;
    ret = str;
    return ret;
}
void setClient(void){
    Client *new_client;
    Client *tail;
    char buf[512];
    printf("新規口座作成>");
    if(fgets(buf,512,stdin) ==NULL){
   	 fprintf(stderr,"setClient:エラー");
   	 return;
    }
    chop(buf);
    if((new_client=malloc(sizeof (Client))) == NULL){
   	 fprintf(stderr, "setClient:口座がいっぱいです");
   	 return;
    }
    new_client->name = my_strdup(buf);
    printf("%sさんの口座が作成されました \n", new_client->name);
    new_client->zankou = 0;
    new_client->next = NULL;
    if(client_top == NULL){
    client_top = new_client;
    return;
    }
    for(tail = client_top; tail->next != NULL; tail = tail->next){
   	 ;
    }
    tail->next = new_client;
}
void nyukin(void){
    char key[512];
    int maney;
    int f=0;
    Client *pos;
    if(client_top == NULL){
   	 printf("口座がありません\n");

   	 return;
    }
    printf("口座名と入金する金額を入力してください>");
    printf("口座名>");scanf("%s", key);
    for(pos = client_top; pos != NULL; pos =pos->next){
    f++;
   	 if(strcmp(key, pos->name)==0){//名前検索
   	 printf("入金額>");scanf("%d", &maney);
   		 pos->zankou=pos->zankou+maney;
   	 printf("入金が完了しました\n残高%d円\n", pos->zankou);
   		 return;
   	 }
    }
    printf("口座がありません");
}
void shukkin(void){
    char key[512];
    int maney;
    Client *pos;
    if(client_top == NULL){
   	 printf("口座がありません\n");

   	 return;
    }
    printf("口座名と出金する金額を入力してください>");
    printf("口座名>");scanf("%s", key);
    for(pos = client_top; pos != NULL; pos =pos->next){
   	 if(strcmp(key, pos->name)==0){
   		 printf("出金金額>");scanf("%d", &maney);
   		 if(pos->zankou < maney){//-にならないようにする
   		 printf("残高がありません");
   		 return;
   		 }
   		 pos->zankou=pos->zankou-maney;
   	 printf("出金が完了しました\n残高%d円\n", pos->zankou);
   		 return;
   	 }
    }
    printf("残高がありません");
}
void shoukai(void){//残高確認
    char key[512];
    Client *pos;
    if(client_top == NULL){
   	 printf("口座がありません\n");

   	 return;
    }
    printf("口座名を入力してください>");
    printf("口座名>");scanf("%s", key);
    for(pos = client_top; pos != NULL; pos =pos->next){
   	 if(strcmp(key, pos->name)==0){
   	 printf("残高%d円\n", pos->zankou);
   		 return;
   	 }
    printf("口座はありません\n");
    }
}
void kaiyaku(void){//口座を削除
    char key[512];
    Client *pos;
    Client *temp;
    if(client_top ==NULL){
   	 printf("口座がありません\n");
   	 return;
    }
    printf("削除する口座名を入力してください >");
    scanf("%s", key);
    if(strcmp(client_top->name,key)==0){
   	 temp=client_top;
   	 client_top=client_top->next;
   	 free(temp);
   	 printf("%sの口座を削除しました\n", key);
   	 return;
    }
    for(pos = client_top; pos->next != NULL; pos =pos->next){
   	 if(strcmp(key, pos->next->name)==0){
   		 temp=pos->next;
   		 pos->next =temp->next;
   		 free(temp);
   		 printf("%sの口座を削除しました\n", key);
   		 return;
   		 }
   	 }
    printf("%s様は見つかりませんでした\n", key);
}
void quit(void){
    Client *target;
    Client *temp;
    target = client_top;
    while(target != NULL){
   	 temp = target->next;
   	 free(target);
   	 target = temp;
      	}
    printf("プログラムを終了します.\n");
}
void kakikomi(void){//テキストに書き込み
    int i;
    Client *pos;
    FILE *fp;
    fp=fopen("ginkou.txt","w");
    for(pos = client_top; pos != NULL; pos =pos->next){
   	 fprintf(fp,"%s %d ", pos->name, pos->zankou);
    }
    fclose(fp);
}
void yomikomi(void){//テキスト読み込み
    FILE *fp;
    Client *new_client;
    Client *tail;
    char a[512];
    int b;
    char fname[]="Bank.txt";
    fp=fopen(fname,"r");
    
    if(fp==NULL){
   	 printf("本プログラムを実行されるのは初めてですね。\n");
		return;
		}
    else{
   	 while(fscanf(fp,"%s %d", a, &b)!= EOF){//ファイルの最後まで読み込む
   		 if((new_client = malloc(sizeof (Client))) == NULL){//メモリ確保
   			 fprintf(stderr,"メモリがありません");
   			 return;
   		 }
   		 
   		 new_client->name = my_strdup(a);
   		 new_client->zankou = b;
   		 new_client->next = NULL;
   		 if(client_top == NULL){
   			 client_top = new_client;
   		 }
   		 else {
   			 for(tail = client_top; tail->next != NULL; tail = tail->next){
   			 ;    
   			 }
   		 tail->next = new_client;
   		 }
   	 }    
    }    
    fclose(fp);
}
int main(void){
    int flag = 1;
    init();
    yomikomi();
    int command;
    while (flag){
   	 printf("新規口座(1) 入金(2) 出金(3) 残高照会(4) 口座解約(5) 終了(0)> ");
   	 scanf("%d", &command);
   	 getchar();
   	 switch (command) {
   		 case 1:
   		 setClient();
   		 break;
   		 case 2:
   		 nyukin();
   		 break;
   		 case 3:
   		 shukkin();
   		 break;
   		 case 4:
   		 shoukai();
   		 break;
   		 case 5:
   		 kaiyaku();
   		 break;
   		 case 0:
   		 kakikomi();
   		 quit();
   		 flag = 0;
   		 break;
   		 default:
   		 fprintf(stderr, "入力番号が間違っています\n");
   	 }
    }
    return EXIT_SUCCESS;
}


