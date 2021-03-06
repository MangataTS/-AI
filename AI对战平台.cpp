#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

//----------------------分割线 ------------------------------
//Mangata的AI 

const int N = 15;

int bord[N][N];//  0表示当前为空，1表示黑子，2表示白子
int ai_ = 1;//ai_ = 1 表示的是AI先手
int s0;
bool IS_END = false; 

int dx[8] = {0,-1,-1,-1,0,1,1,1};
int dy[8] = {-1,-1,0,1,1,1,0,-1};

void init() {
    printf("输入1或者2进行选择\n1，AI执黑先行\n2，玩家执黑先行\n");
    int s;
    scanf("%d", &s);
    if (s != 1 && s != 2)return init();
    if(s == 1) ai_ = 1;
    else ai_ = 0;
    for(int i = 0;i < N; ++i)
        for(int j = 0;j < N; ++j) bord[i][j] = 0;
    IS_END = false;
}

bool is_inbord(int x,int y) {
    if(x < 0 || x >= N || y < 0 || y >= N) return false;
    return true;
}

bool can_luozi(int x,int y) {
    if(!is_inbord(x,y)) return false;
    if(bord[x][y] != 0) return false;
    return true;
}

bool issame(int x,int y,int k) {
    if(!is_inbord(x,y)) return false;
    return bord[x][y] == k || bord[x][y] + k == 0;
}

bool sum_num_of_same(int x,int y,int k) {
    int i = x + dx[k],j = y + dy[k];
    int sum = 0;
    int color = bord[x][y];
    if(color == 0) return 0; //如果当前点为空直接返回0
    if(issame(i,j,color)) sum++,i+=dx[k],j+=dy[k];
    return sum;
}

bool is_end(int x,int y) {
    for(int k = 0;k < 4; ++k)
        if(sum_num_of_same(x,y,k) + sum_num_of_same(x,y,k+4) >= 4) IS_END = true;
    return IS_END; //不考虑禁手
}

int live3(int x,int y) {//计算[x、y]点落子成活三个数
    int key = bord[x][y],sum = 0;
    for(int k = 0,i = 1;k < 4; ++k) {//四个方向寻找活三
        int loc = 1;
        int fg = 2;//表示能构成活三的可能
        //正方向找过去
        for(i = 1;issame(x + dx[k] * i,y + dy[k] * i,bord[x][y]); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//如果当前位置不是空位就continue
        i++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一
        //反方向找过去
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,bord[x][y]); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//如果当前位置不是空位就continue
        i++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一
        if(loc == 3 && fg > 0) //构成活三
            sum++;
    }
    return sum;
}

int live4(int x,int y) {//落子成活四的个数
    int sum = 0;
    for(int k = 0,i = 1;k < 4;++k) {
        int loc = 1;
        for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,bord[x][y]); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//如果当前位置不是空位就continue

        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,bord[x][y]); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//如果当前位置不是空位就continue

        if(loc == 4) sum++;
    }
    return sum;
}

int cheng5(int x,int y) {//落子成5的个数
    int sum = 0;
    for(int k = 0,i = 1;k < 4;++k) {
        int loc = 1;
        for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,bord[x][y]); ++i) loc++;
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,bord[x][y]); --i) loc++;
        if(loc == 5) sum++;
    }
    return sum;
}

int rush4(int x,int y) {//落子成冲4的个数
    int sum = 0;
    for(int k = 0,i = 1;k < 4; ++k) {//四个方向寻找活三
        int loc = 1;
        int fg = 2;//表示能构成活三的可能
        //正方向找过去
        for(i = 1;issame(x + dx[k] * i,y + dy[k] * i,bord[x][y]); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一
        //反方向找过去
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,bord[x][y]); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一

        if(loc == 4 && fg > 0) //构成活三
            sum++;
    }
    return sum;
}

void go(int x,int y,int color) {
    bord[x][y] = color;//落子
    if(is_end(x,y)) {
        if(ai_ == 1 && color == 1 || ai_ == 0 && color == 2) printf("AI胜利");
        else printf("玩家胜利");
    }
    printf("落子  x = %d, y = %d\n",x,y);
}

int fenshu(int x,int y) {
    //if(ban(x,y)) return 0;//如果是禁手返回0分
    if(is_end(x,y)) { //如果能直接结束游戏，那么直接返回最高权值
        return 10000;
    }
    int rating = live4(x,y) * 1000 + live3(x,y) * 500 + rush4(x,y) * 100;
    for(int i = 0;i < 8; ++i) if(can_luozi(x + dx[i],y + dy[i])) rating += 10;//查看当前落子的周围八个位置，如果能落子就加10分
    return rating;//返回计算分数
}

