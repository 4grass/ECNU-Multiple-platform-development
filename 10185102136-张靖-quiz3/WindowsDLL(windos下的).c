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
EXPORT char* _cdecl lower(char* s)
{
    for(int i=0;s[i]!='\0';i++)
    {
        if(s[i]>='A' && s[i]<='Z')
        {
            s[i]+=32;
        }
    }
    return s;
}

EXPORT char* _cdecl author(int i)
{
    if(i==1)
    {
        return "10185102136";
    }
    if(i==2)
    {
        return "ÕÅ¾¸";
    }
    return "";
}



