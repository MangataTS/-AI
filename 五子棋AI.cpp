/*
〖开局〗在对局开始阶段形成的布局。一般指前3手棋形成的局面。
〖连〗2枚以上的同色棋子在一条线上邻接成串。
〖五连〗五枚同色棋子在一条线上邻接连串。                               		√
〖长连〗五枚以上同色棋子在一条线上邻接成串。								√ 
〖成五〗五连和长连的统称。
〖威胁〗下一手可以成五或者活四的点。
〖活四〗有两个威胁的四。                                                	√
〖冲四〗只有一个威胁的四。													√ 
〖死四〗不能成五的四连。													√ 
〖三〗可以形成四再形成五的三枚同色棋子组成的棋型。							√ 
〖活三〗再走一着可以形成活四的三。   									 	√
〖连活三〗两端都是威胁的活三。简称“连三”。		 						√ 
〖跳活三〗中间夹有一个威胁的活三。简称“跳三”。							√ 
〖眠三〗再走一着可以形成冲四的三。											√ 
〖死三〗不能成五的三。														√ 
〖活二〗再走一着可以形成活三的二。                                       	√
〖连活二〗连的活二。简称“连二”。											√ 
〖跳活二〗中间隔有一个空点的活二。简称“跳二”。
〖大跳活二〗中间隔有两个空点的活二。简称“大跳二”。
〖眠二〗再走一着可以形成眠三的二。
〖死二〗不能成五的二。
〖先手〗对方必须应答的着法，相对于活三先手而言，冲四称为“绝对先手”。
〖三三〗一子落下同时形成两个活三。也称“双三”。
〖四四〗一子落下同时形成两个冲四。也称“双四”。
〖四三〗一子落下同时形成一个冲四和一个活三。
 */

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
#define mt(x) memset(x,0,sizeof x)
#define m 15
#define n 15
typedef long double ll;
const int N = 15;
#define INF 10000000

const int NUM = 5;

struct Node {
	int x,y,point;
}; 

bool cmpbig(Node a, Node b) {
	return a.point > b.point;
}
bool cmpsmall(Node a, Node b) {
	return a.point < b.point;
}


int bord[N][N];//  0表示当前为空，1表示黑子，2表示白子
int ai_ = 1;//ai_ = 1 表示的是AI先手
int s0;
bool IS_END = false; 
const int posit_value[20][20] =	{	//这是一个位置价值，从外到内依次递减 
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },

{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },

{ 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0 },

{ 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0 },

{ 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 },

{ 0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0 },

{ 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0 },

{ 0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0 },

{ 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 },

{ 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0 },

{ 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0 },

{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },

{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },

{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};


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
    return bord[x][y] == k;
}

int sum_num_of_same(int x,int y,int k) {
    int i = x + dx[k],j = y + dy[k];
    int sum = 0;
    int color = bord[x][y];
    if(color == 0) return 0; //如果当前点为空直接返回0
    while(issame(i,j,color)) 
		sum++,i+=dx[k],j+=dy[k];
    return sum;
}

bool is_end(int x,int y) {
    for(int k = 0;k < 4; ++k) {
    	int p = (sum_num_of_same(x,y,k + 4) + sum_num_of_same(x,y,k));
    	if(p >= 4)
        	IS_END = true;
	}	
    return IS_END; //不考虑禁手
}