//目前的AI不考虑禁手

int AI_3(int kk,int color) {
    int loc_key = -100000,temp;
    for(int i = 0;i  < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue;
            bord[i][j] = color;
            temp = fenshu(i,j);
            if(temp == 0) {//避开无效点
                bord[i][j] = 0;
                continue;
            }
            if(temp  == 10000) {
                bord[i][j] = 0;
                return 10000;
            }
            bord[i][j] = 0;
            if(temp - kk * 2 > loc_key) { //第三层博弈树取极大值
                loc_key = temp - kk * 2;
            }
        }
    }
    return loc_key;
}//第三层AI

int AI_2(int color) {
    int loc_key = 100000,temp;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue; //不能落子
            bord[i][j] = color;
            temp = fenshu(i,j);
            if(temp == 0) {//避开无效点
                bord[i][j] = 0;
                continue;
            }
            if(temp == 10000) {//如果对于第二层找到了必胜点，那么返回负值
                bord[i][j] = 0;
                return -10000;
            }
            temp = AI_3(temp,3 - color);
            bord[i][j] = 0;
            if(temp < loc_key) loc_key = temp; //第二层博弈树取极小值
        }
    }
    return loc_key;
}//第二层AI

pair<int,int> AI_1(int color) {
    if(bord[7][7] == 0) return pair<int,int>(7,7); //如果天元没有落子，那么落子天元
    int loc_key = -100000,keyi,keyj,temp;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue;
            bord[i][j] = color;
            temp = fenshu(i,j);
            if(temp == 0) { //剪枝，避开无效点
                bord[i][j] = 0;
                continue;
            }
            if(temp == 10000) {
                bord[i][j] = 0;
                return pair<int, int>(i, j); //如果已经找到必胜点，那么直接返回当前的值
            }
            temp = AI_2(3 - color);
            bord[i][j] = 0;
            if(temp > loc_key) {//第一层博弈树取极大
                loc_key = temp;
                keyi = i,keyj = j;
            }
        }
    }
    printf("loc_key = %d,x = %d,y = %d\n",loc_key,keyi,keyj);
    return pair<int,int> (keyi,keyj);
}//第一层AI

//----------------------分割线 ------------------------------

typedef long double ll; 
int m,n;
char pan[15][15];
ll visx[15][15];
ll viso[15][15];
int f[]={-1,-1,-1, 0};//方向 \ | / — 
int g[]={-1, 0, 1,-1};
int CMcheck[5],Difficult,PRvis;
int special;
struct point
{
    int x,y;
}p;
//服务区 
void loading(int p);
int menu();
void funny();

//基本函数 
int pd(int x);
void Init();
void PR();
void PM();
void CM(int cn);
void get(int cn);
int check(int x,int y);
void win(char winner);
void CVis();
void Game();

//运算函数 
int CK(int i,int k,int j,int jcn,char x,int cn,int jc);
int ck(int i,int k,int j,char x,int cn);
ll BC(int i,int k,char X);
void jp(int i,int k,int j,int s[],ll &Q,ll &E,int &C,int p,char X);
void sl(int i,int k,int j,int C,int &c,char x); 
void BFS(int x,int y,char X,int key,ll up);


int main()
{
    srand((int)time(0));
    system("color");
    while(1)
    {
        int key=menu();
        system("cls");
        if(key==1)
        {
//            puts("【提示：在落子时输入两个负数坐标可立即开始新的一局嗷】\n\n输入格式为【数字空格数字】\n\n回车键确认 ~(￣▽￣)~\n");
//            getchar();
            Game();
        }
        else if(key==0)
        {
            puts("\n好吧，希望下次能与您切磋  *（￣︶￣）*\n");
            break;
        }
        else puts("请按格式输入确认进行游戏~   ~(￣▽￣)~  ");
    }
    return 0;
}

