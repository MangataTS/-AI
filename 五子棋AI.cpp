#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define bwin 1
#define wwin -1
#define noover 0

const int attack_key[6] ={0,10,100,1000,10000,999999};//�ֱ��Ӧ�ŵ�������������Ӹ����Ľ�����ֵ 
const int defense_key[6] = {0,30,100,9999999,9999999,999999};//�ֱ��Ӧ��������������ӵķ�����ֵ 
const int N = 7 + 1;
int dx[8] = {0,-1,-1,-1,0,1,1,1};
int dy[8] = {-1,-1,0,1,1,1,0,-1};
int own = 0;

int bord[N][N];
int bord_key[N][N];//�������̵Ĺ�ֵ����ֵ


void out(int x,int y) {
	if(bord[x][y] == 0) putchar(' ');
	else if(bord[x][y] == 1) putchar('A'); //���� 
	else if(bord[x][y] == -1) putchar('B'); //���� 
}

void init() {//���̳�ʼ�� 
	for(int i = 1;i < N; ++i) {
		for(int j = 1;j < N; ++j) {
			bord[i][j] = 0;		
		}
	}
}

void display() {//��ʾ���� 
	system("cls");
	for(int i = 1;i < N; ++i) {
		for(int j = 1;j < N; ++j) {
			out(i,j);
			putchar(' ');
		}
		puts("");
	}
	puts("-------------------------------");
	for(int i = 1;i < N; ++i) {
		for(int j = 1;j < N; ++j) {
			printf("%d\t",bord_key[i][j]);
		}
		puts("");
	}
//	for(int k = 1;k < N; ++k) printf("--");
//	putchar('\n');
//	for(int i = 1;i < N; ++i) {
//		putchar('|');
//		for(int j = 1;j < N; ++j) {
//			out(i,j);
//			putchar('|');
//		}
//		putchar('\n');
//		for(int k = 1;k < N ; ++k) printf("--");
//		putchar('\n');
//	}
}

//int check(int x,int y) {
//	for(int i = 1;i < N; ++i) {
//		int wh = 0,bl = 0;
//		int wh_row = 0,bl_row = 0; 
//		for(int j = 1;j < N; ++j) { // ˮƽ�ʹ�ֱ��� 
//			if(bord[j][i] == 'O') { //��ֱ���� 
//				if(bord[j][i - 1] == 'O') bl_row++;
//				else bl_row = 1;
//			}else if(bord[j][i] == 'X') {
//				if(bord[j][i - 1] == 'X') wh_row++;
//				else wh_row = 1;
//			}
//			else wh_row = bl_row = 0;
//			
//			if(bord[i][j] =='O') {//ˮƽ���� 
//				if(bord[i][j - 1] == 'O') bl++;
//				else bl = 1;
//			}
//			else if(bord[i][j] == 'X') {
//				if(bord[i][j - 1] == 'X') wh++;
//				else wh = 1;
//			}
//			else wh = bl = 0;
//			if(wh == 5 || wh_row == 5) return wwin;
//			if(bl == 5 || bl_row == 5) return bwin;
//		}
//		
//		for(int i = 1;i < N - 5; ++i) {
//			int wh_row = 0,bl_row = 0;
//			int wh_line = 0,bl_line = 0;
//			for(int j = 1,k = i;j < N - i; ++j,++k) {
//				
//			}
//		}
//	}
//	return noover;
//}