//----------------------------------------------------------------------------------------------分割线  
//这个范围内是进攻函数    貌似敌人的进攻就是自己的防御 
int live2(int x,int y,int color) {//目前粗略判断一下 ，落子相邻的活2，也就是连活2 
	int sum = 0;
	for(int k = 0;k < 8; ++k) {
		int kong1 = 0;
		int kong2 = 0;
		int color_num = 0;
		for(int i = -1;i >= -2 && is_inbord(x + dx[k] * i,y + dy[k] * i) && issame(x + dx[k] * i,y + dy[k] * i,0); --i) {
			kong1++;
		}
		if(kong1 == 1) {
			for(int i = 1;i <= 4 && is_inbord(x + dx[k] * i,y + dy[k] * i); ++i) {
				if(issame(x + dx[k] * i,y + dy[k] * i,0)) kong2++;
				else if(issame(x + dx[k] * i,y + dy[k] * i,color)) color_num++;
				else break;
			}
			if(kong2 == 3 && color_num == 1) sum++;
		}
		else if(kong1 == 2) {
			for(int i = 1;i <= 3 && is_inbord(x + dx[k] * i,y + dy[k] * i); ++i) {
				if(issame(x + dx[k] * i,y + dy[k] * i,0)) kong2++;
				else if(issame(x + dx[k] * i,y + dy[k] * i,color)) color_num++;
				else break;
			}
			if(kong2 == 2 && color_num == 1) sum++;
		}
		
	} 
	return sum;
}

int die2(int x,int y,int color) {//落子成死二的个数
	int sum = 0;
	for(int k = 0;k < 8; ++k) {
		if(is_inbord(x + dx[k],y + dy[k]) && bord[x + dx[k]][y + dy[k]] == color) {
			if(is_inbord(x + dx[k] * 2,y + dy[k] * 2) && bord[x + dx[k] * 2][y + dy[k] * 2] != 3 - color) continue;//正方向第二格如果在棋盘内并且不是地方棋子 
			if(is_inbord(x - dx[k],y - dy[k]) && bord[x - dx[k]][y - dy[k]] != 3 - color) continue; //反方向如果不是地方棋子，并且在棋盘内	
			sum++;
		} 
		
	} 
	return sum;
} 

int mian2(int x,int y,int color) {//计算眠2的数量 
	int sum = 0;
	for(int k = 0;k < 8; ++k) {
		if(is_inbord(x + dx[k],y + dy[k]) && bord[x + dx[k]][y + dy[k]] == color) {
			if(is_inbord(x + dx[k] * 2,y + dy[k] * 2) && bord[x + dx[k] * 2][y + dy[k] * 2] == 3 - color && is_inbord(x - dx[k],y - dy[k]) && bord[x - dx[k]][y - dy[k]] == 0) sum++;
			else if(is_inbord(x - dx[k],y - dy[k]) && bord[x - dx[k]][y - dy[k]] == 3 - color && is_inbord(x + dx[k] * 2,y + dy[k] * 2) && bord[x + dx[k] * 2][y + dy[k] * 2] == 0) sum++; 
			sum++;
		} 
		
	} 
	return sum;
}

