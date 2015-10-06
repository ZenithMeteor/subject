#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct database 
{
	int h;
	int Knew;
	int Kold;
	short int EPC;
	short int SQN;	
};
char CRC(char *p, int len)
{
  char crc=0;
  while(len)
  {
    crc+=*p;
    crc%=137;
    crc<<=8;
    len--;
    p++;
  }
  crc>>=8;
  return crc;
}
void Hash()
{
	return;
}
short int Inc(short int input)
{
	++input;
	return input;
}
short int Dec(short int input)
{
	--input;
	return input;
}
int main()
{
	short int EPC_tag,SQN_tag;//tag資料 
	int h_tag,k_tag;//tag資料 
	FILE *rdatabase=fopen("database.txt","r");
	FILE *connect=fopen("connect.txt","r");
		
	int M3;// reader&server 產生的訊息 
	int M1,M2;//tag 產生的訊息
	int r1,r2;//亂數 
	
	database data[100];
	for(int i=0;i<100;i++)
	{
		scanf("%d%d%d%hd%hd",&data[i].h,&data[i].Knew,&data[i].Kold,&data[i].EPC,&data[i].SQN);
	}
	
	
	//建立資料庫
	int n;
	
	printf("資料數量：") ;
	scanf("%d",&n);
	database data[n];
	printf("輸入資料(h Knew Kold EPC SQN)\n");	
	for(int i=0;i<n;i++)
	{
		scanf("%d%d%d%hd%hd",&data[i].h,&data[i].Knew,&data[i].Kold,&data[i].EPC,&data[i].SQN);

	}	
	printf("輸入tag的資料(h k EPC SQN)");
	scanf("%d%d%hd%hd",&h_tag,&k_tag,&EPC_tag,&SQN_tag);
	
	
	srand(time(NULL));
	// reader
	{
		r1=rand();
		printf("r1:%d\n",r1);
	}
	//tag    收到 r1 
	{
		long long int temp,p1=EPC_tag,p2=r1;		
		r2=rand();
		
		p1=p1<<16;
		temp=p1+SQN_tag;
		temp=Hash(temp);
		M1=((!temp) | r2) & (temp | (!r2));
		
		p1=p1<<16;
		p2=p2<<16;
		temp=p1+p2+r2;
		temp=Hash(temp);
		M2=((!temp) | k_tag) & (temp | (!k_tag));
		printf("M1:%d M2:%d r2:%d\n",M1,M2,r2);
	} 
	
	//server   收到  h_tag M1 M2 
	{
		//4.1
		int i;
		for(i=0;data[i].h!=h_tag;i++);
		if(i==n)
		{
			printf("找不到tag\n");
		}
		else
		{
			// 4.2
			long long int temp,p1=data[i].EPC;
			int temp2;
			temp=p1<<16+data[i].SQN;
			temp2=Hash(temp);			
			int r2_server=((!M1) | temp2) & (M1 | (!temp2));
			
			//4.3
			temp=(p1<<32)+(r1<<16)+r2_server;		
			temp2=Hash(temp);
			temp2=((!temp2) | data[i].Knew ) & ( temp2 | (!data[i].Knew));
			
			if( M2== (( (!temp2) | (int)data[i].Knew ) & ( temp2 | (!(int)data[i].Knew) ) )  )
			{
				printf("server認證成功\ \n");
				//4.4
				data[i].SQN=Inc(data[i].SQN);
				//4.5
				temp=p1<<32+r2_server<<16+data[i].SQN;
				temp2=Hash(temp);
				M3=( (!temp2)| data[i].Knew) & (temp2 | (!data[i].Knew) );
				printf("M3:%d\n",M3);
				//4.6
				data[i].Kold=data[i].Knew;
				temp=data[i].Knew<<16+r2_server;
				data[i].Knew=Hash(temp);
				//4.7
				temp=p1<<16+data[i].SQN;
				data[i].h=Hash(temp);
												
			}
			else
			{
				printf("server認證失敗\n");	
			}
												
		}
		//tag  收到 M3
		{
			//6.1
			long long int temp,p1=EPC_tag;
			int temp2;
			SQN_tag=Inc(SQN_tag);
			//6.2
			temp=p1<<32+r2<<16+SQN_tag;
			temp2=Hash(temp);
			if(M3 ==(  ( (!temp2) | k_tag) & ( temp2 | (!k_tag ) ) )  )
			{
				printf("tag認證成功\\n");
				//6.3
				temp=k_tag<<16+r2;
				k_tag=Hash(temp);
				//6.4
				temp=p1<<16+SQN_tag;
				h_tag=Hash(temp);
			}
			else
			{
				printf("tag認證失敗\n");
				SQN_tag=Dec(SQN_tag);
			}
			
			
			
				
		} 
		
	}
	
	
	
	
	system("pause");
	return 0;
}
/*
3
1 13 13 10 56
5 26 26 48 93
3 56 56 13 65

5 26 48 93

*/
