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
    //printf("输入1或者2进行选择\n1，AI执黑先行\n2，玩家执黑先行\n");
    int s;
    ai_ = 0;
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
	for(int k = 0;k < 8; ++k) {//第一种中间空一格的跳活三  eg: 011010
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
	return jushi_fenshu(color) - jushi_fenshu(3 - color);
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


vector<Node> seekpoint(int color) {
	vector<Node> V;
	for(int i = 0;i < N; ++i) {
		for(int j = 0;j < N; ++j) {
			if(bord[i][j] != 0) continue;
			int temp = fenshu(i,j,color) + fenshu(i,j,3-color);
			V.push_back({i,j,temp});
		}
	}
	sort(V.begin(),V.end(),cmpbig);
	return V;
}
Node best_point;
int min_max(int depth,int alpha,int beta,int color) {
	int k1 = jushi_fenshu(color);
	int k2 = jushi_fenshu(3 - color);
	int key =  k1 - k2;
	if(depth == 0) {
		if(depth == 0)
			return jushi_fenshu(color) - jushi_fenshu(3 - color);
	}
	else if(depth % 2 == 0) {
		vector<Node> V = seekpoint(color);
		for(int i = 0,len = V.size();i < NUM && i < len; ++i) {
			int temp = min_max(depth - 1,alpha,beta,3 - color);
			if(temp > alpha) {
				alpha = temp;
				if(depth == 6) {
					best_point.x = V[i].x;
					best_point.y = V[i].y;
					best_point.point = V[i].point;
				}
			}
			if(beta <= alpha)break;//剪枝
		}
		return alpha;
	}
	else {
		vector<Node> V = seekpoint(color);
		for(int i = 0,len = V.size(); i < 10 && i < len; ++i) {
			int temp = min_max(depth - 1,alpha,beta,3-color);
			if(temp < beta) {
				beta = temp;
			}
			if(beta <= alpha) break;
		}
		return beta;
	}
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
char pan[15][15];
ll visx[15][15];
ll viso[15][15];
int f[]={ 0,-1,-1,-1};//方向 — | \ /  
int g[]={-1, 0,-1, 1};
int num=0,hnum=0,xnum=0,tim;
int choice;
struct point
{
    int x,y;
}p;
char dog; 
bool tpchar(int x,int y,char X);
bool tpcheck(int x,int y);
void find(int x,int y,int i,int &dd,int &d,int &b,int &bb,char s);
bool f3(int x,int y,int i,int dd,int d,int b,int bb);
bool f4(int x,int y,int i,int dd,int d,int b,int bb);
int f5(int x,int y,int i,int dd,int d,int b,int bb);
void Init()
{
    for(int i=0;i<m;++i)
    for(int k=0;k<n;++k)
    {
        visx[i][k]=0;
        viso[i][k]=0;
        pan[i][k]=' ';
    }
    mt(visx);mt(viso); 
    dog=' ';
	return ;
}
int pd(int x)
{
    if(x<0||x>=m)return 0;
    return 1;
}
void get()
{
	ll maxx=0;
    ll maxo=-1;
    int a,b,c,d; 
    
    for(int i=0;i<m;++i)
    for(int k=0;k<n;++k)
    if(pan[i][k]==' ')
    {
    	///*
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
    if(dog=='o')
	{
		if(maxo>=maxx)p.x=c,p.y=d; 
	    else if(maxx>=2)p.x=a,p.y=b;
	    else p.x=c,p.y=d;
	} 
    else
    {
    	if(maxo>=maxx)p.x=c,p.y=d; 
	    else if(maxx>=2)p.x=a,p.y=b;
	    else p.x=c,p.y=d;
    }
    return ;
}
void live34(int i,int k,int j,char x,int cn,int jc,int jcn,int &dis,int &js,int &te,int &tw)
{
	char dx;
	if(x=='x')dx='o';
	else dx='x';
	int ls,lx,ys=0,yx=0,firs=0,firx=0;
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
	//CK内容 
	if(cn!=0)
	{
		if(jcn==2&&pan[i+cn*jc*f[j]][k+cn*jc*g[j]]==x)
		{
			dis++;js++;te=1;
			return ;
		}
		if(jcn==3 && ( (dx!=pan[i-cn*f[j]][k-cn*g[j]]&&pd(i-cn*f[j])&&pd(k-cn*g[j])) || (dx!=pan[i+cn*jc*f[j]][k+cn*jc*g[j]]&&pd(i+cn*jc*f[j])&&pd(k+cn*jc*g[j]))))
		{
			dis++;js++;te=1;
			return ;
		}
		if(ls+lx>6&&((cn==1&&ys>=2&&yx==1)||(cn==-1&&yx>=2&&ys==1))&&(pan[i+(ls-1)*f[j]][k+(ls-1)*g[j]]==' '||pan[i-(lx-1)*f[j]][k-(lx-1)*g[j]]==' '))
		{
			dis++;js++;te=1;
			return ;
		}
	}
	//ck内容 
	if(cn==0)
	{
		if(firs+firx>3||firs+1==ls||firx+1==lx||ls+lx<7||ls<3||lx<3||ys!=1||yx!=1)return ;
		else 
		{
			dis++;js++;tw=1;
			return ;
		}
		//cn为0时候只有ck在,所以直接return 
	}
	else
	{
		if(ls+lx>6&&((cn==1&&ys>=2&&yx==0)||(cn==-1&&yx>=2&&ys==0))&&pan[i+(ls-1)*f[j]][k+(ls-1)*g[j]]==' '&&pan[i-(lx-1)*f[j]][k-(lx-1)*g[j]]==' ')
		{
			dis++;js++;tw=1;
			return ;
		}
	}
}
void jp(int i,int k,int j,int s[],ll &Q,ll &E,int &C,int p,char X)
{
	//基本点判断   
	char x,dx;
	if(p)x='x',dx='o';
	else x='o',dx='x';
	int js=0;
	for(s[0]= f[j],s[1]= g[j];tpchar(i+s[0],k+s[1],x);s[0]+=f[j],s[1]+=g[j],Q++);
    for(s[2]=-f[j],s[3]=-g[j];tpchar(i+s[2],k+s[3],x);s[2]-=f[j],s[3]-=g[j],E++);
    //   3+1 或者2+2 限制点 
    //（冲四） 
	if((Q==3&&E==1)||(E==3&&Q==1)||(Q>=2&&E>=2))Q=8,js=1;//此处优化 
    else
    {
    	if(Q>2)Q+=Q-2;
	    if(E>2)E+=E-2;
	    if(Q>0&&E>0&&tpchar(i+s[0],k+s[1],' ')&&tpchar(i+s[2],k+s[3],' '))Q++;//简单优化 
	    Q+=E;
    }
	if(Q>=6)Q=8;
	// （冲四）2+1点强化 
    if(Q==4&&(E==1||E==2)&&tpchar(i+s[0],k+s[1],' ')&&tpchar(i+s[2],k+s[3],' '))
	{
		Q=7.3,js=1;//空白2+1空白 
	}
	if(js)
	{
		if(X!=' ')
		{
			C=0;
			return ;
		}
		if(p)visx[i][k]=Q;
		else viso[i][k]=Q;
		C=0; 
	}
	//下面是3连（活三）的QE两种情况 
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
	if(x=='x')dx='o';
	else dx='x';
	
	int Q,E,y;//分开对各向长度考虑 + //判断属于延伸
	if(C)
	{
		for(Q=1;dx!=pan[i+Q*f[j]][k+Q*g[j]]&&pd(i+Q*f[j])&&pd(k+Q*g[j])&&Q<5;Q++)
			if(pan[i+Q*f[j]][k+Q*g[j]]==x)y=1; 
        for(E=1;dx!=pan[i-E*f[j]][k-E*g[j]]&&pd(i-E*f[j])&&pd(k-E*g[j])&&E<5;E++)
			if(pan[i-E*f[j]][k-E*g[j]]==x)y=1;
        //长度限制     且当前点优先级不高   在此方向不对该点赋值 
		if(x=='x')
		{
			if(Q+E<6&&y&&visx[i][k]<6)c=0;
		}
		else
		{
			if(Q+E<6&&y&&viso[i][k]<6)c=0;
		}
	}
}
 
ll BC(int i,int k,char X)
{
	//i，k默认为空 
	ll value=0;//记录当前点的值，返回给BFS 
	int disx=0,diso=0;//记录当前点周围有效边数量 
	int Cx=1,Co=1;//若有此点算是交叉点，则后面不再对该点赋值 
	int tex=0,teo=0,twx=0,two=0;//记录有效边类型
	int threex=0,fourx=0;//x活三,活/冲四数量
	int threeo=0,fouro=0;//o活三,活/冲四数量
    for(int j=0;j<4;++j)//遍历四个方向 
    {
    	//冲点判断 
		int dx=0,bx=0,ddx=0,bbx=0;
		int qo=0,bo=0,ddo=0,bbo=0;
		find(i,k,j,ddx,dx,bx,bbx,'x');
		if(f3(i,k,j,ddx,dx,bx,bbx))threex++;
		//活四
		if(f4(i,k,j,ddx,dx,bx,bbx))fourx++;
		else fourx+=f5(i,k,j,ddx,dx,bx,bbx);
		
		find(i,k,j,ddo,qo,bo,bbo,'o');
		if(f3(i,k,j,ddo,qo,bo,bbo))threeo++;
		//活四
		if(f4(i,k,j,ddo,qo,bo,bbo))fouro++;
		else fouro+=f5(i,k,j,ddo,qo,bo,bbo);
		if((fourx+threex)>=2||(fouro+threeo)>=2)
        {
            if(((fourx+threex)>=2&&dog=='o')||((fouro+threeo)>=2&&dog=='x'))value=5;//3
			if((threex&&fourx)||(threeo&&fouro))value=7;
			if(X==' ')
            {
            	if(((fourx+threex)>=2&&dog=='o')||((fouro+threeo)>=2&&dog=='x'))
            	{
            		visx[i][k]=7.0;
                	viso[i][k]=7.0;
            	}
                if(threex==1&&fourx==1)visx[i][k]=7.0;//活三7.1方向的交叉应该更高， 设置为7.0为临时之举 ，4，2负变平 
                if(threeo==1&&fouro==1)viso[i][k]=7.0;
            }
            //value=5;
            if(value==7)Cx=0,Co=0;//是交叉点，取消后续改变
            //数学处理 
        }
		//QE为当前方向取值，同jp函数 
    	ll Qx=0,Ex=0;
    	ll Qo=0,Eo=0;
    	int x[4],o[4];// 数组存方向延伸  cx/co  同CxCo 用于死路判断取消后续改变 
        jp(i,k,j,x,Qx,Ex,Cx,1,X);
        jp(i,k,j,o,Qo,Eo,Co,0,X);
        if(Qx>=7&&X=='x')return Qx;
		if(Qo>=7&&X=='o')return Qo;//有绝杀直接返回 
        //*/
		int cx=1,co=1;
		sl(i,k,j,Cx,cx,'x');//死路判断 
		sl(i,k,j,Co,co,'o');//死路判断 
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
	pan[x][y]=X;
	ll value;
	int sk=0;
	char dx;
	if(X=='x')dx='o';
	else dx='x';
	for(int j=0;j<4;++j)//四条直线方向  每线搜索3*2个点   
	{
		int tp;//tp 用于延伸方向判断长度  
		for(int jc= 1,tp=0;pd(x+jc*f[j])&&pd(y+jc*g[j])&&pan[x+jc*f[j]][y+jc*g[j]]!=dx&&jc<4+tp;++jc)
		{
			//如果该点是敌对点，延伸 
			if(pan[x+jc*f[j]][y+jc*g[j]]==X)tp++;
			//不存在或者为空跳过
			if(!pd(x+jc*f[j])||!pd(y+jc*g[j])||pan[x+jc*f[j]][y+jc*g[j]]!=' ')continue;
			 
			if(X=='x'&&visx[x+jc*f[j]][y+jc*g[j]]>=5)continue;
			if(X=='o'&&viso[x+jc*f[j]][y+jc*g[j]]>=5)continue;
			//*/
			value=BC(x+jc*f[j],y+jc*g[j],X);//造成价值的搜索 
			up+=value;
			if(value>=5)sk++;
			if(value>=7)key++;
			if(value>=7)break;
		}
		for(int jc= 1,tp=0;pd(x-jc*f[j])&&pd(y-jc*g[j])&&pan[x-jc*f[j]][y-jc*g[j]]!=dx&&jc<4+tp;++jc)
		{
			if(pan[x-jc*f[j]][y-jc*g[j]]==X)tp++;
			if(!pd(x-jc*f[j])||!pd(y-jc*g[j])||pan[x-jc*f[j]][y-jc*g[j]]!=' ')continue;
			 
			if(X=='x'&&visx[x-jc*f[j]][y-jc*g[j]]>=5)continue;
			if(X=='o'&&viso[x-jc*f[j]][y-jc*g[j]]>=5)continue;
			//*/
			value=BC(x-jc*f[j],y-jc*g[j],X);
			up+=value;
			if(value>=5)sk++;
			if(value>=7)key++;
			if(value>=7)break;
		}
	}
	//*
	if(tpcheck(x,y))
		{
			pan[x][y]=' ';
			return;
		}
	//*/
	if(key>=2)
	{
		if(X=='x')visx[x][y]=6;//6.27  (1,1)败给优化 
		if(X=='o')viso[x][y]=6;//可以考虑值，789 
	}
	else if(sk>2)
	{
		//if(X=='x'&&dog!='x'&&visx[x][y]<5)visx[x][y]=5;
//		if(X=='o'&&dog!='o'&&viso[x][y]<5)viso[x][y]=5;
		if(X=='x'&&visx[x][y]<5)visx[x][y]=5;
		if(X=='o'&&viso[x][y]<5)viso[x][y]=5;
	}
	else
	{
		if(X=='x'&&visx[x][y]<6)visx[x][y]=up/5.0;
		if(X=='o'&&viso[x][y]<6)viso[x][y]=up/5.0;
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
        	BC(i,k,' ');//从可以落子的点分析 
        }
    }
    ///*
    for(int i=1;i<m-1;++i)
    for(int k=1;k<n-1;++k)
    {
        if(pan[i][k]==' ')
        {
        	if(visx[i][k]<5&&visx[i][k]>=0)BFS(i,k,'x',0,0);
        	if(viso[i][k]<5&&viso[i][k]>=0)BFS(i,k,'o',0,0);
        }
    }
	//*/
    return ;
}

void PR()
{
	//return ;
	if(choice)
	{
		puts("CVis  X图：");
		printf("    ");
	    for(int k=0;k<n;++k)
	    printf("  %2d  ",k);
	    puts(""); 
	    for(int i=0;i<m;++i)
	    {
	        printf("    ");
	        for(int k=0;k<n;++k)
	        printf(" -----"); 
	        puts("");
	        
	        for(int k=0;k<n;++k)
	        {
	            if(!k)printf("%2d：|",i);
	            if(visx[i][k]<-5)printf(" 9.9 |");
	            else if(visx[i][k]<0)printf(" 8.8 |");
	            else printf(" %.1lf |",visx[i][k]);
	        }
	        puts("");
	        if(i==m-1)
	        {
	            printf("    ");
	            for(int k=0;k<n;++k)
	            printf(" -----"); 
	            puts("");
	        }
	    }
	    
	    
	    puts("CVis  O图：");
		 printf("    ");
	    for(int k=0;k<n;++k)
	    printf("  %2d  ",k);
	    puts(""); 
	    for(int i=0;i<m;++i)
	    {
	        printf("    ");
	        for(int k=0;k<n;++k)
	        printf(" -----"); 
	        puts("");
	        
	        for(int k=0;k<n;++k)
	        {
	            if(!k)printf("%2d：|",i);
	            if(viso[i][k]<-5)printf(" 9.9 |");
	            else if(viso[i][k]<0)printf(" 8.8 |");
	            else printf(" %.1lf |",viso[i][k]);
	        }
	        puts("");
	        if(i==m-1)
	        {
	            printf("    ");
	            for(int k=0;k<n;++k)
	            printf(" -----"); 
	            puts("");
	        }
	    }
	}
	
    //*/
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
            printf("  %c |",pan[i][k]);
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
void find(int x,int y,int i,int &dd,int &d,int &b,int &bb,char s)
{
	while(tpchar(x-(d+1)*f[i],y-(d+1)*g[i],s)&&d<5)d++;
	while(tpchar(x+(b+1)*f[i],y+(b+1)*g[i],s)&&b<5)b++;
	while(tpchar(x-(dd+d+2)*f[i],y-(dd+d+2)*g[i],s)&&d+dd<5)dd++;
	while(tpchar(x+(bb+b+2)*f[i],y+(bb+b+2)*g[i],s)&&b+bb<5)bb++;
}
bool f3(int x,int y,int i,int dd,int d,int b,int bb)
{
     	 if(d+b ==2 && dd==0 && bb==0 && tpchar(x-(d+1)*f[i],y-(d+1)*g[i],' ') && tpchar(x+(b+1)*f[i],y+(b+1)*g[i],' ') && ( tpchar(x-(d+2)*f[i],y-(d+2)*g[i],' ') || tpchar(x+(b+2)*f[i],y+(b+2)*g[i],' ') ) )return true;
	else if(d+bb==2 && b==0  && dd==0 && tpchar(x-(d+1)*f[i],y-(d+1)*g[i],' ') && tpchar(x+(b+1)*f[i],y+(b+1)*g[i],' ') && tpchar(x+(bb+b+2)*f[i],y+(bb+b+2)*g[i],' ') )return true;
	else if(d+dd==2 && b==0  && bb==0 && tpchar(x-(d+1)*f[i],y-(d+1)*g[i],' ') && tpchar(x+(b+1)*f[i],y+(b+1)*g[i],' ') && tpchar(x-(dd+d+2)*f[i],y-(dd+d+2)*g[i],' ') )return true;
	else if(b+bb==2 && d==0  && dd==0 && tpchar(x-(d+1)*f[i],y-(d+1)*g[i],' ') && tpchar(x+(b+1)*f[i],y+(b+1)*g[i],' ') && tpchar(x+(bb+b+2)*f[i],y+(bb+b+2)*g[i],' ') )return true;
	else if(b+dd==2 && d==0  && bb==0 && tpchar(x-(d+1)*f[i],y-(d+1)*g[i],' ') && tpchar(x+(b+1)*f[i],y+(b+1)*g[i],' ') && tpchar(x-(dd+d+2)*f[i],y-(dd+d+2)*g[i],' ') )return true;
	return false;
}
bool f4(int x,int y,int i,int dd,int d,int b,int bb)
{
	if(b+d ==3 && dd==0 && bb==0 && tpchar(x-(d +1)*f[i],y-(d +1)*g[i],' ') && tpchar(x+(b   +1)*f[i],y+(b   +1)*g[i],' '))
		return true;
	else return false;
}
int f5(int x,int y,int i,int dd,int d,int b,int bb)
{
	if(b+d ==3 && dd==0 && bb==0 && (tpchar(x-(d+1)*f[i],y-(d+1)*g[i],' ') || tpchar(x+(b+1)*f[i],y+(b+1)*g[i],' ')))return 1;
	if(b+bb==3 && d ==0 && dd==0 && tpchar(x+(b+1)*f[i],y+(b+1)*g[i],' '))return 1;
	if(b+dd==3 && bb==0 && d ==0 && tpchar(x-(d+1)*f[i],y-(d+1)*g[i],' '))return 1;
	if(d+bb==3 && dd==0 && b ==0 && tpchar(x+(b+1)*f[i],y+(b+1)*g[i],' '))return 1;
	if(d+dd==3 && b ==0 && bb==0 && tpchar(x-(d+1)*f[i],y-(d+1)*g[i],' '))return 1;
	if(b+d+bb==3 && dd==0 && tpchar(x+(b+1)*f[i],y+(b+1)*g[i],' ') ) return 1;
	if(b+d+dd==3 && bb==0 && tpchar(x-(d+1)*f[i],y-(d+1)*g[i],' ') ) return 1;
	if(((b+d==0&&bb==dd&&bb==3)||(b+d==1&&bb==dd&&bb==2)||(b+d==2&&bb==dd&&bb==1))&& tpchar(x+(b+1)*f[i],y+(b+1)*g[i],' ')&& tpchar(x-(d+1)*f[i],y-(d+1)*g[i],' '))return 2;
	return 0;
}
bool tpchar(int x,int y,char X)//测当前xy是否为X 
{
	if(pd(x)&&pd(y)&&pan[x][y]==X)
		return true;
	return false;
}
bool tpcheck(int x,int y)//看是否犯禁手 
{
	int three=0,four=0;//活三,活/冲四数量 
	bool pdd=false;
	bool pddmid=false;
	for(int i=0;i<4;++i)//四个直线的方向 
	{
		int d=0,b=0,dd=0,bb=0;
		find(x,y,i,dd,d,b,bb,pan[x][y]);
		if(f3(x,y,i,dd,d,b,bb))three++;
		//活四
		if(f4(x,y,i,dd,d,b,bb))four++;
		else four+=f5(x,y,i,dd,d,b,bb);
		//长连 
		if(d+b>4)pdd=true;
	}
	if(pdd)return true;
	if(three&&four)
	{
		//三三四，三四四不考虑 
		return false; 
	}
	else if(three>1)return true;
	else if(four>1)return true;
	return false;
}
int check(int x,int y)
{
	//禁手搜索
	//三三，四四，长连
	//puts("搜索！！！！！！！！！！！！！！！！！！！");
	tim--; 
	if(pan[x][y]==dog&&tpcheck(x,y))
	{
		if(dog=='x')puts("x犯禁手，o获胜！！！");
		else puts("o犯禁手，x获胜！！！");
		return true;
	}
	for(int j=0;j<4;++j)
	{
		int i,p=4;
		for(i= 1; tpchar(x+i*f[j],y+i*g[j],pan[x][y]) && p ; ++i,--p);
    	for(i=-1; tpchar(x+i*f[j],y+i*g[j],pan[x][y]) && p ; --i,--p);
    	if(!p)
    	{
    		printf("\n%c5连获胜   ！！！\n\n",pan[x][y]);//win(pan[x][y]);
    		if(pan[x][y]=='o')num++;
    		else xnum++;
        	return 1;
    	}
	}
	if(!tim)
	{
		puts("\n和棋啦！！");
		hnum++;
		return 1;
	}
	return 0;
}
int main() {
	int loc = 1;
	srand((int)time(NULL));
//	printf("%d\n",jushi_fenshu(1));
//	bord[9][4] = bord[10][4] = bord[6][6] = bord[6][8] = bord[7][5] = bord[9][7] = 1;
//	bord[8][6] = bord[7][6] = bord[9][5] = bord[7][5] = bord[12][4] = 2;
//	printf("%d\n",fenshu(6,4,1));
//	getchar();

	while(loc <= 1) {
		num=0;
	    Init();init();
	    tim=m*n-1;
		choice=0;
		p.x=7;//rand()%15
		p.y=7;//rand()%15
		printf("点%d %d 开\n",p.x,p.y);
		if(dog==' ')dog='o';
		pan[p.x][p.y]='o';
		visx[p.x][p.y]=-1;
		viso[p.x][p.y]=-1;
		CVis();//alphago.down(p.x,p.y);
		go(p.x,p.y,1);
		PR();printf("o:( %d %d )\n",p.x,p.y);
		//*/
		int t=m*n-tim;
	    while(1)
	    {
	//    	min_max(6,-INF,INF,2);
	//    	p.x = best_point.x;
	//    	p.y = best_point.y;
	//    	printf("Ai 落子 %d %d,分数 = %d\n",p.x,p.y,best_point.point);
	//    	go(p.x,p.y,2);
	    	pair<int,int> aiai = AI_1(2);
			go(aiai.first,aiai.second,2);
			p.x=aiai.first;
			p.y=aiai.second;
	        if(dog==' ')dog='x';
	       	pan[p.x][p.y]='x';
			visx[p.x][p.y]=-1;
			viso[p.x][p.y]=-1;
			
			CVis();//alphago.down(p.x,p.y);
			PR();printf("x:( %d %d )\n",p.x,p.y);
			if(check(p.x,p.y))break;
			
	        
			if(t==0)
			{
				if(pan[7][7]==' ')p.x=7,p.y=7;
				else p.x=6,p.y=6;
				t=1;
			} 
			else get();
		    pan[p.x][p.y]='o';
		    go(p.x,p.y,1);
		    visx[p.x][p.y]=-1;
			viso[p.x][p.y]=-1;
			
			CVis();//alphago.down(p.x,p.y);
			PR();printf("o:( %d %d )\n",p.x,p.y);
			if(check(p.x,p.y))break;
		}
		printf("【计步：%d】\n",225-tim); 
		loc++;
	}
	printf("ai_win = %d ai_lose = %d\n",ai_win,ai_lose);
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