int menu()
{
    int choice;special=0;
    do
    {
        printf("\n\n\n\n\n开发者：弥攸——可以关注公众号:\033[32m 代码小帮手 \033[0m q(≧▽≦q)\n\n");
        printf("===========================\n");
        printf("||                       ||\n");
        printf("||      1.开始游戏       ||\n");
        printf("||                       ||\n");
        printf("||      0.结束游戏       ||\n");
        printf("||                       ||\n");
        printf("===========================\n");
        printf("请输入您的选择：");
        
        scanf("%d",&choice);
//        choice = 1;
        
        if(choice!=1&&choice!=0)funny();
    }while(choice!=1&&choice!=0);
    if(!choice)return 0;
    do
    {
        system("cls");
        printf("=========================================\n");
        printf("||                                     ||\n");
        printf("||   1.以 【左 上】 为（0，0）的棋盘   ||\n");
        printf("||        (先纵坐标，再横坐标）        ||\n");
        printf("||                                     ||\n");
        printf("||   2.以 【左 下】 为（0，0）的棋盘   ||\n");
        printf("||        (先横坐标，再纵坐标）        ||\n");
        printf("||                                     ||\n");
        printf("=========================================\n");
        printf("请您选择更习惯的棋盘：");
        PRvis = 1;
		//scanf("%d",&PRvis);
        if(PRvis!=1&&PRvis!=2)funny();
    }while(PRvis!=1&&PRvis!=2);
    
    do
    {
        system("cls");
        printf("请您继续选择棋盘规格N 【5<=N<=15】：");
        //scanf("%d",&m);
		m = 15;
		n=m;
        if(m>15||m<5)
        {
            puts("\n不符合规格嗷，请重新输入 ~(￣▽￣)~ ");
            Sleep(2000);
            system("cls");
        }
    }while(m>15||m<5);
    
    do
    {
        system("cls");
        printf("=================================\n");
        printf("||                             ||\n");
        printf("||       1.无心插柳柳成荫      ||\n");
        printf("||                             ||\n");
        printf("||       2.简单套路你能行      ||\n");
        printf("||                             ||\n");
        printf("||       3.唯有套路得我心      ||\n");
        printf("||                             ||\n");
        printf("||       4.人家叫我分水岭      ||\n");
        printf("||                             ||\n");
        printf("||       5.我若先手我无敌      ||\n");
        printf("||                             ||\n");
        printf("||       6.我就先手试试看      ||\n");
        printf("||                             ||\n");
        printf("=================================\n");
        printf("请选择难度：");
        scanf("%d",&Difficult);
        if(Difficult == 6) ai_ = 0,s0 = 2;
        else ai_ = 1,s0 = 1;
        getchar();
        if(Difficult<1||Difficult>6)funny();
    }while(Difficult<1||Difficult>6);
    return 1;
}

void funny()
{
    puts("");
    char s[99]={"看不见没有那个选项嘛？ 不要对我有其他想法  我只是个没有感情的杀手"};
    for(int i=0;s[i];++i)
    {
        printf("%c",s[i]);
        Sleep(50);
        if(i==21)Sleep(400);
        if(i==40)Sleep(400);
    }
    Sleep(600);
    puts("   （￣へ￣） ");
    Sleep(1000);
    puts("\n别搞事情嗷  (￣▽￣) ");
    Sleep(2000);
    system("cls");
    return ;
}

void Init()
{
    for(int i=0;i<m;++i)
    for(int k=0;k<n;++k)
    {
        visx[i][k]=0;
        viso[i][k]=0;
        pan[i][k]=' ';
    }
}

int pd(int x)
{
    if(x<0||x>=m)return 0;
    return 1;
}

void swap()
{
    int t=p.y;
    p.y=p.x;
    p.x=m-t-1;
}