int evaluate_attack(int x,int y,int c) { //������ֵ���� 
	int i = x,j = y;
	int ans = 0; 
	
	//��ֱ 
	int cnt = 0;
	if(i + 1 < N) {
		i++;
	}
	while(i < N && bord[i][j] == c) {//������ 
		i++;
		cnt++;
	}
	i = x;
	if(i > 1) {
		i--;
	}
	while(i >= 1 && bord[i][j] == c) {//������ 
		i--;
		cnt++;
	}
	ans = max(ans,cnt);
	
	//ˮƽ����
	i = x,j = y;
	cnt = 0;
	if(j + 1 < N) {
		j++;
	}
	while(j < N && bord[i][j] == c) { //������ 
		j++;
		cnt++;
	}
	j = y;
	if(j > 1) {
		j--;
	}
	while(j >= 1 && bord[i][j] == c) {
		j--;
		cnt++;
	}
	ans = max(ans,cnt);
	
	//������������ 
	cnt = 0; 
	i = x,j = y;
	if(i > 1 && j > 1) {
		i--,j--;
	}
	while(i >= 1 && j >= 1 && bord[i][j] == c) { //�������� 
		i--,j--;
		cnt++;
	}
	
	i = x,j = y;
	if(i + 1 < N && j + 1 < N) {
		i++,j++;
	}
	while(i < N && j < N && bord[i][j] == c) { //�������� 
		i++,j++;
		cnt++;
	}
	ans = max(ans,cnt);
	
	//������������
	cnt = 0;
	i = x,j = y;
	if(i > 1 && j + 1 < N) {
		i--,j++;
	} 
	while(i >= 1 && j < N && bord[i][j] == c) {
		i--,j++;
		cnt++;
	}
	i = x,j = y;
	if(i + 1 < N && j > 1) {
		i++,j--;
	}
	while(i < N && j >= 1 && bord[i][j] == c) {
		i++,j--;
		cnt++;
	}
	ans = max(ans,cnt);
	
	int des = 0;
	
	if((x == 1 || x == N - 1 || y == 1 || y == N - 1 ) && ans <= 3) des = 999999;
	
	
	return max(0,attack_key[min(ans,5)]);
//	int i = x,j = y;
//	bord[i][j] = c;
//	int ans = 0;
//	//��ֱ������������� 
//	int cnt = 0;
//	while(i >= 1 && bord[i][j] == c) {//������ 
//		cnt++;
//		i--;
//	}
//	i = x;
//	while(i < N && bord[i][j] == c) {//������ 
//		cnt++;
//		i++;
//	}
//	ans = max(ans,cnt);
//	//ˮƽ������������� 
//	i = x;
//	cnt = 0;
//	while(j >= 1 && bord[i][j] == c) {//������ 
//		cnt++;
//		j--;
//	}
//	while(j < N && bord[i][j] == c) {//������ 
//		cnt++;
//		j++;
//	}
//	ans = max(ans,cnt);
//	
//	//���Խ��߷��� 
//	cnt = 0;
//	i = x,j = y; 
//	while(i >= 1 && j >=1 && bord[i][j] == c) {//�������������� 
//		cnt++;
//		i--,j--;
//	}
//	ans = max(ans,cnt);
//	i = x,j = y;
//	while(i < N && j < N && bord[i][j] == c) {//��������������
//		cnt++;
//		i++,j++;
//	}
//	ans = max(ans,cnt);
//	
//	
//	//��Խ��߷��� 
//	i = x,j = y;
//	cnt = 0;
//	while(i >= 1 && j < N && bord[i][j] == c) {//��������������
//		cnt++;
//		i--,j++;
//	}
//	while(i < N && j >= 1 && bord[i][j] == c) {//��������������
//		cnt++;
//		i++,j--; 
//	}
//	ans = max(ans,cnt);
//	bord[x][y] = 0;
//	return attack_key[min(ans,5)];//����һ������(i,j)���ļ�ֵ��������33��44���������ֵȹ��� 
}