int live3(int x,int y,int color) {//计算[x、y]点落子成活三个数
    int sum = 0;	
    for(int k = 0,i = 1;k < 4; ++k) {//四个方向寻找  连活三
        int loc = 1;
        int fg = 2;//表示能构成活三的可能
        //正方向找过去
        for(i = 1;issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//如果当前位置不是空位说明构成活三的可能减一
        i++;
		if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一
        //反方向找过去
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//如果当前位置不是空位说明构成活三的可能减一
        i--;
		if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一
        if(loc == 3 && fg >= 1) //构成活三
            sum++;
    }
    for(int k = 0;k < 8; ++k) {  //第一种中间空一格的活三也就是跳活三  eg: 010110
    	int loc = 0;
    	int kong = 1;
    	int feikong = 0;
    	if(!is_inbord(x - dx[k],y - dy[k])) continue; // 不在边界 
    	else if(bord[x - dx[k]][y - dy[k]] != 0) continue;//反方向不是空 
    	if(!is_inbord(x + dx[k],y + dy[k])) continue; // 不在边界 
    	else if(bord[x + dx[k]][y + dy[k]] != 0) continue;//正方向不是空 
    	for(int i = 2;i <= 4; ++i) {		//往这个方向看3格 
    		if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) break;
    		if(bord[x + dx[k] * i][y + dy[k] * i] == 3 - color) //和敌方棋子相等 
				break;
			if(bord[x + dx[k] * i][y + dy[k] * i] == color) feikong++;
			else kong++;
			if(i == 2 && kong == 2) break; //如果中间空了两个位置那么就不是跳活三 
		}
		if(kong == 2 && feikong == 2) //是跳活三 
			sum++;
	}
	for(int k = 5;k < 8; ++k) {//第一种中间空一格的跳活三  eg: 011010
		int feikong = 0;
		int kong = 0;
		if(!is_inbord(x - dx[k],y - dy[k])) continue;//不在边界
		else if(bord[x - dx[k]][y - dy[k]] != color) continue;//反方向第一个位置为color
		if(!is_inbord(x - dx[k] * 2,y - dy[k] * 2)) continue;//不在边界
		else if(bord[x - dx[k] * 2][y - dy[k] * 2] != 0) continue;//反方向第二个位置为0 
		for(int i = 1;i <= 3; ++i) {
			if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) break;
			if(bord[x + dx[k] * i][y + dy[k] * i] == 3 - color) //和敌方棋子相等 
				break;
			if(bord[x + dx[k] * i][y + dy[k] * i] == color) feikong++;
			else kong++;
			if(i == 2 && bord[x + dx[k] * i][y + dy[k] * i] != color) break;//如果第二个位置不和color相等那么就不是跳3 
		}
		if(kong == 2 && feikong == 1) sum++; 
	} 
    return sum;
}

int mian3(int x,int y,int color) {//在[x,y]这个位置形成的眠三的数量 
	int sum = 0;
    for(int k = 0,i = 1;k < 4; ++k) {//四个方向寻找眠三
        int loc = 1;
        int fg = 2;//表示能构成眠3的可能
        //正方向找过去
        for(i = 1;issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么fg--
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一
        //反方向找过去
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么fg--
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一

        if(loc == 3 && fg == 1) //构成眠3
            sum++;
    }
    return sum;
}

int die3(int x,int y,int color) {//落子成死三的个数
	int sum = 0;
	for(int k = 0,i = 1;k < 4; ++k) {
		int loc = 0; 
		for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color) && loc < 3; ++i) loc++;
		if(is_inbord(x + dx[k] * i,y + dy[k] * i) && bord[x + dx[k] * i][y + dy[k] * i] != 3 - color) continue; //如果下一个落子在棋盘内，并且棋盘下一个位置不为另一个棋子 
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color) && loc < 3; --i) loc++;
		if(is_inbord(x + dx[k] * i,y + dy[k] * i) && bord[x + dx[k] * i][y + dy[k] * i] != 3 - color) continue; //如果下一个落子在棋盘内，并且棋盘下一个位置不为另一个棋子 
		if(loc == 2)//如果满足 死三的条件 
			sum++; 
	} 
	return sum;
} 

int live4(int x,int y,int color) {//落子成活四的个数 目前只计算了连活4 ，跳活4还有待计算 
    int sum = 0;
    for(int k = 0,i = 1;k < 4;++k) {//连活4 
        int loc = 0;
        for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color) && loc < 4; ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//如果当前位置不是空位就continue

        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color) && loc < 4; --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//如果当前位置不是空位就continue

        if(loc == 3) sum++;
    }
    return sum;
}

int die4(int x,int y,int color) {//落子成死四的个数
	int sum = 0;
	for(int k = 0,i = 1;k < 4; ++k) {
		int loc = 0;
		for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color) && loc < 4; ++i) loc++;
		if(is_inbord(x + dx[k] * i,y + dy[k] * i) && bord[x + dx[k] * i][y + dy[k] * i] != 3 - color) continue; //如果下一个落子在棋盘内，并且棋盘下一个位置不为另一个棋子 
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color) && loc < 4; --i) loc++;
		if(is_inbord(x + dx[k] * i,y + dy[k] * i) && bord[x + dx[k] * i][y + dy[k] * i] != 3 - color) continue; //如果下一个落子在棋盘内，并且棋盘下一个位置不为另一个棋子 
		if(loc == 3)
			sum++;
	} 
	return sum;
} 