void PR()
{

    system("cls");
    puts("\n目前棋盘：\n");
    int version=PRvis;
    if(version==1)
    {
        //以左上为00的坐标 
        printf("    ");
        for(int k=0;k<n;++k)
        printf("  %2d ",k);
        puts(""); 
        for(int i=0;i<m;++i)
        {
            printf("    ");
            for(int k=0;k<n;++k)
            printf(" ----"); 
            puts("");
            
            for(int k=0;k<n;++k)
            {
                if(!k)printf("%2d：|",i);
                if(i==p.x&&k==p.y)
                {
                    printf("  ");
                    printf("\033[32m%c\033[0m",pan[i][k]);
                    printf(" |");
                }
                else printf("  %c |",pan[i][k]);
            }
            puts("");
            if(i==m-1)
            {
                printf("    ");
                for(int k=0;k<n;++k)
                printf(" ----"); 
                puts("");
            }
        }
    }
    if(version==2)
    {
        //以左下为00的坐标
        for(int i=0;i<m;++i)
        {
            printf("    ");
            for(int k=0;k<n;++k)
            printf(" ----"); 
            puts("");
            
            for(int k=0;k<n;++k)
            {
                if(!k)printf("%2d：|",m-i-1);
                if(i==p.x&&k==p.y)
                {
                    printf("  ");
                    printf("\033[32m%c\033[0m",pan[i][k]);
                    printf(" |");
                }
                else printf("  %c |",pan[i][k]);
            }
            puts("");
            if(i==m-1)
            {
                printf("    ");
                for(int k=0;k<n;++k)
                printf(" ----"); 
                puts("");
            }
        }
        printf("    ");
        for(int k=0;k<n;++k)
        printf("  %2d ",k);
        puts("");  
    }
}
//--------------------------------------------------分割线 
// 这是是下棋的地方 
void PM()
{
    puts("该您下棋咯~~~ ");
    while(true)//~scanf("%d %d",&p.x,&p.y) 
    {
    	int color = 0;
    	if(ai_ == 1) color = 1;
    	else color = 2;
    	pair<int,int> ttt = AI_1(color);
    	go(ttt.first,ttt.second,color);
    	p.x = ttt.first;
    	p.y = ttt.second;
        if(p.x<0)
        {
            special=1;
            break;
        }
        if(PRvis==2)swap(); 
        if(!pd(p.x)||!pd(p.y))
        {
            puts("坐标超出范围，请重新输入 ~(￣▽￣)~");
            continue;
        }
        if(pan[p.x][p.y]!=' ')
        {
            printf("坐标已被占用，请重新输入 ~(￣▽￣)~\n");
            continue;
        }
        pan[p.x][p.y]='x';
        visx[p.x][p.y]=-1;
        viso[p.x][p.y]=-1;
        CVis();
        break;
    }
}
//--------------------------------------------------分割线 

void CM(int cn)
{
    get(cn);
    pan[p.x][p.y]='o';
    CVis();
}

