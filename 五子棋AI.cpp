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
using namespace std;

const int N = 15;
#define INF 10000000

const int NUM = 10;

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
	for(int k = 0;k < 4; ++k) {
		int loc = 1;
		int kong = 0;
		if(is_inbord(x + dx[k],y + dy[k]) && is_inbord(x + dx[k + 4],y + dy[k + 4]) && bord[x + dx[k]][y + dy[k]] != 0 && bord[x + dx[k + 4]][y + dy[k + 4]] != 0) {
			continue;
		}
		else if(is_inbord(x + dx[k],y + dy[k]) && bord[x + dx[k]][y + dy[k]] == color) {
			for(int i = 2;is_inbord(x + dx[k] * i,y + dy[k] * i) && issame(x + dx[k] * i,y + dy[k] * i,0) && kong < 4; ++i) kong++;
			for(int i = -1; is_inbord(x + dx[k] * i,y + dy[k] * i) && issame(x + dx[k] * i,y + dy[k] * i,0) && kong < 4;--i) kong++;
			
		}
		else if(is_inbord(x + dx[k + 4],y + dy[k + 4]) && bord[x + dx[k + 4]][y + dy[k + 4]] == color) {
            for (int i = 2;is_inbord(x + dx[k + 4] * i, y + dy[k + 4] * i) && issame(x + dx[k + 4] * i, y + dy[k + 4] * i, 0) && kong < 4; ++i)
                kong++;
            for (int i = -1;is_inbord(x + dx[k + 4] * i, y + dy[k + 4] * i) && issame(x + dx[k + 4] * i, y + dy[k + 4] * i, 0) && kong < 4; --i)
                kong++;
        }
        if(kong >= 4) sum++;
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
        if(loc == 3 && fg == 1) //构成活三
            sum++;
    }
    for(int k = 0;k < 8; ++k) {  //中间空一格的活三也就是跳活三  eg: 011010
    	int loc = 0;
    	int kong = 0;
    	int feikong = 0;
    	if(!is_inbord(x + dx[k + 4],y + dy[k + 4])) continue; // 不在边界 
    	else if(bord[x + dx[k + 4]][y + dy[k + 4]] != color) continue;//反方向不是color
    	if(!is_inbord(x + dx[k + 4] * 2,y + dy[k + 4] * 2)) continue; // 不在边界 
    	else if(bord[x + dx[k + 4] * 2][y + dy[k + 4] *2] == 0) continue;//反方向不是空的 
    	for(int i = 1;i <= 3; ++i) {		//往这个方向看3格 
    		if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) break;
    		if(bord[x + dx[k] * i][y + dy[k] * i] == 3 - color) //和敌方棋子相等 
				break;
			if(bord[x + dx[k] * i][y + dy[k] * i] == color) feikong++;
			else kong++;
		}
		if(kong == 2 && feikong == 1) //是跳活三 
			sum++;
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
    for(int k = 0,i = 1;k < 4; ++k) {//四个方向寻找活三
        int loc = 1;
        int fg = 2;//表示能构成冲4的可能
        //正方向找过去
        for(i = 1;issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一
        //反方向找过去
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一
        if(loc == 4 && fg == 1) //构成单冲4
            sum++;
    }
    return sum;
}
//----------------------------------------------------------------------------------------------分割线  

void go(int x,int y,int color) {
    bord[x][y] = color;//落子
    if(ai_ == 1 && color == 1 || ai_ == 0 && color == 2)
    	printf("AI落子    x = %d, y = %d\n",x,y);
    else 
    	printf("玩家落子  x = %d, y = %d\n",x,y);
    if(is_end(x,y)) {
        if(ai_ == 1 && color == 1 || ai_ == 0 && color == 2) printf("AI胜利\n");
        else printf("玩家胜利\n");
        return ;
    }
    
}

