#include<bits/stdc++.h>
#include<windows.h>
typedef long double ll; 
int m,n;
char pan[15][15];
ll visx[15][15];
ll viso[15][15];
int f[]={-1,-1,-1, 0};//���� \ | / �� 
int g[]={-1, 0, 1,-1};
int CMcheck[5],Difficult,PRvis;
int special;
struct point
{
    int x,y;
}p;
//������ 
void loading(int p);
int menu();
void funny();

//�������� 
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

//���㺯�� 
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
            loading(4);
            puts("����ʾ��������ʱ�����������������������ʼ�µ�һ��໡�\n\n�����ʽΪ�����ֿո����֡�\n\n�س���ȷ�� ~(������)~\n");
            getchar();
            Game();
        }
        else if(key==0)
        {
            puts("\n�ðɣ�ϣ���´��������д�  *���������*\n");
            break;
        }
        else puts("�밴��ʽ����ȷ�Ͻ�����Ϸ~   ~(������)~  ");
    }
    return 0;
}

int menu()
{
    int choice;special=0;
    do
    {
        printf("\n\n\n\n\n�����ߣ������������Թ�ע���ں�:\033[32m ����С���� \033[0m q(�R���Qq)\n\n");
        printf("===========================\n");
        printf("||                       ||\n");
        printf("||      1.��ʼ��Ϸ       ||\n");
        printf("||                       ||\n");
        printf("||      0.������Ϸ       ||\n");
        printf("||                       ||\n");
        printf("===========================\n");
        printf("����������ѡ��");
        
        scanf("%d",&choice);
        if(choice!=1&&choice!=0)funny();
    }while(choice!=1&&choice!=0);
    if(!choice)return 0;
    do
    {
        system("cls");
        loading(1);
        printf("=========================================\n");
        printf("||                                     ||\n");
        printf("||   1.�� ���� �ϡ� Ϊ��0��0��������   ||\n");
        printf("||        (�������꣬�ٺ����꣩        ||\n");
        printf("||                                     ||\n");
        printf("||   2.�� ���� �¡� Ϊ��0��0��������   ||\n");
        printf("||        (�Ⱥ����꣬�������꣩        ||\n");
        printf("||                                     ||\n");
        printf("=========================================\n");
        printf("����ѡ���ϰ�ߵ����̣�");
        scanf("%d",&PRvis);
        if(PRvis!=1&&PRvis!=2)funny();
    }while(PRvis!=1&&PRvis!=2);
    
    do
    {
        system("cls");
        loading(2);
        printf("��������ѡ�����̹��N ��5<=N<=15����");
        scanf("%d",&m);n=m;
        if(m>15||m<5)
        {
            puts("\n�����Ϲ��໣����������� ~(������)~ ");
            Sleep(2000);
            system("cls");
        }
    }while(m>15||m<5);
    
    do
    {
        system("cls");
        loading(3);
        printf("=================================\n");
        printf("||                             ||\n");
        printf("||       1.���Ĳ���������      ||\n");
        printf("||                             ||\n");
        printf("||       2.����·������      ||\n");
        printf("||                             ||\n");
        printf("||       3.Ψ����·������      ||\n");
        printf("||                             ||\n");
        printf("||       4.�˼ҽ��ҷ�ˮ��      ||\n");
        printf("||                             ||\n");
        printf("||       5.�����������޵�      ||\n");
        printf("||                             ||\n");
        printf("||       6.�Ҿ��������Կ�      ||\n");
        printf("||                             ||\n");
        printf("=================================\n");
        printf("��ѡ���Ѷȣ�");
        scanf("%d",&Difficult);
        getchar();
        if(Difficult<1||Difficult>6)funny();
    }while(Difficult<1||Difficult>6);
    return 1;
}