void get(int cn)
{
    if(Difficult==1)
    {
        int ok=0;
        while(!ok)
        {
            p.x=rand()%m;
            p.y=rand()%n;
            if(pan[p.x][p.y]==' ')ok=1;
        }
    }
    else   //点数优先级
    { 
        ll maxx=0;
        ll maxo=-1;//取-1是为了防止后期全为零优势点（濒临和棋的情况）而乱取坐标 
        int a,b,c,d; 
        
        if(cn==m*n-2) 
        {
            do
            {
                c=rand()%(m/3)+m/3;
                d=rand()%(n/3)+n/3;
            }while(pan[c][d]!=' ');//第一点趋中优势
            p.x=c,p.y=d;
            return ;
        }
        
        for(int i=0;i<m;++i)
        for(int k=0;k<n;++k)
        {
            if(pan[i][k]==' ')
            {
                if(visx[i][k]>maxx)
                {
                    maxx=visx[i][k];
                    a=i;b=k;
                }
                if(viso[i][k]>maxo)
                {
                    maxo=viso[i][k]; 
                    c=i;d=k;
                }
            } 
        }
        if(maxo>=maxx)p.x=c,p.y=d;//优胜 
        else if(maxx>=2)//防胜 
        {
            p.x=a,p.y=b;
        }
        else p.x=c,p.y=d;//任意优势点（可优化）
        visx[p.x][p.y]=-1;
        viso[p.x][p.y]=-1; 
    }
}
//                        jcs数    x/o   上1/下0   jc延伸数 
int CK(int i,int k,int j,int jcn,char x,int cn,int jc) 
{
    //计算 空三或者 3连+1白 
    char dx;
    dx=x=='x'?'o':'x';
    
    if(cn)// 空3  和  3+1白 
    {//     当前方向有两个 且 边缘点是自己     或者    有三点  且     有一边是空白       反向点                              延伸点
        if((jcn==2&&pan[i+jc*f[j]][k+jc*g[j]]==x)||(jcn==3 && ( (dx!=pan[i-f[j]][k-g[j]]&&pd(i-f[j])&&pd(k-g[j])) || (dx!=pan[i+jc*f[j]][k+jc*g[j]]&&pd(i+jc*f[j])&&pd(k+jc*g[j])) )))return 1;
    }
    else
    {//         同上   
        if((jcn==2&&pan[i-jc*f[j]][k-jc*g[j]]==x)||(jcn==3 && ( (dx!=pan[i+f[j]][k+g[j]]&&pd(i+f[j])&&pd(k+g[j])) || (dx!=pan[i-jc*f[j]][k-jc*g[j]]&&pd(i-jc*f[j])&&pd(k-jc*g[j])) )))return 1;
    }
    return 0;
}
//                         x/o     模式/上/下 
int ck(int i,int k,int j,char x,int cn) 
{
    //计算 1+1和2 点情况 
    char dx;
    dx=x=='x'?'o':'x';
    int ls,lx,ys=0,yx=0,firs=0,firx=0;
    //    ls,lx分别记录 当前方向 的 向上向下两种情况 
    //    fir两种分别记录两向 
    for(ls=1;pan[i+ls*f[j]][k+ls*g[j]]!=dx&&pd(i+ls*f[j])&&pd(k+ls*g[j])&&ls<5;ls++)
    if(pan[i+ls*f[j]][k+ls*g[j]]==x&&ls<=3)
    {
        if(!firs)firs=ls;
        ys++;
    }
    for(lx=1;pan[i-lx*f[j]][k-lx*g[j]]!=dx&&pd(i-lx*f[j])&&pd(k-lx*g[j])&&lx<5;lx++)
    if(pan[i-lx*f[j]][k-lx*g[j]]==x&&lx<=3)
    {
        if(!firx)firx=lx;
        yx++;
    }
    if(!cn)//   1+1有效边的情况 
    { //   1+1点距大于3  或者 邻点不为空（lx/ls数字 （停止点） 必须不为邻点）  或者 长度被限制  或者  不属于延伸边 (没有自己）   
        if(firs+firx>3||firs+1==ls||firx+1==lx||ls+lx<7||ls<3||lx<3||ys!=1||yx!=1)return 0;
        return 1;
    }
    else//   2点有效边情况 
    {//    长度限制           点数要求                                        两边为空 
        if(ls+lx>6&&((cn==1&&ys>=2)||(cn==2&&yx>=2))&&pan[i+(ls-1)*f[j]][k+(ls-1)*g[j]]==' '&&pan[i-(lx-1)*f[j]][k-(lx-1)*g[j]]==' ')return 1;
        return 0;
    }
}
void jp(int i,int k,int j,int s[],ll &Q,ll &E,int &C,int p,char X) 
{
    //基本点判断   
    char x,dx;
    if(p)x='x',dx='o';
    else x='o',dx='x';
    int js=0;
    for(s[0]= f[j],s[1]= g[j];pd(i+s[0])&&pd(k+s[1])&&x==pan[i+s[0]][k+s[1]];s[0]+=f[j],s[1]+=g[j],Q++);
    for(s[2]=-f[j],s[3]=-g[j];pd(i+s[2])&&pd(k+s[3])&&x==pan[i+s[2]][k+s[3]];s[2]-=f[j],s[3]-=g[j],E++);
    //   3+1 或者2+2 限制点 
    if((Q==3&&E==1)||(E==3&&Q==1)||(Q>=2&&E>=2))Q=8,js=1;
    else
    {
        // 数学运算 
        if(Q>2)Q+=Q-2;
        if(E>2)E+=E-2;
        if(Q>0&&E>0&&pd(i+s[0])&&pd(i+s[2])&&pd(k+s[3])&&pd(k+s[1])&&' '==pan[i+s[2]][k+s[3]]&&' '==pan[i+s[0]][k+s[1]])Q++;//简单优化 
        Q+=E;
    }
    //   四连点强化 
    if(Q>=6)Q=8;//补上> :bug x_xxxx| 空点为7.0 
    // 2+1点强化 
    if(Q==4&&(E==1||E==2)&&pd(i+s[0])&&pd(i+s[2])&&pd(k+s[3])&&pd(k+s[1])&&' '==pan[i+s[2]][k+s[3]]&&' '==pan[i+s[0]][k+s[1]])Q=7.1,js=1;
    if(js)
    {
        C=0;
        if(X!=' ')return ;
        if(p)visx[i][k]=Q;
        else viso[i][k]=Q;
    }
    //下面是3连的QE两种情况 
    if(Q==4&&E==0)
    {
        if(!pd(i+s[0])||!pd(k+s[1])||pan[i+s[0]][k+s[1]]!=' ')Q-=2;
        else if(!pd(i-f[j])||!pd(k-g[j])||pan[i-f[j]][k-g[j]]==dx)Q--; 
        else 
        {
            Q=6.9;
            if(X==' ')Q=7.1;
        }
    }
    if(E==4&&Q==4)
    {
        if(!pd(i+s[2])||!pd(k+s[3])||pan[i+s[2]][k+s[3]]!=' ')Q-=2;
        else if(!pd(i+f[j])||!pd(k+g[j])||pan[i+f[j]][k+g[j]]==dx)Q--;
        else 
        {
            Q=6.9;
            if(X==' ')Q=7.1;
        }
    }
}
void sl(int i,int k,int j,int C,int &c,char x)
{
    //死路优化 
    char dx;
    dx=x=='x'?'o':'x';
    
    int Q,E,y;//分开对各向长度考虑 + //判断属于延伸
    if(C)
    {
        for(Q=1;dx!=pan[i+Q*f[j]][k+Q*g[j]]&&pd(i+Q*f[j])&&pd(k+Q*g[j])&&Q<5;Q++)if(pan[i+Q*f[j]][k+Q*g[j]]==x)y=1; 
        for(E=1;dx!=pan[i-E*f[j]][k-E*g[j]]&&pd(i-E*f[j])&&pd(k-E*g[j])&&E<5;E++)if(pan[i-E*f[j]][k-E*g[j]]==x)y=1;
        //长度限制     且当前点优先级不高   在此方向不对该点赋值 
        if(Q+E<6&&y&&((x=='x'&&visx[i][k]<6)||(x=='o'&&viso[i][k]<6)))c=0;
    }
}
 
