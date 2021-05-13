

 void iSort(int *a,int n,int ascending)
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
char* author(int i)
{
    if(i==1)
    {
        return "10185102136";
    }
    if(i==2)
    {
        return "???";
    }
    return "";
}