void funny()
{
    puts("");
    char s[99]={"������û���Ǹ�ѡ��� ��Ҫ�����������뷨  ��ֻ�Ǹ�û�и����ɱ��"};
    for(int i=0;s[i];++i)
    {
        printf("%c",s[i]);
        Sleep(50);
        if(i==21)Sleep(400);
        if(i==40)Sleep(400);
    }
    Sleep(600);
    puts("   �����أ��� ");
    Sleep(1000);
    puts("\n��������  (������) ");
    Sleep(2000);
    system("cls");
    return ;
}

void loading(int p)
{
    if(p!=4)
    {
        printf("\n============================\n");
        printf("||    ��Ϸ׼�����̣�%d/4   ||\n",p);
        printf("============================\n\n");
    }
    else
    {
        printf("\n============================\n");
        printf("||      ��Ϸ������ʼ��    ||\n");
        printf("============================\n\n");
    }
    printf("�����ߣ������������Թ�ע���ں�:\033[32m ����С���� \033[0m q(�R���Qq)\n\n");
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
    /*/
    //�������ǵ���ʹ�ã� 
    puts("CVis  Xͼ��");
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
            if(!k)printf("%2d��|",i);
            printf("%4.1lf |",visx[i][k]);
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
    
    
    puts("CVis  Oͼ��");
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
            if(!k)printf("%2d��|",i);
            printf("%4.1lf |",viso[i][k]);
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
    //*/
    system("cls");
    puts("\nĿǰ���̣�\n");
    int version=PRvis;
    if(version==1)
    {
        //������Ϊ00������ 
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
                if(!k)printf("%2d��|",i);
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
        //������Ϊ00������
        for(int i=0;i<m;++i)
        {
            printf("    ");
            for(int k=0;k<n;++k)
            printf(" ----"); 
            puts("");
            
            for(int k=0;k<n;++k)
            {
                if(!k)printf("%2d��|",m-i-1);
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

void PM()
{
    puts("�������忩~~~ ");
    while(~scanf("%d %d",&p.x,&p.y))
    {
        if(p.x<0)
        {
            special=1;
            break;
        }
        if(PRvis==2)swap(); 
        if(!pd(p.x)||!pd(p.y))
        {
            puts("���곬����Χ������������ ~(������)~");
            continue;
        }
        if(pan[p.x][p.y]!=' ')
        {
            printf("�����ѱ�ռ�ã����������� ~(������)~\n");
            continue;
        }
        pan[p.x][p.y]='x';
        visx[p.x][p.y]=-1;
        viso[p.x][p.y]=-1;
        CVis();
        break;
    }
}

void CM(int cn)
{
    puts("\n�� =���أ�= ��˼����~~\n");
    Sleep(300);
    get(cn);
    /*
    scanf("%d %d",&p.x,&p.y);//������� 
    if(PRvis==2)swap(); 
    //*/ 
    pan[p.x][p.y]='o';
    CVis();
    puts("�� =���أ�= �����뵽����");
    Sleep(500);
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
    else   //�������ȼ�
    { 
        ll maxx=0;
        ll maxo=-1;//ȡ-1��Ϊ�˷�ֹ����ȫΪ�����Ƶ㣨���ٺ�������������ȡ���� 
        int a,b,c,d; 
        
        if(cn==m*n-2) 
        {
            do
            {
                c=rand()%(m/3)+m/3;
                d=rand()%(n/3)+n/3;
            }while(pan[c][d]!=' ');//��һ����������
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
        if(maxo>=maxx)p.x=c,p.y=d;//��ʤ 
        else if(maxx>=2)//��ʤ 
        {
            p.x=a,p.y=b;
        }
        else p.x=c,p.y=d;//�������Ƶ㣨���Ż���
        visx[p.x][p.y]=-1;
        viso[p.x][p.y]=-1; 
    }
}
//                        jcs��    x/o   ��1/��0   jc������ 
int CK(int i,int k,int j,int jcn,char x,int cn,int jc) 
{
    //���� �������� 3��+1�� 
    char dx;
    dx=x=='x'?'o':'x';
    
    if(cn)// ��3  ��  3+1�� 
    {//     ��ǰ���������� �� ��Ե�����Լ�     ����    ������  ��     ��һ���ǿհ�       �����                              �����
        if((jcn==2&&pan[i+jc*f[j]][k+jc*g[j]]==x)||(jcn==3 && ( (dx!=pan[i-f[j]][k-g[j]]&&pd(i-f[j])&&pd(k-g[j])) || (dx!=pan[i+jc*f[j]][k+jc*g[j]]&&pd(i+jc*f[j])&&pd(k+jc*g[j])) )))return 1;
    }
    else
    {//         ͬ��   
        if((jcn==2&&pan[i-jc*f[j]][k-jc*g[j]]==x)||(jcn==3 && ( (dx!=pan[i+f[j]][k+g[j]]&&pd(i+f[j])&&pd(k+g[j])) || (dx!=pan[i-jc*f[j]][k-jc*g[j]]&&pd(i-jc*f[j])&&pd(k-jc*g[j])) )))return 1;
    }
    return 0;
}
//                         x/o     ģʽ/��/�� 
int ck(int i,int k,int j,char x,int cn) 
{
    //���� 1+1��2 ����� 
    char dx;
    dx=x=='x'?'o':'x';
    int ls,lx,ys=0,yx=0,firs=0,firx=0;
    //    ls,lx�ֱ��¼ ��ǰ���� �� ��������������� 
    //    fir���ֱַ��¼���� 
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
    if(!cn)//   1+1��Ч�ߵ���� 
    { //   1+1������3  ���� �ڵ㲻Ϊ�գ�lx/ls���� ��ֹͣ�㣩 ���벻Ϊ�ڵ㣩  ���� ���ȱ�����  ����  ����������� (û���Լ���   
        if(firs+firx>3||firs+1==ls||firx+1==lx||ls+lx<7||ls<3||lx<3||ys!=1||yx!=1)return 0;
        return 1;
    }
    else//   2����Ч����� 
    {//    ��������           ����Ҫ��                                        ����Ϊ�� 
        if(ls+lx>6&&((cn==1&&ys>=2)||(cn==2&&yx>=2))&&pan[i+(ls-1)*f[j]][k+(ls-1)*g[j]]==' '&&pan[i-(lx-1)*f[j]][k-(lx-1)*g[j]]==' ')return 1;
        return 0;
    }
}
void jp(int i,int k,int j,int s[],ll &Q,ll &E,int &C,int p,char X) 
{
    //�������ж�   
    char x,dx;
    if(p)x='x',dx='o';
    else x='o',dx='x';
    int js=0;
    for(s[0]= f[j],s[1]= g[j];pd(i+s[0])&&pd(k+s[1])&&x==pan[i+s[0]][k+s[1]];s[0]+=f[j],s[1]+=g[j],Q++);
    for(s[2]=-f[j],s[3]=-g[j];pd(i+s[2])&&pd(k+s[3])&&x==pan[i+s[2]][k+s[3]];s[2]-=f[j],s[3]-=g[j],E++);
    //   3+1 ����2+2 ���Ƶ� 
    if((Q==3&&E==1)||(E==3&&Q==1)||(Q>=2&&E>=2))Q=8,js=1;
    else
    {
        // ��ѧ���� 
        if(Q>2)Q+=Q-2;
        if(E>2)E+=E-2;
        if(Q>0&&E>0&&pd(i+s[0])&&pd(i+s[2])&&pd(k+s[3])&&pd(k+s[1])&&' '==pan[i+s[2]][k+s[3]]&&' '==pan[i+s[0]][k+s[1]])Q++;//���Ż� 
        Q+=E;
    }
    //   ������ǿ�� 
    if(Q>=6)Q=8;//����> :bug x_xxxx| �յ�Ϊ7.0 
    // 2+1��ǿ�� 
    if(Q==4&&(E==1||E==2)&&pd(i+s[0])&&pd(i+s[2])&&pd(k+s[3])&&pd(k+s[1])&&' '==pan[i+s[2]][k+s[3]]&&' '==pan[i+s[0]][k+s[1]])Q=7.1,js=1;
    if(js)
    {
        C=0;
        if(X!=' ')return ;
        if(p)visx[i][k]=Q;
        else viso[i][k]=Q;
    }
    //������3����QE������� 
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
    //��·�Ż� 
    char dx;
    dx=x=='x'?'o':'x';
    
    int Q,E,y;//�ֿ��Ը��򳤶ȿ��� + //�ж���������
    if(C)
    {
        for(Q=1;dx!=pan[i+Q*f[j]][k+Q*g[j]]&&pd(i+Q*f[j])&&pd(k+Q*g[j])&&Q<5;Q++)if(pan[i+Q*f[j]][k+Q*g[j]]==x)y=1; 
        for(E=1;dx!=pan[i-E*f[j]][k-E*g[j]]&&pd(i-E*f[j])&&pd(k-E*g[j])&&E<5;E++)if(pan[i-E*f[j]][k-E*g[j]]==x)y=1;
        //��������     �ҵ�ǰ�����ȼ�����   �ڴ˷��򲻶Ըõ㸳ֵ 
        if(Q+E<6&&y&&((x=='x'&&visx[i][k]<6)||(x=='o'&&viso[i][k]<6)))c=0;
    }
}
 
ll BC(int i,int k,char X)
{
    if(Difficult==1)return 0;
    //��¼��ǰ���ֵ�����ظ�BFS 
    ll value=0;
    //��¼��ǰ����Χ��Ч������ 
    int disx=0,diso=0;
    //���д˵����ǽ���㣬����治�ٶԸõ㸳ֵ 
    int Cx=1,Co=1;
    //��¼��Ч������ 
    int tex=0,teo=0,twx=0,two=0;
    //�����ĸ����� 
    for(int j=0;j<4;++j)
    {
        if(Difficult>2)
        {
            //������ж� 
            int jc,jcx,jco;
            //������¼���� 
            int jx=0,jo=0;
            //��¼��ǰֱ����Ч������ 
            for(jc=1,jcx=0,jco=0;pd(i+jc*f[j])&&pd(k+jc*g[j])&&jc<4;jc++)
            {
                //��ѧ���� 
                if('o'==pan[i+jc*f[j]][k+jc*g[j]])jco++,jcx-=2;
                if('x'==pan[i+jc*f[j]][k+jc*g[j]])jcx++,jco-=2;
            }
            //��ͬ������� 
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
            //1+1��Ч�� һ��ֱ��ֻ�ж�һ�� 
            if(ck(i,k,j,'x',0))disx++,jx++,twx=1;
            if(ck(i,k,j,'o',0))diso++,jo++,two=1;
            //��ѧ���� 
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
                Cx=0;Co=0;//�ǽ���㣬ȡ�������ı�
                //��ѧ���� 
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
        //QEΪ��ǰ����ȡֵ��ͬjp���� 
        ll Qx=0,Ex=0,Qo=0,Eo=0;
        // ����淽������  cx/co  ͬCxCo ������·�ж�ȡ�������ı� 
        int x[4],o[4],cx=1,co=1;
        jp(i,k,j,x,Qx,Ex,Cx,1,X);
        jp(i,k,j,o,Qo,Eo,Co,0,X);
        if(Qx>=7&&X=='x')return Qx;
        if(Qo>=7&&X=='o')return Qo;//�о�ɱֱ�ӷ��� 
        //��·�ж� 
        sl(i,k,j,Cx,cx,'x');
        sl(i,k,j,Co,co,'o');
        if(!cx&&!co)continue;//�Ż����� 
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
void BFS(int x,int y,char X,int key,ll up)//��ֵ�հ׵� -> ı�Լ������ȼ� 
{
    //����Ԥ�㷨������Ӧ���к��������ģ���û�뵽һ�α����ͺ�ǿ�ˣ���ûд���� 
    pan[x][y]=X;
    ll value;int tp,sk=0;
    //tp �������췽���жϳ���  
    char dx;
    dx=x=='x'?'o':'x'; 
    for(int j=0;j<4;++j)//����ֱ�߷���  ÿ������3*2����   
    {
        for(int jc= 1,tp=0;pd(x+jc*f[j])&&pd(y+jc*g[j])&&pan[x+jc*f[j]][y+jc*g[j]]!=dx&&jc<4+tp;++jc)
        {
            //����õ��ǵжԵ㣬���� 
            if(pan[x+jc*f[j]][y+jc*g[j]]==X)tp++;
            //�����ڻ���Ϊ������ 
            if(!pd(x+jc*f[j])||!pd(y+jc*g[j])||pan[x+jc*f[j]][y+jc*g[j]]!=' ')continue;
            // ��ѧ����   �õ�ֵ������� ���������Ӱ�� 
            if(X=='x'&&visx[x+jc*f[j]][y+jc*g[j]]>=5)continue;
            if(X=='o'&&viso[x+jc*f[j]][y+jc*g[j]]>=5)continue;
            
            value=BC(x+jc*f[j],y+jc*g[j],X);
            up+=value;// up���ڴ�Ӱ��ֵ 
            
            if(value>=5)sk++;if(value>=7)sk++,key++;//��ѧ���� 
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
        //��Ϊ��ѧ��������ֵ����û�н��ͣ������ǳ��ڶ�β��Ի�ȡ��  ����ѡ�� 
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
        //�����Ѷ�  ���Դ������� 
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
        printf("�ף���(�á㧥��)��\t");
        Sleep(1000);
        char S[200]={"�ðɣ���Ȼ�ܲ������...    ��������!\n"};
        for(int i=0;S[i];++i)
        {
            printf("%c",S[i]);
            if(i==5||i==25)Sleep(500);
            Sleep(50);
        }
        Sleep(1500);
        if(Difficult!=6)
        {
            char s[200]={"\n���ǣ�����  ���и��ѵ��  (��������)��   \n\n���� , ͨ�غ����֪�������ߵ�С������ ~(������)~  ף����Ϸ���\n\n"};
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
                puts("\n�Ƿ�Ը���������ߵĳ����£�\n\n1Ը��\t0��Ը��"); 
                scanf("%d",&C);
            }while(C!=1&&C!=0);
            if(!C)return ;
            char s[]={"\n��ϲͨ����, ˵�����Ѿ����������������������.   \n\n"
            "��ʵ��.\n\nΪ�˽��ͽ����Ѷ�, �Ѷ�6������һ��©��, ����Ϊ������, ���Ѷ�5�Ͷ���ס��.\n\n"
            "��������������ڲ�д�����������AI, �������к�����, �����Ѿ�������, ��û�ټ���д��.\n\n"
            "�� , , ��������, лл�������ҵ���Ϸ, ϣ�����ܹ�ע�ҵĹ��ںţ��и���໣��������. \n\n"};
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
        printf("����!���ã�\n\n");
        Sleep(1000);
        printf("Ҫ��~~~\n\n");
        Sleep(2000);
        printf("����һ�����ԣ� (������) \n");
        Sleep(1000);
    }
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
        cm=t%2;//���ó������ 
        p.x=m/2;p.y=n/2;
        pan[p.x][p.y]='o';
        visx[p.x][p.y]=-1;
        viso[p.x][p.y]=-1;
        CVis();
        PR();
        if(PRvis==1)printf("�������ӣ���%d %d��\n",p.x,p.y);
        else printf("�������ӣ���%d %d��\n",p.y,m-p.x-1);
    }
    while(t--)
    {
        if(t%2==cm)CM(t);
        else PM();
        
        PR();
        
        if(t%2==cm)
        {
            if(PRvis==1)printf("�������ӣ���%d %d��\n",p.x,p.y);
            else printf("�������ӣ���%d %d��\n",p.y,m-p.x-1);
        }
        Sleep(1000);
        
        if(special)
        {
            system("cls");
            return ;
        }
        if(check(p.x,p.y))return ;
    }
    puts("\n������ ~(������)~ ");
    return ; 
}