ll BC(int i,int k,char X)
{
    if(Difficult==1)return 0;
    //记录当前点的值，返回给BFS 
    ll value=0;
    //记录当前点周围有效边数量 
    int disx=0,diso=0;
    //若有此点算是交叉点，则后面不再对该点赋值 
    int Cx=1,Co=1;
    //记录有效边类型 
    int tex=0,teo=0,twx=0,two=0;
    //遍历四个方向 
    for(int j=0;j<4;++j)
    {
        if(Difficult>2)
        {
            //交叉点判断 
            int jc,jcx,jco;
            //基本记录变量 
            int jx=0,jo=0;
            //记录当前直线有效边数量 
            for(jc=1,jcx=0,jco=0;pd(i+jc*f[j])&&pd(k+jc*g[j])&&jc<4;jc++)
            {
                //数学操作 
                if('o'==pan[i+jc*f[j]][k+jc*g[j]])jco++,jcx-=2;
                if('x'==pan[i+jc*f[j]][k+jc*g[j]])jcx++,jco-=2;
            }
            //不同情况操作 
            if(CK(i,k,j,jcx,'x',1,jc))disx++,jx++,tex=1;
            else if(ck(i,k,j,'x',1))disx++,jx++,twx=1;
            if(CK(i,k,j,jco,'o',1,jc))diso++,jo++,teo=1;
            else if(ck(i,k,j,'o',1))diso++,jo++,two=1;
            
            for(jc=1,jcx=0,jco=0;pd(i-jc*f[j])&&pd(k-jc*g[j])&&jc<4;jc++)
            {
                if('o'==pan[i-jc*f[j]][k-jc*g[j]])jco++,jcx-=2;
                if('x'==pan[i-jc*f[j]][k-jc*g[j]])jcx++,jco-=2;
            }
            if(CK(i,k,j,jcx,'x',0,jc))disx++,jx++,tex=1;
            else if((ck(i,k,j,'x',2)))disx++,jx++,twx=1;
            if(CK(i,k,j,jco,'o',0,jc))diso++,jo++,teo=1;
            else if(ck(i,k,j,'o',2))diso++,jo++,two=1;
            //1+1有效边 一条直线只判断一次 
            if(ck(i,k,j,'x',0))disx++,jx++,twx=1;
            if(ck(i,k,j,'o',0))diso++,jo++,two=1;
            //数学处理 
            if(disx>=2||diso>=2)
            {
                if(X==' ')
                {
                    visx[i][k]=7;
                    viso[i][k]=7;
                    if(twx==1&&tex==1)visx[i][k]=7.1;
                    if(two==1&&teo==1)viso[i][k]=7.1;
                }
                value=5;
                Cx=0;Co=0;//是交叉点，取消后续改变
                //数学处理 
                if(jx==2||jo==2)
                {
                    if(X==' ')
                    {
                        visx[i][k]++;
                        viso[i][k]++;
                    }
                    else value++;
                }
                break;
            }
        }
        //QE为当前方向取值，同jp函数 
        ll Qx=0,Ex=0,Qo=0,Eo=0;
        // 数组存方向延伸  cx/co  同CxCo 用于死路判断取消后续改变 
        int x[4],o[4],cx=1,co=1;
        jp(i,k,j,x,Qx,Ex,Cx,1,X);
        jp(i,k,j,o,Qo,Eo,Co,0,X);
        if(Qx>=7&&X=='x')return Qx;
        if(Qo>=7&&X=='o')return Qo;//有绝杀直接返回 
        //死路判断 
        sl(i,k,j,Cx,cx,'x');
        sl(i,k,j,Co,co,'o');
        if(!cx&&!co)continue;//优化处理 
        if(X==' ')
        {
            if(Qx>visx[i][k]&&Cx&&cx)visx[i][k]=Qx;
            if(Qo>viso[i][k]&&Co&&co)viso[i][k]=Qo;
        }
        else
        {
            if(X=='x'&&Qx>value&&Cx&&cx)value=Qx;
            if(X=='o'&&Qo>value&&Co&&co)value=Qo;
        }
    }
    return value;
}
void BFS(int x,int y,char X,int key,ll up)//低值空白点 -> 谋略计算优先级 
{
    //假设预算法，本来应该有后续遍历的，但没想到一次遍历就很强了，就没写后续 
    pan[x][y]=X;
    ll value;int tp,sk=0;
    //tp 用于延伸方向判断长度  
    char dx;
    dx=x=='x'?'o':'x'; 
    for(int j=0;j<4;++j)//四条直线方向  每线搜索3*2个点   
    {
        for(int jc= 1,tp=0;pd(x+jc*f[j])&&pd(y+jc*g[j])&&pan[x+jc*f[j]][y+jc*g[j]]!=dx&&jc<4+tp;++jc)
        {
            //如果该点是敌对点，延伸 
            if(pan[x+jc*f[j]][y+jc*g[j]]==X)tp++;
            //不存在或者为空跳过 
            if(!pd(x+jc*f[j])||!pd(y+jc*g[j])||pan[x+jc*f[j]][y+jc*g[j]]!=' ')continue;
            // 数学操作   该点值本身过大 不计入假设影响 
            if(X=='x'&&visx[x+jc*f[j]][y+jc*g[j]]>=5)continue;
            if(X=='o'&&viso[x+jc*f[j]][y+jc*g[j]]>=5)continue;
            
            value=BC(x+jc*f[j],y+jc*g[j],X);
            up+=value;// up用于存影响值 
            
            if(value>=5)sk++;if(value>=7)sk++,key++;//数学操作 
        }
        for(int jc= 1,tp=0;pd(x-jc*f[j])&&pd(y-jc*g[j])&&pan[x-jc*f[j]][y-jc*g[j]]!=dx&&jc<4+tp;++jc)
        {
            if(pan[x-jc*f[j]][y-jc*g[j]]==X)tp++;
            if(!pd(x-jc*f[j])||!pd(y-jc*g[j])||pan[x-jc*f[j]][y-jc*g[j]]!=' ')continue;
             
            if(X=='x'&&visx[x-jc*f[j]][y-jc*g[j]]>=5)continue;
            if(X=='o'&&viso[x-jc*f[j]][y-jc*g[j]]>=5)continue;
            value=BC(x-jc*f[j],y-jc*g[j],X);
            up+=value;
            if(value>=5)sk++;if(value>=7)sk++,key++;
        }
    }
    if(Difficult>4)
    {
        //下为数学操作，赋值处理，没有解释，数据是长期多次测试获取的  最优选择 
        if(key>=2)
        {
            if(X=='x')visx[x][y]=6;
            if(X=='o')viso[x][y]=6;
        }
        else if(sk>2)
        {
            if(X=='x'&&visx[x][y]<5)visx[x][y]=5;
            if(X=='o'&&viso[x][y]<5)viso[x][y]=5;
        }
        else
        {
            if(X=='x'&&visx[x][y]<6)visx[x][y]=up/5;
            if(X=='o'&&viso[x][y]<6)viso[x][y]=up/5;
        }
    }
    else
    {
        //降低难度  粗略处理数据 
        if(sk>2)
        {
            if(viso[x][y]<5)viso[x][y]=5;
        }
        else if(sk)
        {
            if(viso[x][y]<6)viso[x][y]=up/5;
        }
    }
    pan[x][y]=' ';
} 
void CVis()
{
    for(int i=0;i<m;++i)
    for(int k=0;k<n;++k)
    {
        if(pan[i][k]==' ')
        {
            visx[i][k]=0;
            viso[i][k]=0;
            BC(i,k,' ');
        }
    }
    if(Difficult>3)
    {
        for(int i=1;i<m-1;++i)
        for(int k=1;k<n-1;++k)
        {
            if(pan[i][k]==' ')
            {
                if(visx[i][k]<5)BFS(i,k,'x',0,0);
                if(viso[i][k]<5)BFS(i,k,'o',0,0);
            }
        }
    }
    return ;
}

