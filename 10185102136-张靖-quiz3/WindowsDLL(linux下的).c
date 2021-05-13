


int sum(int* a, int n);
int plus(int a, int b);

 int  f(int x, int *a)
{
    return a[0]*x*x+a[1]*x+a[2];
}
 char* lower(char* s)
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

 char*  author(int i)
{
    if(i==1)
    {
        return "10185102136";
    }
    if(i==2)
    {
        return "zhangjing";
    }
    return "";
}



