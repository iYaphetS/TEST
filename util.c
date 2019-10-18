#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define ROK 0
#define ERR 1

/*根据规则检查主机名或者域名配置*/
int filterHostorDomainName(const char *pName)
{
    assert(pName);
    int len = strlen(pName);
    char c;
    int count = 0;
    if ( (!isdigit(pName[0]) && !isalpha(pName[0])) || pName[len - 1] == '-')
        return ERR;
    
    while ((c = *pName++) != '\0')
    {
        if (isdigit(c) || isalpha(c) || c == '.' || c == '_' || c == '-')
        {
            if (c == '.' || c == '_' || c == '-')
                count += 1;
            else
                count = 0;
        }
        else
            return ERR;

        if (count >= 2)
            return ERR;  
    }
    return ROK;    
}

/*主机名或者域名匹配原则---最大匹配原则*/
int matchHostorDomainName(const char *mName, const char *pName)
{
    assert(mName);
    assert(pName);
    if (filterHostorDomainName(mName) || filterHostorDomainName(pName))
        return ERR;
    int mlen = strlen(mName);
    int plen = strlen(pName);
    if (strcmp(mName, pName))
    {
        while (*mName != '\0' && mlen >= plen)
        {
            if (*mName++ == '.')
            {
                if (!strcmp(mName, pName))
                    return ROK;
            }
            mlen--;
        }
        return ERR;
    }

    return ROK;
}

int MaxPrefixMatch(const char *msgStr, const char *confStr)
{
    if (NULL == msgStr || NULL == confStr)
        return ERR;
    int mlen = strlen(msgStr);
    int clen = strlen(confStr);
    const char *EmsgStr = msgStr + mlen - 1;
    if (strcmp(msgStr, confStr))
    {
	printf("---------%d %d------\n", mlen, clen);
        while (mlen >= clen)
        {
		printf("msg = %s\n", msgStr);
		printf("con = %s\n", confStr);
            if (*EmsgStr-- == '.')
            {
		printf("msg = %s\n", msgStr);
		printf("con = %s\n", confStr);
		printf("%d\n", mlen - 1);
                if (!strncmp(msgStr, confStr, mlen - 1))
                    return ROK;
            }
            mlen--;
        }
        return ERR;
    }

    return ROK;
}

/*根据规则检查各种配置表参数名称*/
int filterConfigName(const char *cName)
{
    assert(cName);
    char c;
    printf("len = %d\n", strlen(cName));
    while ( (c = *cName++) != '\0')
    {
        printf("---%x %x\n", c, *cName);
        if ( !isdigit(c) && !isalpha(c) &&  !((c & 0x80) && (*cName++ & 0x80) && (*cName++ & 0x80)) )
        {
            printf("--------%x %x\n", c, *cName);
            return ERR;
        }
    }
    return ROK;
}

/*字符串大小写转化*/
char * cStrlwrandStrupr(char *s, const int flag)
{
    assert(s);
    char *ret = s;

    while (*s)
    {   
        if (flag == 1)
        {
            if ( (*s >= 'A') && (*s <= 'Z') )
                *s += 32;
        }
        else
        {
            if ( (*s >= 'a') && (*s <= 'z') )
                *s -= 32;
        }
        s++;
    }
    return ret;
}

int main()
{

    char *Host = "m-nc000.mcc460.3gppnetwork";
    char *msg_Host = "mcc460.3gppnetwork.or-g";
    char *msg_Host1 = "m-nc000.mcc460.3gppnetwork.or-g";

    if (ROK != filterHostorDomainName(Host))
        printf("ERR\n");
    else
        printf("OK\n");

    if (ROK != matchHostorDomainName(msg_Host, Host))
        printf("match fail\n");
    else
        printf("match suc\n");

   if (ROK != MaxPrefixMatch(msg_Host1, Host))
	printf("ERR1111\n");
   else
	printf("OK1111\n");


    if (ROK != filterConfigName("~!@#$^&*(){[}]|;:?/><"))
        printf("config err\n");
    else
        printf("config ok\n");

    char s[] = "SAFDAsa@sxSADA";
    printf("-------------------%s\n", cStrlwrandStrupr(s, 0));

    char dst[100] = {'\0'};
    sprintf(dst, "%s%d", "192.168.1", 245);

    printf("dst = %s\n", dst);

    char s1[100] = {0};
    sprintf(s1, "%d,%d,%d,", 1, 2, 3);
    char s2[100] = {0};
    sprintf(s2, "%d,%d,%d,", 11, 12, 13);

    char buf[100] = {0};
    sprintf(buf, "%d;%s;%d;%s", 1000, s1, 2000, s2);

    printf("buf = %s\n", buf);


    return ROK;
}