void win(char winner)
{
    puts("");
    if(winner=='x')
    {
        printf("咦！Σ(っ°Д°)っ\t");
        Sleep(1000);
        char S[200]={"好吧，虽然很不想承认...    是我输了!\n"};
        for(int i=0;S[i];++i)
        {
            printf("%c",S[i]);
            if(i==5||i==25)Sleep(500);
            Sleep(50);
        }
        Sleep(1500);
        if(Difficult!=6)
        {
            char s[200]={"\n但是！！！  还有更难的嗷  (～￣▽￣)～   \n\n而且 , 通关后可以知道开发者的小故事呢 ~(￣▽￣)~  祝您游戏愉快\n\n"};
            for(int i=0;s[i];++i)
            {
                printf("%c",s[i]);
                if(i==10||i==40||i==50||i==92)Sleep(500);
                Sleep(50);
            }
        }
        else
        {
            int C;
            do
            {
                puts("\n是否愿意听开发者的长故事？\n\n1愿意\t0不愿意"); 
                scanf("%d",&C);
            }while(C!=1&&C!=0);
            if(!C)return ;
            char s[]={"\n恭喜通关啦, 说明你已经算是五子棋资深玩家了呢.   \n\n"
            "其实呢.\n\n为了降低降低难度, 难度6我留了一个漏洞, 我作为开发者, 在难度5就顶不住了.\n\n"
            "大概用了两个星期才写好这个五子棋AI, 本来还有后续的, 发现已经很难了, 就没再继续写了.\n\n"
            "嗯 , , 就这样吧, 谢谢您能玩我的游戏, 希望您能关注我的公众号，有福利嗷（￣︶￣）. \n\n"};
            for(int i=0;s[i];++i)
            {
                printf("%c",s[i]);
                if(s[i]==',')Sleep(500);
                if(i==223||i==225||s[i]=='.')Sleep(1000);
                Sleep(50);
            } 
        }
        Sleep(1500);
    }
    if(winner=='o')
    {
        printf("承让!承让！\n\n");
        Sleep(1000);
        printf("要不~~~\n\n");
        Sleep(2000);
        printf("再来一局试试？ (￣▽￣) \n");
        Sleep(1000);
    }
    Init();
    return ;
}

