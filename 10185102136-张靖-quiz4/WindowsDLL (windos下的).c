#include <windows.h>
#ifdef __cplusplus
#define EXPORT extern "C" __declspec (dllexport)
#else
#define EXPORT __declspec (dllexport)
#endif

EXPORT WINAPI int sum(int* a, int n);
EXPORT _cdecl int plus(int a, int b);


BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved)
{
     return TRUE ;
}

EXPORT int WINAPI f(int x, int *a)
{
    return a[0]*x*x+a[1]*x+a[2];
}
EXPORT void _cdecl iSort(int *a,int n,int ascending)
{
    if(ascending==1)
    {
        int i,j,k,index,temp;
        for(int i=0;i<n-1;i++)
        {
            index=i;
            for(j=i+1;j<n;j++)
            {
                if(a[j]<a[index])
                {
                    index=j;
                }
            }
            if(index!=i)
            {
                temp=a[index];
                a[index]=a[i];
                a[i]=temp;
            }
        }
    }
    else
    {
        int i,j,k,index,temp;
        for(int i=0;i<n-1;i++)
        {
            index=i;
            for(j=i+1;j<n;j++)
            {
                if(a[j]>a[index])
                {
                    index=j;
                }
            }
            if(index!=i)
            {
                temp=a[index];
                a[index]=a[i];
                a[i]=temp;
            }
        }
    }
}

EXPORT char* _cdecl author(int i)
{
    if(i==1)
    {
        return "10185102136";
    }
    if(i==2)
    {
        return "’≈æ∏";
    }
    return "";
}



