/*
�����֡��ڶԾֿ�ʼ�׶��γɵĲ��֡�һ��ָǰ3�����γɵľ��档
������2ö���ϵ�ͬɫ������һ�������ڽӳɴ���
����������öͬɫ������һ�������ڽ�������
����������ö����ͬɫ������һ�������ڽӳɴ���
�����塽�����ͳ�����ͳ�ơ�
����в����һ�ֿ��Գ�����߻��ĵĵ㡣
���ġ�����ȥ��1�ӵ����͡�
�����ġ���������в���ġ�
�����ġ�ֻ��һ����в���ġ�												�� 
�����ġ����ܳ����������
�����������γ������γ������öͬɫ������ɵ����͡�
������������һ�ſ����γɻ��ĵ�����   									��
�������������˶�����в�Ļ�������ơ���������		 
�����������м����һ����в�Ļ�������ơ���������
������������һ�ſ����γɳ��ĵ�����
�����������ܳ��������
�����������γ�������ֱ�������öͬɫ������ɵ����͡�
�����������һ�ſ����γɻ����Ķ���
������������Ļ������ơ���������
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

int bord[N][N];//  0��ʾ��ǰΪ�գ�1��ʾ���ӣ�2��ʾ����
int ai_ = 1;//ai_ = 1 ��ʾ����AI����
int s0;
bool IS_END = false; 

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
    return bord[x][y] == k || bord[x][y] + k == 0;
}

bool sum_num_of_same(int x,int y,int k) {
    int i = x + dx[k],j = y + dy[k];
    int sum = 0;
    int color = bord[x][y];
    if(color == 0) return 0; //�����ǰ��Ϊ��ֱ�ӷ���0
    if(issame(i,j,color)) sum++,i+=dx[k],j+=dy[k];
    return sum;
}

bool is_end(int x,int y) {
    for(int k = 0;k < 4; ++k)
        if(sum_num_of_same(x,y,k) + sum_num_of_same(x,y,k + 4) >= 4) IS_END = true;
    return IS_END; //�����ǽ���
}


//----------------------------------------------------------------------------------------------�ָ���  
//�����Χ���ǽ������� 
int live2(int x,int y,int color) {
	int key = bord[x][y],sum = 0;
	for(int k = 0,i = 1;k < 4; ++k) {
		int loc = 1;
		int fg = 2;
		if()
		
	}
}

int live3(int x,int y,int color) {//����[x��y]�����ӳɻ�������
    int sum = 0;
    for(int k = 0,i = 1;k < 4; ++k) {//�ĸ�����Ѱ�һ���
        int loc = 1;
        int fg = 2;//��ʾ�ܹ��ɻ����Ŀ���
        //�������ҹ�ȥ
        for(i = 1;issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//�����ǰλ�ò��ǿ�λ��continue
        i++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//�����ǰλ�ò��ǿ�λ˵�����ɻ����Ŀ��ܼ�һ
        //�������ҹ�ȥ
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//�����ǰλ�ò��ǿ�λ��continue
        i++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//�����ǰλ�ò��ǿ�λ˵�����ɻ����Ŀ��ܼ�һ
        if(loc == 3 && fg > 0) //���ɻ���
            sum++;
    }
    return sum;
}

int live4(int x,int y,int color) {//���ӳɻ��ĵĸ���
    int sum = 0;
    for(int k = 0,i = 1;k < 4;++k) {
        int loc = 1;
        for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//�����ǰλ�ò��ǿ�λ��continue

        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) continue;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) continue;//�����ǰλ�ò��ǿ�λ��continue

        if(loc == 4) sum++;
    }
    return sum;
}

int cheng5(int x,int y,int color) {//���ӳ�5�ĸ���
    int sum = 0;
    for(int k = 0,i = 1;k < 4;++k) {
        int loc = 1;
        for(i = 1; issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(loc == 5) sum++;
    }
    return sum;
}

int rush4(int x,int y,int color) {//���ӳɳ�4�ĸ���
    int sum = 0;
    for(int k = 0,i = 1;k < 4; ++k) {//�ĸ�����Ѱ�һ���
        int loc = 1;
        int fg = 2;//��ʾ�ܹ��ɻ����Ŀ���
        //�������ҹ�ȥ
        for(i = 1;issame(x + dx[k] * i,y + dy[k] * i,color); ++i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//�����ǰλ�ò��ǿ�λ˵�����ɻ����Ŀ��ܼ�һ
        //�������ҹ�ȥ
        for(i = -1;issame(x + dx[k] * i,y + dy[k] * i,color); --i) loc++;
        if(!is_inbord(x + dx[k] * i,y + dy[k] * i)) fg--;//������˱߽���ôֱ��continue��
        else if(bord[x + dx[k] * i][y + dy[k] * i] != 0) fg--;//�����ǰλ�ò��ǿ�λ˵�����ɻ����Ŀ��ܼ�һ

        if(loc == 4 && fg > 0) //���ɻ���
            sum++;
    }
    return sum;
}
//----------------------------------------------------------------------------------------------�ָ���  

void go(int x,int y,int color) {
    bord[x][y] = color;//����
    if(is_end(x,y)) {
        if(ai_ == 1 && color == 1 || ai_ == 0 && color == 2) printf("AIʤ��");
        else printf("���ʤ��");
    }
    printf("����  x = %d, y = %d\n",x,y);
}

int fenshu(int x,int y,int color) {
    //if(ban(x,y)) return 0;//����ǽ��ַ���0��
    if(is_end(x,y)) { //�����ֱ�ӽ�����Ϸ����ôֱ�ӷ������Ȩֵ
        return 10000;
    }
    int rating = live4(x,y,color) * 1000 + live3(x,y,color) * 500 + rush4(x,y,color) * 100;
    for(int i = 0;i < 8; ++i) if(can_luozi(x + dx[i],y + dy[i])) rating += 10;//�鿴��ǰ���ӵ���Χ�˸�λ�ã���������Ӿͼ�10��
    return rating;//���ؼ������
}

//Ŀǰ��AI�����ǽ���

int AI_3(int kk,int color) {
    int loc_key = -100000,temp;
    for(int i = 0;i  < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue;
            bord[i][j] = color;
            temp = fenshu(i,j,color);
            if(temp == 0) {//�ܿ���Ч��
                bord[i][j] = 0;
                continue;
            }
            if(temp  == 10000) {
                bord[i][j] = 0;
                return 10000;
            }
            bord[i][j] = 0;
            if(temp - kk * 2 > loc_key) { //�����㲩����ȡ����ֵ
                loc_key = temp - kk * 2;
            }
        }
    }
    return loc_key;
}//������AI

int AI_2(int color) {
    int loc_key = 100000,temp;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue; //��������
            bord[i][j] = color;
            temp = fenshu(i,j,color);
            if(temp == 0) {//�ܿ���Ч��
                bord[i][j] = 0;
                continue;
            }
            if(temp == 10000) {//������ڵڶ����ҵ��˱�ʤ�㣬��ô���ظ�ֵ
                bord[i][j] = 0;
                return -10000;
            }
            temp = AI_3(temp,3 - color);
            bord[i][j] = 0;
            if(temp < loc_key) loc_key = temp; //�ڶ��㲩����ȡ��Сֵ
        }
    }
    return loc_key;
}//�ڶ���AI

pair<int,int> AI_1(int color) {
    if(bord[7][7] == 0) return pair<int,int>(7,7); //�����Ԫû�����ӣ���ô������Ԫ
    int loc_key = -100000,keyi,keyj,temp;
    for(int i = 0;i < N; ++i) {
        for(int j = 0;j < N; ++j) {
            if(!can_luozi(i,j)) continue;
            bord[i][j] = color;
            temp = fenshu(i,j,color);
            if(temp == 0) { //��֦���ܿ���Ч��
                bord[i][j] = 0;
                continue;
            }
            if(temp == 10000) {
                bord[i][j] = 0;
                return pair<int, int>(i, j); //����Ѿ��ҵ���ʤ�㣬��ôֱ�ӷ��ص�ǰ��ֵ
            }
            temp = AI_2(3 - color);
            bord[i][j] = 0;
            if(temp > loc_key) {//��һ�㲩����ȡ����
                loc_key = temp;
                keyi = i,keyj = j;
            }
        }
    }
    printf("loc_key = %d,x = %d,y = %d\n",loc_key,keyi,keyj);
    return pair<int,int> (keyi,keyj);
}//��һ��AI

void draw() {
	printf("\n\n");
	printf(" ");
	for(int i = 0;i < N; ++i) printf(" %d ",i);
	puts("");
	for(int i = 0;i < N; ++i) {
		printf("%d ",i);
		for(int j = 0;j < N; ++j) {
			if(bord[i][j] == 1) printf("X ");
			else if(bord[i][j] == 2) printf("O ");
			else printf("  ");
		}
		puts("");
	}
	printf("\n\n");
}

void play(int color) {
	int x,y;
	scanf("%d %d",&x,&y);
	go(x,y,color);
}
int main() {
    init();
    if(ai_) {
	    while(!IS_END) {
	    	pair<int,int> aiai = AI_1(1);
			go(aiai.first,aiai.second,1);
			draw();
	    	play(2);
		}
	}
	else {
		while(!IS_END) {
			play(1);
			pair<int,int> aiai = AI_1(2);
			go(aiai.first,aiai.second,2);
			draw();
		}
	}
}


