 #include<iostream>
#include<fstream>
#include <windows.h>
using namespace std;

unsigned int cal_crc(unsigned char *ptr, unsigned char len) 
{
    unsigned int crc;
    unsigned char da;
    unsigned int crc_ta[256]={ /* CRC �E���� */
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
    0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
    0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
    0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
    0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
    0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
    0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
    0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
    0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
    0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
    0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
    0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
    0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
    0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
    0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
    0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
    0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
    0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
    0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
    0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
    0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
    0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};
    crc=0;
    while(len--!=0) 
    {
        da=(unsigned char) (crc/256); /*�H8��G�i��ƪ��Φ��ȦsCRC����8��*/
        crc<<=8; /*����8��A�۷��CRC���C8�쭼�H2^8*/
        crc^=crc_ta[da^*ptr]; /*��8��M��e�r�`�ۥ[��A�d��DCRC�A�[�W�H�e��CRC*/
        ptr++;
    }
    return(crc);
}
//10�i����2�i�� 
char* itobs(int n, char *ps) 
{
    int size = 12;
    int i = size -1;
      
    while(i+1) 
    {
       ps[i--] = (1 & n) + '0';
       n>>= 1;
    }
      
    ps[size] = '\0';
    return ps;
}

class node
{
public:
    node()
    {
        for(int a=0;a<12;a++)
        {
            n_EPC[a]=0;
        }
        k_old=0;
        k_new=0;
        next=NULL;
    };
    
    unsigned char n_EPC[13];
    unsigned int k_old;
    unsigned int k_new;
    node *next;
};

int main()
{
    fstream fp,fp1,fp2;
    /*
    //����DataBase
    fp.open("Database.txt", ios::out);//�}���ɮ�
    if(!fp){//�p�G�}���ɮץ��ѡAfp��0�F���\�Afp���D0
        cout<<"Fail to open file: DB file"<<endl;
        system("PAUSE");
        return 0;
    }
    char s[sizeof(int) + 1];
    for(int a=0;a<4096;a++)
    {
        fp<<itobs(a,s)<<" "<<4<<" "<<1<<endl;;
    }
    fp.close();
    //��������DataBase
    */
    
    
    //Ū����Ʈw�ئ�link list 
    fp.open("Database.txt", ios::in);//�}���ɮ�
    if(!fp){//�p�G�}���ɮץ��ѡAfp��0�F���\�Afp���D0
        cout<<"Fail to open file: DB file"<<endl;
        system("PAUSE");
        return 0;
    }
    node *root,*db,*now,*del;
    root=new node();
    db=new node();
    root->next=db;
    while(fp>>db->n_EPC)
    {
        fp>>db->k_old;
        fp>>db->k_new;
        db->next=NULL;
        del=db;
        //cout<<db->n_EPC<<" "<<db->k_old<<" "<<db->k_new<<" "<<db->next<<endl;
        db=new node();
        now=root;
        while(now->next!=NULL)
        {
            now=now->next;
        }
        now->next=db;
    }
    //�R���Ÿ`�I 
    now=root;
    while(now->next!=NULL)
    {
        now=now->next;
    }
    free(now);
    del->next=NULL;
    fp.close();
    Sleep(10);
    //����link list
    /* 
    //���� link list
     now=root;
     do
     {
         now=now->next;
         cout<<now->n_EPC<<" "<<now->k_old<<" "<<now->k_new<<endl; 
     }while(now->next!=NULL);
     */ 
     
    
    fp1.open("Tag_file.txt", ios::in);//�}���ɮ�
    if(!fp1){//�p�G�}���ɮץ��ѡAfp��0�F���\�Afp���D0
        cout<<"Fail to open file: Tag file"<<endl;
        system("PAUSE");
        return 0;
    }
    
    fp2.open("B_Time.txt", ios::out);//�}���ɮ�
    if(!fp2){//�p�G�}���ɮץ��ѡAfp��0�F���\�Afp���D0
        cout<<"Fail to open file: Tag file"<<endl;
        system("PAUSE");
        return 0;
    }
    
    unsigned char t_n_EPC[13];
    unsigned int t_N1,t_N2,t_M1,t_M2;
    unsigned int M2_1=0,M2_2=0;
    LARGE_INTEGER t1, t2, ts;
    
    QueryPerformanceFrequency(&ts);
    
    while(fp1>>t_n_EPC>>t_N1>>t_N2>>t_M1>>t_M2)
    {
        now=root;
        QueryPerformanceCounter(&t1);
        do
        {
            now=now->next;
            
            int c_size=0,c_rsize=0; //concatenation size
            c_size=sizeof(now->n_EPC)+(sizeof(now->k_new)/4)+(sizeof(t_N1)/4)+(sizeof(t_N2)/4)-1;//kold new size�@�� 
            unsigned char c_crc_arr[c_size];//knew 
            unsigned char c_1_crc_arr[c_size];//kold
            for(int b=0;b<c_size;b++)
            {
                c_crc_arr[b]=0;
                c_1_crc_arr[b]=0;
            }
            //cout<<now->n_EPC<<" "<<now->k_old<<" "<<t_N1<<" "<<t_N2<<endl;
            // concatenation
            for(int c=0;c<(sizeof(now->k_new)/4);c++)
            {
                c_crc_arr[c_rsize]=(unsigned char)now->k_new;
                c_1_crc_arr[c_rsize]=(unsigned char)now->k_old;
                c_rsize++;
            }
            for(int b=0;b<(sizeof(now->n_EPC)-1);b++)
            {
                if(now->n_EPC[b]=='0')
                {
                    c_crc_arr[c_rsize]=(unsigned char)0;
                    c_1_crc_arr[c_rsize]=(unsigned char)0;
                }
                else
                {
                    c_crc_arr[c_rsize]=(unsigned char)1;
                    c_1_crc_arr[c_rsize]=(unsigned char)1;
                }
                c_rsize++;
            } 
            for(int b=0;b<(sizeof(t_N1)/4);b++)
            {
                c_crc_arr[c_rsize]=t_N1;
                c_1_crc_arr[c_rsize]=t_N1;
                c_rsize++;
            }
            for(int b=0;b<(sizeof(t_N2)/4);b++)
            {
                c_crc_arr[c_rsize]=t_N2;
                c_1_crc_arr[c_rsize]=t_N2;
                c_rsize++;
            }
            /*
            //��X���� 
            for(int b=0;b<c_size;b++)
            {
                cout<<(unsigned int)c_crc_arr[b];
            }
            cout<<endl;
            */
            
            M2_1=(cal_crc(c_crc_arr,sizeof(c_crc_arr)) ^ now->k_new);
            M2_2=(cal_crc(c_1_crc_arr,sizeof(c_1_crc_arr)) ^ now->k_old);
            //cout<<M2_1<<" "<<M2_2<<endl;
            
            if(t_M2==M2_1 || t_M2==M2_2)
            {
                //cout<<"YES"<<endl;
                QueryPerformanceCounter(&t2);
                fp2<<(t2.QuadPart-t1.QuadPart)*1000/(double)(ts.QuadPart)<<endl;
                //cout<<"Time: "<<(t2.QuadPart-t1.QuadPart)*1000/(double)(ts.QuadPart)<<"(ms)"<<endl;
                break; 
            }
        }while(now->next!=NULL);
    }
    
    fp2.close();
    fp1.close();
    //����node�O����
    //�i�o�gXD 
    
    system("PAUSE");
    return 0;
}