int check(int x,int y)
{
    for(int j=0;j<4;++j)
    {
        int i,p=4;
        for(i= 1; pd(x+i*f[j]) && pd(y+i*g[j]) && pan[x+i*f[j]][y+i*g[j]]==pan[x][y] && p ; ++i,--p);
        for(i=-1; pd(x+i*f[j]) && pd(y+i*g[j]) && pan[x+i*f[j]][y+i*g[j]]==pan[x][y] && p ; --i,--p);
        if(!p)
        {
            win(pan[x][y]);
            return 1;
        }
    }
    return 0;
}

void Game()
{
    Init();
    
    PR();
    
    int t=m*n;
    int cm=t%2;
    if(Difficult==6)
    {
        t--;
        cm=t%2;//重置出手序号 
        p.x=m/2;p.y=n/2;
        pan[p.x][p.y]='o';
        visx[p.x][p.y]=-1;
        viso[p.x][p.y]=-1;
        CVis();
        PR();
        if(PRvis==1)printf("电脑落子：【%d %d】\n",p.x,p.y),bord[p.x][p.y] = 3 - s0;
        else printf("电脑落子：【%d %d】\n",p.y,m-p.x-1);
    }
    while(t--)
    {
        if(t%2==cm)CM(t);
        else PM();
        PR();
        
        if(t%2==cm)
        {
            if(PRvis==1)printf("电脑落子：【%d %d】\n",p.x,p.y),bord[p.x][p.y] = 3 - s0;
            else printf("电脑落子：【%d %d】\n",p.y,m-p.x-1);
        }
        
        if(special)
        {
            system("cls");
            return ;
        }
        if(check(p.x,p.y))return ;
    }
    puts("\n和棋啦 ~(￣▽￣)~ ");
    init();
    return ; 
}