int cheng5(int x,int y,int color) {//落子成5的个数
    int sum = 0;
    for(int k = 0,i = 1;k < 4;++k) {
        int loc = 1;
        for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(loc == 5) return ++sum;
    }
    return sum;
}

int changlian(int x,int y,int color) {//落子长连的个数 
	int sum = 0;
    for(int k = 0,i = 1;k < 4;++k) {
        int loc = 1;
        for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(loc > 5) return ++sum;
    }
    return sum;
} 

int rush4(int x,int y,int color) {//落子成单冲4的个数
    int sum = 0;
	for(int k = 0,i;k < 8; ++k) {
		int color_num = 0;
		// 落子连冲4的情况 eg: 011112 
		if(is_inbord(x + dx[k],y + dy[k]) && bord[x + dx[k]][y + dy[k]] == color && is_inbord(x - dx[k],y - dy[k]) && issame(x - dx[k],y - dy[k],0)) { //正方向第一个位置为color反方向第一个位置为0 
			for(i = 2;i <= 3 && is_inbord(x + dx[k] * i,y + dy[k] * i); ++i) {
					if(issame(x + dx[k] * i,y + dy[k] * i,color)) color_num++;
					else break;
			}
			if(is_inbord(x + dx[k] * i,y + dy[k] * i) && color_num == 2) {
				if(bord[x + dx[k] * i][y + dy[k] * i] == 3 - color) sum++; 
			}
		}
		else if(bord[x + dx[k]][y + dy[k]] == 0) {//落子跳冲4的情况 eg 101112 
			for(i = 2;i <= 4 && is_inbord(x + dx[k] * i,y + dy[k] * i); ++i) {
				if(issame(x + dx[k] * i,y + dy[k] * i,color)) color_num++;
				else break;
			}
			if(is_inbord(x + dx[k] * i,y + dy[k] * i) && color_num == 3) {
				if(bord[x + dx[k] * i][y + dy[k] * i] == 3 - color) sum++;
			}
		}
	} 
    return sum;
}
//----------------------------------------------------------------------------------------------分割线  

int ai_win = 0,ai_lose = 0;

void go(int x,int y,int color) {
    bord[x][y] = color;//落子
    if(ai_ == 1 && color == 1 || ai_ == 0 && color == 2)
    	printf("AI落子    x = %d, y = %d\n",x,y);
    else 
    	printf("玩家落子  x = %d, y = %d\n",x,y);
    if(is_end(x,y)) {
        if(ai_ == 1 && color == 1 || ai_ == 0 && color == 2) printf("AI胜利\n"),ai_win++;
        else printf("玩家胜利\n"),ai_lose++;
        return ;
    }
    
}

int fenshu(int x,int y,int color) {//对当前[x,y]坐标落子的价值初步评估 
    int live3_ = live3(x,y,color);
    int rating; 
    if(changlian(x,y,color) >= 1 || cheng5(x,y,color) >= 1) { //长连和成五返回  
    	return 100000;
	}
	else if(live4(x,y,color) >= 1 || rush4(x,y,color) >= 2 || (rush4(x,y,color) >= 1 && live3_ >= 1) || live3_ >= 2) { //落子形成活四或者两个冲4或者一个冲4和一个活三也就是四三 ，或者双活三 
		return 20000;
	}
	rating = (live3_ + rush4(x,y,color))* 600 + (mian3(x,y,color) + live2(x,y,color))* 100 +  (die4(x,y,color) + die3(x,y,color) + die2(x,y,color)) * (-5);
    for(int i = 0;i < 8; ++i) if(can_luozi(x + dx[i],y + dy[i])) rating += 1;//查看当前落子的周围八个位置，如果能落子就加1分,这个算棋势分数 
    return rating + posit_value[x][y] ;//返回计算分数
}