int fenshu(int x,int y,int color) {//对当前[x,y]坐标落子的价值初步评估 
//	int win5 = 0, alive4 = 0, die4 = 0, lowdie4 = 0, alive3 = 0,
//		die3 = 0, tiao3 = 0, alive2 = 0, lowalive2 = 0, die2 = 0, nothing = 0;
	
//	win5 = cheng5(x,y,color) + changlian(x,y,color);
//	alive4 = live4(x,y,color);
//	die4 = deie
    int live3_ = live3(x,y,color);
    int rating; 
    if(changlian(x,y,color) >= 1 || cheng5(x,y,color) >= 1) { //长连和成五返回  
    	return 100000;
	}
	else if(live4(x,y,color) >= 1 || rush4(x,y,color) >= 2 || (rush4(x,y,color) >= 1 && live3_ >= 1) || live3_ >= 2) { //落子形成活四或者两个冲4或者一个冲4和一个活三也就是四三 ，或者双活三 
		return 10000;
	}
	rating = (live3_ + rush4(x,y,color))* 1000 + (mian3(x,y,color) + live2(x,y,color))* 20 +  (die4(x,y,color) + die3(x,y,color) + die2(x,y,color)) * (-10);
	return rating;
//	else if(live3_ >= 1 && mian3(x,y,color) >= 1) { //活3+眠3 
//		rating = 5000;
//	}
//	else if(live3_ >= 1 || rush4(x,y,color) >= 1) {//活三或者冲4 
//		rating = 500;
//	}
//	else if(live2(x,y,color) >= 2) {//双活2 
//		rating = 50;
//	}
//	else if(mian3(x,y,color) >= 1 || live2(x,y,color) >= 1) {//眠3或活2 
//		rating = 5;
//	}
//	else if(die4(x,y,color) >= 1 || die3(x,y,color) >= 1 || die2(x,y,color)) {//落子成死棋 
//		rating = -5;
//	}
//    for(int i = 0;i < 8; ++i) if(can_luozi(x + dx[i],y + dy[i])) rating += 1;//查看当前落子的周围八个位置，如果能落子就加10分,这个算棋势分数 
//    return rating; + posit_value[x][y];//返回计算分数
}

int jushi_fenshu(int color) {
	int ans = 0;
	bool vis[N][N];
	memset(vis,0,sizeof vis);
	for(int i = 0;i < N; ++i) {
		for(int j = 0;j < N; ++j) {
			if(bord[i][j] != color) continue; 
			for(int k = 0;k < 8; ++k) {
				for(int l = 1;l <= 2; ++l) {
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
int AI_6(int color) {
	int loc_key = INF,temp;
    vector<Node> V;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue; //不能落子
            V.push_back({i,j,fenshu(i,j,3 - color)});
        }
    }
    sort(V.begin(),V.end(),cmpsmall);
    if(V.size())
    	return V[0].point;
    else return 0;
//    for(int i = 0;i < 8 && i < V.size(); ++i) {
//    	bord[V[i].x][V[i].y] = color;
//    	temp = AI_5(3 - color);; //
//    	bord[V[i].x][V[i].y] = 0;
//    	if(temp < loc_key) {	//第四层博弈树取极小 
//            loc_key = temp;
//        }
//	}
//    return loc_key;
} 

int AI_5(int color) {
	return jushi_fenshu(color) - jushi_fenshu(3 - color); //+ jushi_fenshu(3-color);
}

int AI_4(int color) {
int loc_key = INF,temp;
    vector<Node> V;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue; //不能落子
            temp = (fenshu(i,j,color)+ fenshu(i,j,3 - color)); // + fenshu(i,j,3 - color)
//            if(temp >= 100000) return -100000;
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
            temp = (fenshu(i,j,color)+ fenshu(i,j,3 - color)); // + fenshu(i,j,3 - color)
//            if(temp >= 100000) return 100000;
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
            temp = (fenshu(i,j,color) + fenshu(i,j,3 - color)); // + fenshu(i,j,3 - color)
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
    int loc_key = -INF,keyi,keyj,temp;
    vector<Node> V;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue;
            temp = (fenshu(i,j,color) + fenshu(i,j,3 - color) * 2); // + fenshu(i,j,3 - color)
            if(temp >= 100000) return pair<int,int> (i,j);
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
	bord[0][5] = 1;
	printf("%d\n",jushi_fenshu(1));
	
    init();
    int cout = 0;
    if(ai_) {
	    while(!IS_END) {
	    	pair<int,int> aiai = AI_1(1);
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
			pair<int,int> aiai = AI_1(2);
			go(aiai.first,aiai.second,2);
			draw();
		}
	}
	printf("\n总共走了%d步\n",cout);
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

