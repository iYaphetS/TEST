#include <iostream>
#include <string>
#include <ctreing>
using namespace std;



CString CTestDlg::GetIPAddress(const CString &sHostName)
{
    CString strIP = "";
    struct hostent FAR *lpHostEnt = gethostbyname (sHostName);
    if (lpHostEnt == NULL) return "";
    LPSTR lpAddr = lpHostEnt->h_addr_list[0];
    if (lpAddr)
    {
        struct in_addr  inAddr;
        memmove (&inAddr, lpAddr, 4);
        strIP = inet_ntoa (inAddr);
        if (strIP.IsEmpty()) return "";
    }
    else return "";
     
    return strIP;
}

class S
{
    S(){};
    virtual void print()
    {
        printf("S-----\n");
    }
};

class B : public S
{
    B(){};
    virtual void print()
    {
        printf("B-----\n");
    }
};


int main()
{

    S *s =  


    return 0;
}