int jushi_fenshu(int color) {
	int ans = 0;
	bool vis[N][N];
	memset(vis,0,sizeof vis);
	for(int i = 0;i < N; ++i) {
		for(int j = 0;j < N; ++j) {
			if(bord[i][j] != color) continue; 
			for(int k = 0;k < 8; ++k) {
				for(int l = 1;l <= 3; ++l) {
					if(is_inbord(i + dx[k] * l,j + dy[k] * l) && bord[i + dx[k] * l][j + dy[k] * l] == 0 && vis[i + dx[k] * l][j + dy[k] * l] == false) { //在棋盘内并且坐标点为空 
						ans += fenshu(i + dx[k] * l,j + dy[k] * l,color);
						vis[i + dx[k] * l][j + dy[k] * l] = true;
					}
				}
			}
		}
	}
	return ans;
} 

//目前的AI不考虑禁手

int AI_7(int color) {
	return jushi_fenshu(color) - jushi_fenshu(3 - color);
} 

int AI_6(int color) {
	int loc_key = INF,temp;
    vector<Node> V;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue; //不能落子
            temp = (fenshu(i,j,color) + fenshu(i,j,3 - color)); // + fenshu(i,j,3 - color)
//            if(temp >= 100000) return -100000;
            V.push_back({i,j,temp});
        }
    }
    sort(V.begin(),V.end(),cmpbig);
    for(int i = 0,len = V.size();i < NUM && i < len; ++i) { // 最佳落子点 
    	bord[V[i].x][V[i].y] = color;
    	temp = AI_7(3 - color);
    	bord[V[i].x][V[i].y] = 0;
    	if(temp < loc_key) {	//第六层博弈树取极小
            loc_key = temp;
        }
	}
    return loc_key;
} 

int AI_5(int color) {
//	return jushi_fenshu(color) - jushi_fenshu(3 - color);
	int loc_key = -INF,temp;
    vector<Node> V;
    for(int i = 0;i  < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue;
            temp = (fenshu(i,j,color) + fenshu(i,j,3 - color)); // + fenshu(i,j,3 - color)
            V.push_back({i,j,temp});
        }
    }
    
    sort(V.begin(),V.end(),cmpbig);
    for(int i = 0,len = V.size();i < NUM && i < len; ++i) {// 最佳落子点 
    	bord[V[i].x][V[i].y] = color;
    	temp = AI_6(3 - color);
    	bord[V[i].x][V[i].y] = 0;
    	if(temp > loc_key) {//第五层博弈树取极大
            loc_key = temp;
        }
	}
    return loc_key;
}

int AI_4(int color) {
	int loc_key = INF,temp;
    vector<Node> V;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue; //不能落子
            temp = (fenshu(i,j,color) + fenshu(i,j,3 - color)); 
            V.push_back({i,j,temp});
        }
    }
    sort(V.begin(),V.end(),cmpbig);
    for(int i = 0,len = V.size();i < NUM && i < len; ++i) { // 最佳落子点 
    	bord[V[i].x][V[i].y] = color;
    	temp = AI_5(3 - color);
    	bord[V[i].x][V[i].y] = 0;
    	if(temp < loc_key) {	//第四层博弈树取极小
            loc_key = temp;
        }
	}
    return loc_key;
}

int AI_3(int color) {
    int loc_key = -INF,temp;
    vector<Node> V;
    for(int i = 0;i  < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue;
            temp = (fenshu(i,j,color) + fenshu(i,j,3 - color)); 
            V.push_back({i,j,temp});
        }
    }
    
    sort(V.begin(),V.end(),cmpbig);
    for(int i = 0,len = V.size();i < NUM && i < len; ++i) {// 最佳落子点 
    	bord[V[i].x][V[i].y] = color;
    	temp = AI_4(3 - color);
    	bord[V[i].x][V[i].y] = 0;
    	if(temp > loc_key) {//第三层博弈树取极大
            loc_key = temp;
        }
	}
    return loc_key;
}//第三层AI

