#include<bits/stdc++.h>
using namespace std;
#define mt(x) memset(x,0,sizeof x)
#define m 15
#define n 15
typedef long double ll;
char pan[15][15];
ll visx[15][15];
ll viso[15][15];
int f[]={ 0,-1,-1,-1};//���� �� | \ /  
int g[]={-1, 0,-1, 1};
int num=0,hnum=0,xnum=0,tim,cnt;
int choice;
struct point
{
    int x,y;
}p,pg[100];
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
	//CK���� 
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
	//ck���� 
	if(cn==0)
	{
		if(firs+firx>3||firs+1==ls||firx+1==lx||ls+lx<7||ls<3||lx<3||ys!=1||yx!=1)return ;
		else 
		{
			dis++;js++;tw=1;
			return ;
		}
		//cnΪ0ʱ��ֻ��ck��,����ֱ��return 
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
	//�������ж�   
	char x,dx;
	if(p)x='x',dx='o';
	else x='o',dx='x';
	int js=0;
	for(s[0]= f[j],s[1]= g[j];tpchar(i+s[0],k+s[1],x);s[0]+=f[j],s[1]+=g[j],Q++);
    for(s[2]=-f[j],s[3]=-g[j];tpchar(i+s[2],k+s[3],x);s[2]-=f[j],s[3]-=g[j],E++);
    //   3+1 ����2+2 ���Ƶ� 
    //�����ģ� 
	if((Q==3&&E==1)||(E==3&&Q==1)||(Q>=2&&E>=2))Q=8,js=1;//�˴��Ż� 
    else
    {
    	if(Q>2)Q+=Q-2;
	    if(E>2)E+=E-2;
	    if(Q>0&&E>0&&tpchar(i+s[0],k+s[1],' ')&&tpchar(i+s[2],k+s[3],' '))Q++;//���Ż� 
	    Q+=E;
    }
	if(Q>=6)Q=8;
	// �����ģ�2+1��ǿ�� 
    if(Q==4&&(E==1||E==2)&&tpchar(i+s[0],k+s[1],' ')&&tpchar(i+s[2],k+s[3],' '))
	{
		Q=7.1,js=1;//�հ�2+1�հ� 
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
	//������3������������QE������� 
    if(Q==4&&E==0)
	{
		if(!pd(i+s[0])||!pd(k+s[1])||pan[i+s[0]][k+s[1]]!=' ')Q-=2;
		else if(!pd(i-f[j])||!pd(k-g[j])||pan[i-f[j]][k-g[j]]==dx)Q--; 
		else 
		{
			Q=6.9;
			if(X==' ')Q=7.2;
		}
	}
    if(E==4&&Q==4)
	{
		if(!pd(i+s[2])||!pd(k+s[3])||pan[i+s[2]][k+s[3]]!=' ')Q-=2;
		else if(!pd(i+f[j])||!pd(k+g[j])||pan[i+f[j]][k+g[j]]==dx)Q--;
		else 
		{
			Q=6.9;
			if(X==' ')Q=7.2;
		} 
	} 
}
void sl(int i,int k,int j,int C,int &c,char x)
{
	//��·�Ż� 
	char dx;
	if(x=='x')dx='o';
	else dx='x';
	
	int Q,E,y;//�ֿ��Ը��򳤶ȿ��� + //�ж���������
	if(C)
	{
		for(Q=1;dx!=pan[i+Q*f[j]][k+Q*g[j]]&&pd(i+Q*f[j])&&pd(k+Q*g[j])&&Q<5;Q++)
			if(pan[i+Q*f[j]][k+Q*g[j]]==x)y=1; 
        for(E=1;dx!=pan[i-E*f[j]][k-E*g[j]]&&pd(i-E*f[j])&&pd(k-E*g[j])&&E<5;E++)
			if(pan[i-E*f[j]][k-E*g[j]]==x)y=1;
        //��������     �ҵ�ǰ�����ȼ�����   �ڴ˷��򲻶Ըõ㸳ֵ 
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
	//i��kĬ��Ϊ�� 
	ll value=0;//��¼��ǰ���ֵ�����ظ�BFS 
	int disx=0,diso=0;//��¼��ǰ����Χ��Ч������ 
	int Cx=1,Co=1;//���д˵����ǽ���㣬����治�ٶԸõ㸳ֵ 
	int tex=0,teo=0,twx=0,two=0;//��¼��Ч������
	int threex=0,fourx=0;//x����,��/��������
	int threeo=0,fouro=0;//o����,��/��������
    for(int j=0;j<4;++j)//�����ĸ����� 
    {
    	//����ж� 
		int dx=0,bx=0,ddx=0,bbx=0;
		int qo=0,bo=0,ddo=0,bbo=0;
		find(i,k,j,ddx,dx,bx,bbx,'x');
		if(f3(i,k,j,ddx,dx,bx,bbx))threex++;
		//����
		if(f4(i,k,j,ddx,dx,bx,bbx))fourx++;
		else fourx+=f5(i,k,j,ddx,dx,bx,bbx);
		
		find(i,k,j,ddo,qo,bo,bbo,'o');
		if(f3(i,k,j,ddo,qo,bo,bbo))threeo++;
		//����
		if(f4(i,k,j,ddo,qo,bo,bbo))fouro++;
		else fouro+=f5(i,k,j,ddo,qo,bo,bbo);
		if((fourx+threex)>=2||(fouro+threeo)>=2)
        {
            if(((fourx+threex)>=2&&dog=='o')||((fouro+threeo)>=2&&dog=='x'))value=5;//3
			if((threex&&fourx)||(threeo&&fouro))value=7; 
			if(X==' ')
            {
            	if(fourx+threex>=2&&dog=='o')
            	{
            		if(fourx)visx[i][k]=7.1,viso[i][k]=7.1;
            		else visx[i][k]=7.0,viso[i][k]=7.0;
            	}
            	else if(fouro+threeo>=2&&dog=='x')
            	{
            		if(fouro)visx[i][k]=7.1,viso[i][k]=7.1;
            		else visx[i][k]=7.0,viso[i][k]=7.0;
            	}
                if((threex&&fourx)||(threeo&&fouro))
                {
                	if((bbx==3||bbo==3)&&tpchar(i+5*f[j],k+5*g[j],' '))
                	{
                		pg[cnt  ].x=i+f[j];
                		pg[cnt++].y=k+g[j];
                	}
                	else if((ddx==3||ddo==3)&&tpchar(i-5*f[j],k-5*g[j],' '))
                	{
                		pg[cnt  ].x=i-f[j];
                		pg[cnt++].y=k-g[j];
                	}
                	else
					{
						if(threex&&fourx)visx[i][k]=7.3;
						else viso[i][k]=7.3;
					}
                }
            }
            if(value==7)Cx=0,Co=0;//�ǽ���㣬ȡ�������ı�
            //��ѧ���� 
        }
		//QEΪ��ǰ����ȡֵ��ͬjp���� 
    	ll Qx=0,Ex=0;
    	ll Qo=0,Eo=0;
    	int x[4],o[4];// ����淽������  cx/co  ͬCxCo ������·�ж�ȡ�������ı� 
        jp(i,k,j,x,Qx,Ex,Cx,1,X);
        jp(i,k,j,o,Qo,Eo,Co,0,X);
        if(Qx>=7&&X=='x')return Qx;
		if(Qo>=7&&X=='o')return Qo;//�о�ɱֱ�ӷ��� 
        //*/
		int cx=1,co=1;
		sl(i,k,j,Cx,cx,'x');//��·�ж� 
		sl(i,k,j,Co,co,'o');//��·�ж� 
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
	pan[x][y]=X;
	ll value;
	int sk=0;
	char dx;
	if(X=='x')dx='o';
	else dx='x';
	for(int j=0;j<4;++j)//����ֱ�߷���  ÿ������3*2����   
	{
		int tp;//tp �������췽���жϳ���  
		for(int jc= 1,tp=0;pd(x+jc*f[j])&&pd(y+jc*g[j])&&pan[x+jc*f[j]][y+jc*g[j]]!=dx&&jc<4+tp;++jc)
		{
			//����õ��ǵжԵ㣬���� 
			if(pan[x+jc*f[j]][y+jc*g[j]]==X)tp++;
			//�����ڻ���Ϊ������
			if(!pd(x+jc*f[j])||!pd(y+jc*g[j])||pan[x+jc*f[j]][y+jc*g[j]]!=' ')continue;
			 
			if(X=='x'&&visx[x+jc*f[j]][y+jc*g[j]]>=5)continue;
			if(X=='o'&&viso[x+jc*f[j]][y+jc*g[j]]>=5)continue;
			//*/
			value=BC(x+jc*f[j],y+jc*g[j],X);//��ɼ�ֵ������ 
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
		if(X=='x')visx[x][y]=6;//6.27  (1,1)�ܸ��Ż� 
		if(X=='o')viso[x][y]=6;//���Կ���ֵ��789 
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
	cnt=0;
	//*
	for(int i=0;i<15;++i)
    for(int k=0;k<15;++k)
    {
        if(pan[i][k]==' ')
        {
        	visx[i][k]=0;
			viso[i][k]=0;
        	BC(i,k,' ');//�ӿ������ӵĵ���� 
        }
    }
    //*/
    //*
    for(int i=0;i<15;++i)
    for(int k=0;k<15;++k)
    {
        if(pan[i][k]==' ')
        {
        	if(visx[i][k]<5&&visx[i][k]>=0)BFS(i,k,'x',0,0);
        	if(viso[i][k]<5&&viso[i][k]>=0)BFS(i,k,'o',0,0);
        }
    }
	//*/
	for(int i=0;i<cnt;++i)
	{
		visx[pg[i].x][pg[i].y]=7.5;
		viso[pg[i].x][pg[i].y]=7.5;
	} 
    return ;
}

void PR()
{
	//return ;
	if(choice)
	{
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
bool tpchar(int x,int y,char X)//�⵱ǰxy�Ƿ�ΪX 
{
	if(pd(x)&&pd(y)&&pan[x][y]==X)
		return true;
	return false;
}
bool tpcheck(int x,int y)//���Ƿ񷸽��� 
{
	int three=0,four=0;//����,��/�������� 
	bool pdd=false;
	bool pddmid=false;
	for(int i=0;i<4;++i)//�ĸ�ֱ�ߵķ��� 
	{
		int d=0,b=0,dd=0,bb=0;
		find(x,y,i,dd,d,b,bb,pan[x][y]);
		if(f3(x,y,i,dd,d,b,bb))three++;
		//����
		if(f4(x,y,i,dd,d,b,bb))four++;
		else four+=f5(x,y,i,dd,d,b,bb);
		//���� 
		if(d+b>4)pdd=true;
	}
	if(pdd)return true;
	if(three&&four)
	{
		//�����ģ������Ĳ����� 
		return false; 
	}
	else if(three>1)return true;
	else if(four>1)return true;
	return false;
}
int check(int x,int y)
{
	//��������
	//���������ģ�����
	//puts("������������������������������������������");
	tim--; 
	if(pan[x][y]==dog&&tpcheck(x,y))
	{
		if(dog=='x')puts("x�����֣�o��ʤ������");
		else puts("o�����֣�x��ʤ������");
		return true;
	}
	for(int j=0;j<4;++j)
	{
		int i,p=4;
		for(i= 1; tpchar(x+i*f[j],y+i*g[j],pan[x][y]) && p ; ++i,--p);
    	for(i=-1; tpchar(x+i*f[j],y+i*g[j],pan[x][y]) && p ; --i,--p);
    	if(!p)
    	{
    		printf("\n%c5����ʤ   ������\n\n",pan[x][y]);//win(pan[x][y]);
    		if(pan[x][y]=='o')num++;
    		else xnum++;
        	return 1;
    	}
	}
	if(!tim)
	{
		puts("\n����������");
		hnum++;
		return 1;
	}
	return 0;
}
int main()
{
	num=0;
	srand((unsigned) time(NULL));
    alphago.init();
    Init();
    tim=m*n-1;
	choice=0;
	p.x=7;
	p.y=5;
	printf("��%d %d ��\n",p.x,p.y);
	if(dog==' ')dog='x';
	pan[p.x][p.y]='x';
	visx[p.x][p.y]=-1;
	viso[p.x][p.y]=-1;
	CVis();alphago.down(p.x,p.y);
	PR();printf("x:( %d %d )\n",p.x,p.y);
	//*/
	int t=m*n-tim;
    while(1)
    {
		if(t==1)
		{
			if(pan[7][7]==' ')p.x=7,p.y=7;
			else p.x=6,p.y=6;
			t=0;
		} 
		else get();
	    pan[p.x][p.y]='o';
	    visx[p.x][p.y]=-1;
		viso[p.x][p.y]=-1;
		
		CVis();alphago.down(p.x,p.y);
		PR();printf("o:( %d %d )\n",p.x,p.y);
		if(check(p.x,p.y))break;
		
        pair<int,int>q;
        q=alphago.location();
        //scanf("%d %d",&q.first,&q.second); 
        if(dog==' ')dog='x';
        pan[q.first][q.second]='x';
        p.x=q.first;p.y=q.second;
		visx[p.x][p.y]=-1;
		viso[p.x][p.y]=-1;
		
		CVis();alphago.down(p.x,p.y);
		PR();printf("x:( %d %d )\n",p.x,p.y);
		if(check(p.x,p.y))break;
	}
	printf("���Ʋ���%d��\n",225-tim); 
    return 0;
    //*/
}
/*
	���ý��֣�
		���������Ӻ�checkһ�ε����� ���ֵ� ��
			����г���֮����γɣ���ô���������
			Ҳ������������ĳ�������ֵ���ɱ����
				bfs��ʱ�򣬼����ģ�������  ���ļ�ֵ�㣬�Ҹõ������ֵĽ��ֵ㣬��ôval upup 
*/
/*
���⣺
	���ĵ�ͬ���� 
*/
