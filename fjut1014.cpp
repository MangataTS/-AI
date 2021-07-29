/*
〖开局〗在对局开始阶段形成的布局。一般指前3手棋形成的局面。
〖连〗2枚以上的同色棋子在一条线上邻接成串。
〖五连〗五枚同色棋子在一条线上邻接连串。                                √
〖长连〗五枚以上同色棋子在一条线上邻接成串。
〖成五〗五连和长连的统称。
〖威胁〗下一手可以成五或者活四的点。
〖四〗五连去掉1子的棋型。
〖活四〗有两个威胁的四。                                                √
〖冲四〗只有一个威胁的四。												√ 
〖死四〗不能成五的四连。
〖三〗可以形成四再形成五的三枚同色棋子组成的棋型。
〖活三〗再走一着可以形成活四的三。   									 √
〖连活三〗两端都是威胁的活三。简称“连三”。		 
〖跳活三〗中间夹有一个威胁的活三。简称“跳三”。
〖眠三〗再走一着可以形成冲四的三。
〖死三〗不能成五的三。
〖二〗可以形成三、四直至五的两枚同色棋子组成的棋型。
〖活二〗再走一着可以形成活三的二。                                       √
〖连活二〗连的活二。简称“连二”。
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

int bord[N][N];//  0表示当前为空，1表示黑子，2表示白子
int ai_ = 1;//ai_ = 1 表示的是AI先手
int s0;
bool IS_END = false; 

int dx[8] = {0,-1,-1,-1,0,1,1,1};
int dy[8] = {-1,-1,0,1,1,1,0,-1};

void init() {
	int seed;
    scanf("%d",&seed);
    srand(seed);
    int col,row;
    scanf("%d%d",&col,&row);
//    printf("输入1或者2进行选择\n1，AI执黑先行\n2，玩家执黑先行\n");
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
//    	printf("sum_p = %d\n",p);
    	if(p >= 4)
        	IS_END = true;
	}
    
        
			
    return IS_END; //不考虑禁手
}


//----------------------------------------------------------------------------------------------分割线  
//这个范围内是进攻函数 
int live2(int x,int y,int color) {//目前粗略判断一下 
	int sum = 0;
	for(int k = 0,i = 1;k < 4; ++k) {
		int loc = 1;
		int fg = 2;
		if(is_inbord(x + dx[k],y + dy[k]) && is_inbord(x + dx[k + 4],y + dy[k + 4]) && bord[x + dx[k]][y + dy[k]] == color && bord[x + dx[k + 4]][y + dy[k + 4]] == color) {
			continue;
		}
		else if(is_inbord(x + dx[k],y + dy[k]) && bord[x + dx[k]][y + dy[k]] == color) {
			int kong = 0;
			for(int i = 1;is_inbord(x + dx[k] * i,y + dy[k] * i) && issame(x + dx[k] * i,y + dy[k] * i,0); ++i) kong++;
			for(int i = -1; is_inbord(x + dx[k] * i,y + dy[k] * i) && issame(x + dx[k] * i,y + dy[k] * i,0);--i) kong++;
			if(kong >= 3) sum++;
		}
		else if(is_inbord(x + dx[k],y + dy[k]) && bord[x + dx[k + 4]][y + dy[k + 4]] == color) {
            int kong = 0;
            for (int i = 1;
                 is_inbord(x + dx[k] * i, y + dy[k] * i) && issame(x + dx[k] * i, y + dy[k] * i, 0); ++i)
                kong++;
            for (int i = -1;
                 is_inbord(x + dx[k] * i, y + dy[k] * i) && issame(x + dx[k] * i, y + dy[k] * i, 0); --i)
                kong++;
            if (kong >= 3) sum++;
        }
	}
	return sum;
}

int live3(int x,int y,int color) {//计算[x、y]点落子成活三个数
    int sum = 0;
    for(int k = 0,i = 1;k < 4; ++k) {//四个方向寻找活三
        int loc = 1;
        int fg = 2;//表示能构成活三的可能
        //正方向找过去
        for(i = 1;issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//如果当前位置不是空位就continue
        i++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一
        //反方向找过去
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
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

int live4(int x,int y,int color) {//落子成活四的个数
    int sum = 0;
    for(int k = 0,i = 1;k < 4;++k) {
        int loc = 1;
        for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//如果当前位置不是空位就continue

        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//如果当前位置不是空位就continue

        if(loc == 4) sum++;
    }
    return sum;
}

int cheng5(int x,int y,int color) {//落子成5的个数
    int sum = 0;
    for(int k = 0,i = 1;k < 4;++k) {
        int loc = 1;
        for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(loc == 5) sum++;
    }
    return sum;
}

int rush4(int x,int y,int color) {//落子成冲4的个数
    int sum = 0;
    for(int k = 0,i = 1;k < 4; ++k) {//四个方向寻找活三
        int loc = 1;
        int fg = 2;//表示能构成活三的可能
        //正方向找过去
        for(i = 1;issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一
        //反方向找过去
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//如果出了边界那么直接continue；
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//如果当前位置不是空位说明构成活三的可能减一

        if(loc == 4 && fg > 0) //构成活三
            sum++;
    }
    return sum;
}
//----------------------------------------------------------------------------------------------分割线  

void go(int x,int y,int color) {
    bord[x][y] = color;//落子
//    if(is_end(x,y)) {
//        if(ai_ == 1 && color == 1 || ai_ == 0 && color == 2) printf("AI胜利\n");
//        else printf("玩家胜利\n");
//        return ;
//    }
//    if(ai_ == 1 && color == 1 || ai_ == 0 && color == 2)
//    	printf("AI落子    x = %d, y = %d\n",x,y);
//    else 
//    	printf("玩家落子  x = %d, y = %d\n",x,y);
}

int fenshu(int x,int y,int color) {
    //if(ban(x,y)) return 0;//如果是禁手返回0分
    if(is_end(x,y)) { //如果能直接结束游戏，那么直接返回最高权值
    	IS_END = false;
        return 10000;
    }
    int rating =cheng5(x,y,color) * 2000 + live2(x,y,color) * 50  + live4(x,y,color) * 1000 + live3(x,y,color) * 800 +rush4(x,y,color) * 100;
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
            temp = fenshu(i,j,color) + fenshu(i,j,3 - color);
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
            temp = fenshu(i,j,color) + fenshu(i,j,3 - color);
            
            if(temp < loc_key) loc_key = temp; //第二层博弈树取极小值
            
            if(temp == 0) {//避开无效点
                bord[i][j] = 0;
                continue;
            }
            if(temp == 10000) {//如果对于第二层找到了必胜点，那么返回负值
                bord[i][j] = 0;
                return -10000;
            }
//            temp = AI_3(temp,3 - color);
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
            temp = fenshu(i,j,color) + fenshu(i,j,3 - color) * 2;
//            if(temp > loc_key) {//第一层博弈树取极大
//                loc_key = temp;
//                keyi = i,keyj = j;
//            }
            if(temp == 0) { //剪枝，避开无效点
                bord[i][j] = 0;
                continue;
            }
            if(temp == 10000) {
                bord[i][j] = 0;
                return pair<int, int>(i, j); //如果已经找到必胜点，那么直接返回当前的值
            }
            temp += AI_2(3 - color);
            bord[i][j] = 0;
            if(temp > loc_key) {//第一层博弈树取极大
                loc_key = temp;
                keyi = i,keyj = j;
            }
        }
    }
//    printf("loc_key = %d,x = %d,y = %d\n",loc_key,keyi,keyj);
    return pair<int,int> (keyi,keyj);
}//第一层AI

void draw() {
	printf("\n\n");
	printf("         ");
	printf(" ");
	for(int i = 0;i < N; ++i) if(i < 10) printf("   %d",i); else printf("  %d",i);
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
			if(bord[i][j] == 1) printf("|X  ");
			else if(bord[i][j] == 2) printf("|O  ");
			else printf("|   ");
		}
		puts("");
	}
	printf("\n\n");
}

void play(int color) {
	int x,y;
//	printf("请输入落子坐标\n"); 
	scanf("%d %d",&x,&y);
	if(is_inbord(x,y) && bord[x][y] == 0)
		go(x,y,color);
	else return play(color);
}
int main() {
    init();
    if(ai_) {
	    while(!IS_END) {
	    	pair<int,int> aiai = AI_1(1);
			go(aiai.first,aiai.second,1);
			printf("%d\n",aiai.first);
			printf("%d\n",aiai.second);
			fflush(stdout);
//			if(IS_END) {
//				draw();
//				system("pause");
//				return 0;
//			}
				
//			draw();
	    	play(2);
		}
	}
	else {
		while(!IS_END) {
			play(1);
			pair<int,int> aiai = AI_1(2);
			go(aiai.first,aiai.second,2);
			printf("%d\n",aiai.first);
			printf("%d\n",aiai.second);
			fflush(stdout);
//			draw();
		}
	}
}