int AI_2(int color) {
    int loc_key = INF,temp;
    vector<Node> V;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue; //不能落子
            temp = (fenshu(i,j,color) + fenshu(i,j,3 - color)); 
//            if(temp >= 100000) return -100000;
            V.push_back({i,j,temp});
        }
    }
    sort(V.begin(),V.end(),cmpbig);
    for(int i = 0,len = V.size();i < NUM && i < len; ++i) {// 最佳落子点 
    	bord[V[i].x][V[i].y] = color;
    	temp = AI_3(3 - color);
    	bord[V[i].x][V[i].y] = 0;
    	if(temp < loc_key) {	//第二层博弈树取极小
            loc_key = temp;
        }
	}
    return loc_key;
}//第二层AI

pair<int,int> AI_1(int color) {
    if(bord[7][7] == 0) return pair<int,int>(7,7); //如果天元没有落子，那么落子天元
    
    int jushi_key = jushi_fenshu(color);
	
	int loc_key = -INF,keyi,keyj,temp;
    vector<Node> V;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue;
            int k1 = (fenshu(i,j,color));
            int k2 = fenshu(i,j,3 - color);
            temp = k1 + k2;
            if(k1 >= 100000 || k2 >= 100000) return pair<int,int> (i,j);
            V.push_back({i,j,temp});
        }
    }
   
    sort(V.begin(),V.end(),cmpbig);
    for(int i = 0,len = V.size();i < NUM && i < len; ++i) {// 最佳落子点 
    	bord[V[i].x][V[i].y] = color;
    	temp = AI_2(3 - color);
    	bord[V[i].x][V[i].y] = 0;
    	if(temp > loc_key) {//第一层博弈树取极大
            loc_key = temp;
            keyi = V[i].x,keyj = V[i].y;
        }
	}
    printf("loc_key = %d,x = %d,y = %d\n",loc_key,keyi,keyj);
    return pair<int,int> (keyi,keyj);
}//第一层AI


Node kaiju(int x,int y) {// 黑子调用，传的参数是白子第一个落子的位置，也就是在棋面第三步的时候黑子调用 
	//黑子走天元 
	vector<Node> V;
	if(x == 6 && y == 8) {// 斜指开局
		V.push_back({5,9,fenshu(5,9,1)});//长星局
		V.push_back({6,9,fenshu(6,9,1)});//峡月局
		V.push_back({7,9,fenshu(7,9,1)});//恒星局 
		V.push_back({8,9,fenshu(8,9,1)});//水月局 
		V.push_back({9,9,fenshu(9,9,1)});//流星局
		V.push_back({7,8,fenshu(7,8,1)});//云月局
		V.push_back({8,8,fenshu(8,8,1)});// 浦月局
		V.push_back({9,8,fenshu(9,8,1)});//岚月局
		V.push_back({8,7,fenshu(8,7,1)});//银月局
		V.push_back({9,7,fenshu(9,7,1)});//明星局
		V.push_back({8,6,fenshu(8,6,1)});//斜月局
		V.push_back({9,6,fenshu(9,6,1)});//名月局 
		V.push_back({9,5,fenshu(9,5,1)});//彗星局 
	}
	else if(x == 6 && y == 7){//直指开局
		V.push_back({5,7,fenshu(5,7,1)});//寒星局 
		V.push_back({5,8,fenshu(5,8,1)});//溪月局
		V.push_back({5,9,fenshu(5,9,1)});//疏星局
		V.push_back({6,8,fenshu(6,8,1)});//花月局
		V.push_back({6,9,fenshu(6,9,1)});//残月局
		V.push_back({7,8,fenshu(7,8,1)});//雨月局
		V.push_back({7,9,fenshu(7,9,1)});//金星局
		V.push_back({8,7,fenshu(8,7,1)});//松月局
		V.push_back({8,8,fenshu(8,8,1)});//丘月局
		V.push_back({8,9,fenshu(8,9,1)});//新月局 
		V.push_back({9,7,fenshu(9,7,1)});//瑞星局
		V.push_back({9,8,fenshu(9,8,1)});//山月局
		V.push_back({9,9,fenshu(9,9,1)});//游星局 
	}
	else {
		printf("白子指定开局错误!\n");
		return Node{-1,-1,-1};//返回一个无效值 
			
	}
	sort(V.begin(),V.end(),cmpbig);
	return V[rand() % 3];//玄学优化：返回最优的前三个坐标种的随机一种 
} 