int evaluate_defense(int x,int y,int c) {
	int i = x,j = y;
	int ans = 0; 
	
	//��ֱ 
	int cnt = 0;
	if(i + 1 < N) {
		i++;
	}
	while(i < N && bord[i][j] == -c) {//������ 
		i++;
		cnt++;
	}
	i = x;
	if(i > 1) {
		i--;
	}
	while(i >= 1 && bord[i][j] == -c) {//������ 
		i--;
		cnt++;
	}
	ans = max(ans,cnt);
	
	//ˮƽ����
	i = x,j = y;
	cnt = 0;
	if(j + 1 < N) {
		j++;
	}
	while(j < N && bord[i][j] == -c) { //������ 
		j++;
		cnt++;
	}
	j = y;
	if(j > 1) {
		j--;
	}
	while(j >= 1 && bord[i][j] == -c) {
		j--;
		cnt++;
	}
	ans = max(ans,cnt);
	
	//������������ 
	cnt = 0; 
	i = x,j = y;
	if(i > 1 && j > 1) {
		i--,j--;
	}
	while(i >= 1 && j >= 1 && bord[i][j] == -c) { //�������� 
		i--,j--;
		cnt++;
	}
	
	i = x,j = y;
	if(i + 1 < N && j + 1 < N) {
		i++,j++;
	}
	while(i < N && j < N && bord[i][j] == -c) { //�������� 
		i++,j++;
		cnt++;
	}
	ans = max(ans,cnt);
	
	//������������
	i = x,j = y;
	cnt = 0;
	if(i > 1 && j + 1 < N) {
		i--,j++;
	} 
	while(i >= 1 && j < N && bord[i][j] == -c) {
		i--,j++;
		cnt++;
	}
	i = x,j = y;
	if(i + 1 < N && j > 1) {
		i++,j--;
	}
	while(i < N && j >= 1 && bord[i][j] == -c) {
		i++,j--;
		cnt++;
	}
	ans = max(ans,cnt);
	int des = 0;
	if((x == 1 || x == N - 1 || y == 1 || y == N - 1 ) && ans < 4) des = 9999999;
	return max(defense_key[min(ans,5)] - des,0);
}


void bord_evaluate(int c) {//���������̽��й�ֵ����,��ǰ��������ΪC 
	for(int i = 1;i < N; ++i) {
		for(int j = 1;j < N; ++j) {
			if(bord[i][j] == 0) bord_key[i][j] = evaluate_attack(i,j,c) + evaluate_defense(i,j,c);
			else bord_key[i][j] = -1;
		}
	}
}

pair<int,int> DFS(int c) {
	pair<int,int> ans;
	ans.first = N/2,ans.second = N/2;
	int k = 0;
	bord_evaluate(c);
	for(int i = 1;i < N; ++i) {
		for(int j = 1;j < N; ++j) {
			if(bord_key[i][j] > k) {
				ans.first = i;
				ans.second = j;
				k = bord_key[i][j];
			}
		}
	}
	return ans;
}


void play() {
	int x,y;
	scanf("%d%d",&x,&y);
	x++,y++;
	bord[x][y] = -own;
}


int main()
{
	int seed;
	int op;
	int blk_x,blk_y;
	int whit_x,whit_y;
	//scanf("%d",seed);
	int col,row;
	//scanf("%d%d",&col,row);
	
	scanf("%d",&op);
	if(op == 1) {
		own = 1;
		while(true) {
			pair<int,int> loc = DFS(own);
			bord[loc.first][loc.second] = own;
			display();
			printf("��ǰ�������� X = %d ��Y = %d\n",loc.first-1,loc.second-1);
			//printf("%d %d\n",loc.first-1,loc.second-1);
			play();
			//fflush(stdout);
		}
		
//		scanf("%d%d",&blk_x,&blk_y);
	}
	else {
		own = -1;
		while(true) {
			play();
			pair<int,int> loc = DFS(own);
			bord[loc.first][loc.second] = own;
			display();
			printf("��ǰ�������� X = %d ��Y = %d\n",loc.first-1,loc.second-1);
			if(loc.first == 3 && loc.second == 6) {
				puts("YES");
			}
			//printf("%d %d\n",loc.first-1,loc.second-1);
			//fflush(stdout);
		}
	}
	
	
	
	return 0;
 } 
