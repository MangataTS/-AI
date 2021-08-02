/*
�����֡��ڶԾֿ�ʼ�׶��γɵĲ��֡�һ��ָǰ3�����γɵľ��档
������2ö���ϵ�ͬɫ������һ�������ڽӳɴ���
����������öͬɫ������һ�������ڽ�������                               		��
����������ö����ͬɫ������һ�������ڽӳɴ���								�� 
�����塽�����ͳ�����ͳ�ơ�
����в����һ�ֿ��Գ�����߻��ĵĵ㡣
�����ġ���������в���ġ�                                                	��
�����ġ�ֻ��һ����в���ġ�													�� 
�����ġ����ܳ����������													�� 
�����������γ������γ������öͬɫ������ɵ����͡�							�� 
������������һ�ſ����γɻ��ĵ�����   									 	��
�������������˶�����в�Ļ�������ơ���������		 						�� 
�����������м����һ����в�Ļ�������ơ���������							�� 
������������һ�ſ����γɳ��ĵ�����											�� 
�����������ܳ��������														�� 
�����������һ�ſ����γɻ����Ķ���                                       	��
������������Ļ������ơ���������											�� 
����������м����һ���յ�Ļ������ơ���������
������������м���������յ�Ļ������ơ�����������
���߶�������һ�ſ����γ������Ķ���
�����������ܳ���Ķ���
�����֡��Է�����Ӧ����ŷ�������ڻ������ֶ��ԣ����ĳ�Ϊ���������֡���
��������һ������ͬʱ�γ�����������Ҳ�ơ�˫������
�����ġ�һ������ͬʱ�γ��������ġ�Ҳ�ơ�˫�ġ���
��������һ������ͬʱ�γ�һ�����ĺ�һ��������
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


int bord[N][N];//  0��ʾ��ǰΪ�գ�1��ʾ���ӣ�2��ʾ����
int ai_ = 1;//ai_ = 1 ��ʾ����AI����
int s0;
bool IS_END = false; 
const int posit_value[20][20] =	{	//����һ��λ�ü�ֵ�����⵽�����εݼ� 
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
    printf("����1����2����ѡ��\n1��AIִ������\n2�����ִ������\n");
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
    if(color == 0) return 0; //�����ǰ��Ϊ��ֱ�ӷ���0
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
    return IS_END; //�����ǽ���
}


//----------------------------------------------------------------------------------------------�ָ���  
//�����Χ���ǽ�������    ò�Ƶ��˵Ľ��������Լ��ķ��� 
int live2(int x,int y,int color) {//Ŀǰ�����ж�һ�� ���������ڵĻ�2��Ҳ��������2 
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

int die2(int x,int y,int color) {//���ӳ������ĸ���
	int sum = 0;
	for(int k = 0;k < 8; ++k) {
		if(is_inbord(x + dx[k],y + dy[k]) && bord[x + dx[k]][y + dy[k]] == color) {
			if(is_inbord(x + dx[k] * 2,y + dy[k] * 2) && bord[x + dx[k] * 2][y + dy[k] * 2] != 3 - color) continue;//������ڶ�������������ڲ��Ҳ��ǵط����� 
			if(is_inbord(x - dx[k],y - dy[k]) && bord[x - dx[k]][y - dy[k]] != 3 - color) continue; //������������ǵط����ӣ�������������	
			sum++;
		} 
		
	} 
	return sum;
} 

int mian2(int x,int y,int color) {//������2������ 
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

int live3(int x,int y,int color) {//����[x��y]�����ӳɻ�������
    int sum = 0;	
    for(int k = 0,i = 1;k < 4; ++k) {//�ĸ�����Ѱ��  ������
        int loc = 1;
        int fg = 2;//��ʾ�ܹ��ɻ����Ŀ���
        //�������ҹ�ȥ
        for(i = 1;issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//�����ǰλ�ò��ǿ�λ˵�����ɻ����Ŀ��ܼ�һ
        i++;
		if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//�����ǰλ�ò��ǿ�λ˵�����ɻ����Ŀ��ܼ�һ
        //�������ҹ�ȥ
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//�����ǰλ�ò��ǿ�λ˵�����ɻ����Ŀ��ܼ�һ
        i--;
		if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//�����ǰλ�ò��ǿ�λ˵�����ɻ����Ŀ��ܼ�һ
        if(loc == 3 && fg == 1) //���ɻ���
            sum++;
    }
    for(int k = 0;k < 8; ++k) {  //�м��һ��Ļ���Ҳ����������  eg: 011010
    	int loc = 0;
    	int kong = 0;
    	int feikong = 0;
    	if(!is_inbord(x + dx[k + 4],y + dy[k + 4])) continue; // ���ڱ߽� 
    	else if(bord[x + dx[k + 4]][y + dy[k + 4]] != color) continue;//��������color
    	if(!is_inbord(x + dx[k + 4] * 2,y + dy[k + 4] * 2)) continue; // ���ڱ߽� 
    	else if(bord[x + dx[k + 4] * 2][y + dy[k + 4] *2] == 0) continue;//�������ǿյ� 
    	for(int i = 1;i <= 3; ++i) {		//���������3�� 
    		if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) break;
    		if(bord[x + dx[k] * i][y + dy[k] * i] == 3 - color) //�͵з�������� 
				break;
			if(bord[x + dx[k] * i][y + dy[k] * i] == color) feikong++;
			else kong++;
		}
		if(kong == 2 && feikong == 1) //�������� 
			sum++;
	}
    return sum;
}

int mian3(int x,int y,int color) {//��[x,y]���λ���γɵ����������� 
	int sum = 0;
    for(int k = 0,i = 1;k < 4; ++k) {//�ĸ�����Ѱ������
        int loc = 1;
        int fg = 2;//��ʾ�ܹ�����3�Ŀ���
        //�������ҹ�ȥ
        for(i = 1;issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//������˱߽���ôfg--
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//�����ǰλ�ò��ǿ�λ˵�����ɻ����Ŀ��ܼ�һ
        //�������ҹ�ȥ
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//������˱߽���ôfg--
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//�����ǰλ�ò��ǿ�λ˵�����ɻ����Ŀ��ܼ�һ

        if(loc == 3 && fg == 1) //������3
            sum++;
    }
    return sum;
}

int die3(int x,int y,int color) {//���ӳ������ĸ���
	int sum = 0;
	for(int k = 0,i = 1;k < 4; ++k) {
		int loc = 0; 
		for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color) && loc < 3; ++i) loc++;
		if(is_inbord(x + dx[k] * i,y + dy[k] * i) && bord[x + dx[k] * i][y + dy[k] * i] != 3 - color) continue; //�����һ�������������ڣ�����������һ��λ�ò�Ϊ��һ������ 
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color) && loc < 3; --i) loc++;
		if(is_inbord(x + dx[k] * i,y + dy[k] * i) && bord[x + dx[k] * i][y + dy[k] * i] != 3 - color) continue; //�����һ�������������ڣ�����������һ��λ�ò�Ϊ��һ������ 
		if(loc == 2)//������� ���������� 
			sum++; 
	} 
	return sum;
} 

int live4(int x,int y,int color) {//���ӳɻ��ĵĸ��� Ŀǰֻ����������4 ������4���д����� 
    int sum = 0;
    for(int k = 0,i = 1;k < 4;++k) {//����4 
        int loc = 0;
        for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color) && loc < 4; ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//�����ǰλ�ò��ǿ�λ��continue

        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color) && loc < 4; --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//�����ǰλ�ò��ǿ�λ��continue

        if(loc == 3) sum++;
    }
    return sum;
}

int die4(int x,int y,int color) {//���ӳ����ĵĸ���
	int sum = 0;
	for(int k = 0,i = 1;k < 4; ++k) {
		int loc = 0;
		for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color) && loc < 4; ++i) loc++;
		if(is_inbord(x + dx[k] * i,y + dy[k] * i) && bord[x + dx[k] * i][y + dy[k] * i] != 3 - color) continue; //�����һ�������������ڣ�����������һ��λ�ò�Ϊ��һ������ 
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color) && loc < 4; --i) loc++;
		if(is_inbord(x + dx[k] * i,y + dy[k] * i) && bord[x + dx[k] * i][y + dy[k] * i] != 3 - color) continue; //�����һ�������������ڣ�����������һ��λ�ò�Ϊ��һ������ 
		if(loc == 3)
			sum++;
	} 
	return sum;
} 

int cheng5(int x,int y,int color) {//���ӳ�5�ĸ���
    int sum = 0;
    for(int k = 0,i = 1;k < 4;++k) {
        int loc = 1;
        for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(loc == 5) return ++sum;
    }
    return sum;
}

int changlian(int x,int y,int color) {//���ӳ����ĸ��� 
	int sum = 0;
    for(int k = 0,i = 1;k < 4;++k) {
        int loc = 1;
        for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(loc > 5) return ++sum;
    }
    return sum;
} 

int rush4(int x,int y,int color) {//���ӳɵ���4�ĸ���
    int sum = 0;
    for(int k = 0,i = 1;k < 4; ++k) {//�ĸ�����Ѱ�һ���
        int loc = 1;
        int fg = 2;//��ʾ�ܹ��ɳ�4�Ŀ���
        //�������ҹ�ȥ
        for(i = 1;issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//�����ǰλ�ò��ǿ�λ˵�����ɻ����Ŀ��ܼ�һ
        //�������ҹ�ȥ
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//�����ǰλ�ò��ǿ�λ˵�����ɻ����Ŀ��ܼ�һ
        if(loc == 4 && fg == 1) //���ɵ���4
            sum++;
    }
    return sum;
}
//----------------------------------------------------------------------------------------------�ָ���  

void go(int x,int y,int color) {
    bord[x][y] = color;//����
    if(ai_ == 1 && color == 1 || ai_ == 0 && color == 2)
    	printf("AI����    x = %d, y = %d\n",x,y);
    else 
    	printf("�������  x = %d, y = %d\n",x,y);
    if(is_end(x,y)) {
        if(ai_ == 1 && color == 1 || ai_ == 0 && color == 2) printf("AIʤ��\n");
        else printf("���ʤ��\n");
        return ;
    }
    
}

int fenshu(int x,int y,int color) {//�Ե�ǰ[x,y]�������ӵļ�ֵ�������� 
//	int win5 = 0, alive4 = 0, die4 = 0, lowdie4 = 0, alive3 = 0,
//		die3 = 0, tiao3 = 0, alive2 = 0, lowalive2 = 0, die2 = 0, nothing = 0;
	
//	win5 = cheng5(x,y,color) + changlian(x,y,color);
//	alive4 = live4(x,y,color);
//	die4 = deie
    int live3_ = live3(x,y,color);
    int rating; 
    if(changlian(x,y,color) >= 1 || cheng5(x,y,color) >= 1) { //�����ͳ��巵��  
    	return 100000;
	}
	else if(live4(x,y,color) >= 1 || rush4(x,y,color) >= 2 || (rush4(x,y,color) >= 1 && live3_ >= 1) || live3_ >= 2) { //�����γɻ��Ļ���������4����һ����4��һ������Ҳ�������� ������˫���� 
		return 10000;
	}
	rating = (live3_ + rush4(x,y,color))* 1000 + (mian3(x,y,color) + live2(x,y,color))* 20 +  (die4(x,y,color) + die3(x,y,color) + die2(x,y,color)) * (-10);
	return rating;
//	else if(live3_ >= 1 && mian3(x,y,color) >= 1) { //��3+��3 
//		rating = 5000;
//	}
//	else if(live3_ >= 1 || rush4(x,y,color) >= 1) {//�������߳�4 
//		rating = 500;
//	}
//	else if(live2(x,y,color) >= 2) {//˫��2 
//		rating = 50;
//	}
//	else if(mian3(x,y,color) >= 1 || live2(x,y,color) >= 1) {//��3���2 
//		rating = 5;
//	}
//	else if(die4(x,y,color) >= 1 || die3(x,y,color) >= 1 || die2(x,y,color)) {//���ӳ����� 
//		rating = -5;
//	}
//    for(int i = 0;i < 8; ++i) if(can_luozi(x + dx[i],y + dy[i])) rating += 1;//�鿴��ǰ���ӵ���Χ�˸�λ�ã���������Ӿͼ�10��,��������Ʒ��� 
//    return rating; + posit_value[x][y];//���ؼ������
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
					if(is_inbord(i + dx[k] * l,j + dy[k] * l) && bord[i + dx[k] * l][j + dy[k] * l] == 0 && vis[i + dx[k] * l][j + dy[k] * l] == false) { //�������ڲ��������Ϊ�� 
						ans += fenshu(i + dx[k] * l,j + dy[k] * l,color);
						vis[i + dx[k] * l][j + dy[k] * l] = true;
					}
				}
			}
		}
	}
	return ans;
} 

//Ŀǰ��AI�����ǽ���
int AI_6(int color) {
	int loc_key = INF,temp;
    vector<Node> V;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue; //��������
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
//    	if(temp < loc_key) {	//���Ĳ㲩����ȡ��С 
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
            if(!can_luozi(i,j)) continue; //��������
            temp = (fenshu(i,j,color)+ fenshu(i,j,3 - color)); // + fenshu(i,j,3 - color)
//            if(temp >= 100000) return -100000;
            V.push_back({i,j,temp});
        }
    }
    sort(V.begin(),V.end(),cmpbig);
    for(int i = 0,len = V.size();i < NUM && i < len; ++i) { // ������ӵ� 
    	bord[V[i].x][V[i].y] = color;
    	temp = AI_5(3 - color);
    	bord[V[i].x][V[i].y] = 0;
    	if(temp < loc_key) {	//���Ĳ㲩����ȡ��С
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
    for(int i = 0,len = V.size();i < NUM && i < len; ++i) {// ������ӵ� 
    	bord[V[i].x][V[i].y] = color;
    	temp = AI_4(3 - color);
    	bord[V[i].x][V[i].y] = 0;
    	if(temp > loc_key) {//�����㲩����ȡ����
            loc_key = temp;
        }
	}
    return loc_key;
}//������AI

int AI_2(int color) {
    int loc_key = INF,temp;
    vector<Node> V;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue; //��������
            temp = (fenshu(i,j,color) + fenshu(i,j,3 - color)); // + fenshu(i,j,3 - color)
//            if(temp >= 100000) return -100000;
            V.push_back({i,j,temp});
        }
    }
    sort(V.begin(),V.end(),cmpbig);
    for(int i = 0,len = V.size();i < NUM && i < len; ++i) {// ������ӵ� 
    	bord[V[i].x][V[i].y] = color;
    	temp = AI_3(3 - color);
    	bord[V[i].x][V[i].y] = 0;
    	if(temp < loc_key) {	//�ڶ��㲩����ȡ��С
            loc_key = temp;
        }
	}
    return loc_key;
}//�ڶ���AI

pair<int,int> AI_1(int color) {
    if(bord[7][7] == 0) return pair<int,int>(7,7); //�����Ԫû�����ӣ���ô������Ԫ
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
    for(int i = 0,len = V.size();i < NUM && i < len; ++i) {// ������ӵ� 
    	bord[V[i].x][V[i].y] = color;
    	temp = AI_2(3 - color);
    	bord[V[i].x][V[i].y] = 0;
    	if(temp > loc_key) {//��һ�㲩����ȡ����
            loc_key = temp;
            keyi = V[i].x,keyj = V[i].y;
        }
	}
    printf("loc_key = %d,x = %d,y = %d\n",loc_key,keyi,keyj);
    return pair<int,int> (keyi,keyj);
}//��һ��AI




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
	printf("��������������\n"); 
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
	printf("\n�ܹ�����%d��\n",cout);
	puts("\n-------------game over------------------");
	puts("-------------�ָ���------------------");
	puts("-------------�ָ���------------------");
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