void draw() {
	printf("\n\n");
	printf("         ");
	printf("   ");
	for(int i = 0;i < N; ++i) if(i < 10) printf("  %d ",i); else printf("  %d",i);
	puts("");
	for(int i = 0;i < N; ++i) {
		printf("         ");
		for(int j = 0;j <= N; ++j) {
			printf("----");
		}
		puts("");
		printf("         ");
		if(i < 10)
		printf("%d  ",i);
		else printf("%d ",i);
		for(int j = 0;j < N; ++j) {
			if(bord[i][j] == 1) printf("| X ");
			else if(bord[i][j] == 2) printf("| O ");
			else printf("|   ");
		}
		puts("");
	}
	printf("\n\n");
}

void play(int color) {
	int x,y;
	printf("请输入落子坐标\n"); 
	scanf("%d %d",&x,&y);
	if(is_inbord(x,y) && bord[x][y] == 0)
		go(x,y,color);
	else return play(color);
}
int main() {
	srand((int)time(NULL)); 
//	bord[4][4] = bord[4][9] = 1;
//	bord[11][6] = bord[11][7] = bord[11][9] = bord[10][7] = bord[13][10] = 2;
//	printf("%d\n",live3(11,8,2));
//	printf("%d\n",jushi_fenshu(2));
//	bord[2][5] = bord[3][7] = bord[3][8] = bord[3][9] = bord[4][5] = bord[3][10] = 0;
	double sum_time = 0;
    init();
    int cout = 0;
    if(ai_) {
	    while(!IS_END) {
	    	//开始计时
			clock_t start = clock(); 
	    	pair<int,int> aiai = AI_1(1);
	    	double end = (clock() - start)/1000.0;
	    	printf("AI调用所需时间为:%lf秒",end);
			sum_time +=  end;
			go(aiai.first,aiai.second,1);
			cout++;
			if(IS_END) {
				draw();
				system("pause");
				break;
			}
				
			draw();
	    	play(2);
	    	cout++;
			if(IS_END) {
				draw();
				system("pause");
				break;
			}
		}
	}
	else {
		while(!IS_END) {
			play(1);
			if(IS_END) {
				draw();
				system("pause");
				break;
			}
			clock_t start = clock(); 
			pair<int,int> aiai = AI_1(2);
			double end = (clock() - start)/1000.0;
			printf("AI调用所需时间为:%lf秒",end);
			sum_time +=  end;
			go(aiai.first,aiai.second,2);
			draw();
		}
	}
	printf("\n总共走了%d步\n",cout);
	printf("AI总共思考了%lf秒\n",sum_time);
	puts("\n-------------game over------------------");
	puts("-------------分割线------------------");
	puts("-------------分割线------------------");
	while(true) getchar(); 
}
/*
7 6
6 6
5 6
8 7
6 5
8 6
4 7
8 3
8 5
6 4
6 2
8 8
9 9
9 7
10 6
11 5


7 6
6 7
8 8
3 3
8 5

 */

