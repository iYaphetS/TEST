#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <net/if.h>  
#include <sys/ioctl.h>
#include <arpa/inet.h> 

/*<arpa/inet.h>头文件不加 
get_host_info会得不到主机的ip地址信息
getlocalhostip 调用inet_ntoa得到的是非法地址*/

int AddIp(char* VipStart,int VipNum, char* DestVip)
{
	int IpLastPart;
	char ThreePartOfIp[64];
	memset(ThreePartOfIp,0,sizeof(ThreePartOfIp));
	GetPartFromIp(VipStart,ThreePartOfIp,&IpLastPart);
	IpLastPart += VipNum;
	sprintf(DestVip,"%s%d",ThreePartOfIp,IpLastPart);
	return 0;
}

int GetPartFromIp(char* IpAddress,char* ThreePartOfIp,int* LastPartOfIp)
{
	char* TmpStr1 = NULL;
	char* TmpStr2 = NULL;
	TmpStr2 = IpAddress;
    int i = 0;
	for(i; i<3; i++)
	{
		TmpStr1 = strstr(TmpStr2,".");
		if(NULL == TmpStr1)
		{
			return -1;
		}
		else
		{
			TmpStr2 = TmpStr1+1;
		}
	}
	*LastPartOfIp=atoi(TmpStr2);
	memcpy(ThreePartOfIp, IpAddress, TmpStr2-IpAddress);
	return 0;
}


/*获取主机的ip地址（点分十进制）*/
int get_host_info (char* szIPAddress)
{
	int iRtnCode;
    struct hostent *hptr;
	struct in_addr in;
	char cHostName[64];

	iRtnCode = gethostname(cHostName, sizeof(cHostName));

    printf("host = %s\n", cHostName);

	if (iRtnCode != 0)
	{
		strcpy(szIPAddress,"");
        return -1;
	}

	hptr = gethostbyname(cHostName);

	if (NULL == hptr) 
	{
		strcpy(szIPAddress,"");
        return -1;
	}

	memcpy(&in, (u_long *)hptr->h_addr_list[1], sizeof(in));
    //LPSTR lpAddr = hptr->h_addr_list[0];
    //memmove(&in, (u_long *)hptr->h_addr_list[0], sizeof(in));
    //szIPAddress = inet_ntoa(in);
    //printf("--------type = %d, name = %s, aliases = %s, ip = %s, ip = %s--------------\n", hptr->h_addrtype, hptr->h_name, hptr->h_aliases[0], hptr->h_addr_list[0], hptr->h_addr_list[1]);

	strcpy(szIPAddress, inet_ntoa(in));

    printf("------------------------------------------\n");
    	
	return 0;
} /* end of get_host_info() */

char * getlocalhostip()
{
    int MAXINTERFACES = 16;
    char *ip = NULL;
    int fd, intrface, retn = 0;
    struct ifreq buf[MAXINTERFACES];

    struct ifconf ifc;
    printf("--------1--------\n");
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
    {
        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t)buf;

        printf("--------2--------\n");
        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))
        {
            intrface = ifc.ifc_len / sizeof(struct ifreq);

            printf("--------3--------\n");
            while(intrface--)
            {
                if (!(ioctl(fd, SIOCGIFADDR, (char *)&buf[intrface])))
                {
                    printf("--------4--------\n");
                    ip = (inet_ntoa(((struct sockaddr_in *)(&buf[intrface].ifr_addr))->sin_addr));
                    break;
                }
            }
        }

        printf("--------5--------\n");
        close(fd);

    }
    printf("--------6--------\n");

    return ip;
}

typedef unsigned long  u_long;
typedef unsigned char  u_char;
typedef unsigned short u_short;

typedef struct hdr_flag {
  u_char r:1;			//������
  u_char p:1;  			//�����������
  u_char e:1;  			//������
  u_char t:1;  			//�ط����
  u_char rsvd:4; 		//����
}FLAGS;

typedef struct DiameterHeader
{
	u_char version;			//�汾
	u_long length;			//��Ϣ����
	FLAGS flags;			//������
	u_long  CmdCode;		//������
	u_long  ApplicationId;	//Ӧ��ID
	u_long  HopByHopId;		//����ID
	u_long  EndToEndId;		//�˵���ID
}DIAMETER_HEAD;


int main()
{

    char dst[100];
    memset(dst, sizeof(dst), 0);

    AddIp("192.168.1.1", 1, dst);

    printf("dst = %s\n", dst);

    char ip[100];
    memset(ip, sizeof(ip), 0);

    get_host_info(ip);
    printf("ip = %s\n", ip);

    printf("--------7--------\n");
    char *p = getlocalhostip();
    printf("--------8--------\n");
    printf("ip = %s\n", p);



    printf("size = %d\n", sizeof(unsigned int));
    printf("size = %d\n", sizeof(FLAGS));
    printf("size = %d\n", sizeof(DIAMETER_HEAD));

    return 0;
}
