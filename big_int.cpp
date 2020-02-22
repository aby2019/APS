#include<iostream>
#include<vector>
#include<string>
using namespace std;

typedef vector <int> big;
void operator >>(istream &in,big &a)
{
    string s;
    cin>>s;
    int len=s.length();
    for(int i=0;i<len;i++)
    {
        a.push_back(s[i]-48);
        if(a[i]>9)
        {
            cout<<"invalid number";
            exit(1);
        }
    }
}
void operator << (ostream &out,big a)
{
    int len=a.size();
    for(int i=0;i<len;i++)
    cout<<a[i];

}
big operator + (big &a,big &b)
{
    int carry=0;
    int s,l;//small and large
    int alen,blen;
    alen=a.size();
    blen=b.size();
    if(alen>blen)
    {
        l=alen;
        s=blen;
    }
    else
    {
        l=blen;
        s=alen;
    }
    big c(l+1);
    for(int i=l-1,j=s-1;i>=0;i--,j--)
    {
        int temp;
        if(s>0)
        {

            if(alen>blen)
            temp=a[i]+b[j]+carry;
            else
            temp=a[j]+b[i]+carry;
            if(temp>9)
            {
                c[i+1]=temp%10;
                carry=1;
            }
            else
            {
                c[i+1]=temp;
                carry=0;
            }
        }
        else
        {
            if(alen>blen)
            temp=a[i]+carry;
            else
            temp=b[i]+carry;
            if(temp>9)
            {
                c[i+1]=temp%10;
                carry=1;
            }
            else
            {c[i+1]=temp;
            carry=0;}
        }
    s--;
    }
    c[0]=carry;
    if(c[0]==0)
    c.erase(c.begin());
    return c;
}
int operator ==(big a,big b)
{
       int k=0;
        while(!a[k])
        {
            if(a.size()>1)
            a.erase(a.begin());
            else
            break;
         }
         k=0;
        while(!b[k])
        {
        if(b.size()>1)
        b.erase(b.begin());
        else
        break;
        }
    int alen=a.size();
    int blen=b.size();
    //if(alen<blen)
    if(alen>blen||alen<blen)
    return 0;
    else
    {
        int i=0;
        while(i<blen)
        {
            if(a[i]!=b[i])
            break;
            i++;
        }
        if(i==blen)
        return 1;
        else
        return 0;
    }
}

big operator +(big &a,int b)
{
    big c;
    int temp=b;
    while(temp)
    {
        c.insert(c.begin(),temp%10);
        temp=temp/10;
    }

    return (a+c);
}
big operator -(big &a,big &b)
{
    big c;
    if(a==b)
    {c.push_back(0);
    return c;}
    if(b[0]==0)
    return a;

    int alen=a.size();
    int blen=b.size();
    big temp(blen);
    for(int i=0;i<blen;i++)
        temp[i]=9-b[i];


    int k;
    for(k=blen-1;(k>=0&&temp[k]==9);k--)
        temp[k]=0;
        temp[k]=temp[k]+1;
        for(int i=0;i<(alen-blen);i++)
        temp.insert(temp.begin(),9);

        c=a+temp;
        c.erase(c.begin());
        k=0;
        while(!c[k])
        c.erase(c.begin());
        return c;

}
big operator *(big &a,big &b)
{
 big check;
    big res;
    check.push_back(0);
    if(b==check||a==check)
    {
            res.push_back(0);
            return res;
    }
    int alen=a.size();
    int blen=b.size();
    big c(alen+blen,0);

    for(int i=blen-1;i>=0;i--)
    {
        for(int j=alen-1;j>=0;j--)
        {
            int temp=a[j]*b[i];
             temp=c[i+j+1]+temp;
             if(temp>9)
             {
                c[i+j]=c[i+j]+(temp/10);
                c[i+j+1]=(temp%10);
             }
             else
             c[i+j+1]=temp;
        }

    }
     int k=0;
        while(!c[k])
        c.erase(c.begin());
        return c;
    return c;
}
big operator *(big &a,int b)
{
    big check;
    big res;
    check.push_back(0);
    if(b==0||a==check)
    {
            res.push_back(0);
            return res;
    }
    big c;
        int temp=b;
        while(temp)
    {
        c.insert(c.begin(),temp%10);
        temp=temp/10;
    }
    return a*c;
}

int operator <(big a,big b)
{
        int k=0;
        while(!a[k])
        {
            if(a.size()>1)
            a.erase(a.begin());
            else
            break;
         }
         k=0;
        while(!b[k])
        {
        if(b.size()>1)
        b.erase(b.begin());
        else
        break;
        }
    int flag=0;
    int alen=a.size();
    int blen=b.size();
    //if(alen<blen)
    if(alen>blen)
    return 0;
    else if(alen<blen)
    return 1;
    else
    {
        int i=0;
        while(i<blen)
        {
            if(a[i]<b[i])
            {
                flag=1;
                break;}
            if(a[i]>b[i])
            {
                break;
            }

            i++;
        }

       if(i!=blen&&flag==1)
       return 1;
       else return 0;
    }

}
big operator /(big &b,big &a)
{

    big result;
    big check;
    check.push_back(0);
    if(a==check)
    {
        cout<<"NOT defined";
        exit(1);
    }

    if(b<a)
    {result.push_back(0);
    return result;
    }
    if(a.size()==1&&b.size()==1)
    {
        result.push_back(b[0]/a[0]);
        return result;
    }

    int i=0;
    big temp;
    big x=a;//divisor is x
    temp.push_back(b[i]);
    int blen=b.size();
    while(i<blen-1)
    {
        if(temp<a)
        {
            temp.push_back(b[++i]);
        }
        if(temp<a)
        {

        result.push_back(0);
        continue;
        }
        int m;
        m=0;
        x=a;
        while(x<temp||x==temp)
        {
            m++;
            x=a*m;

        }
        if(m==0||m==1)
        m=1;
        else
        {
            x=x-a;
            m=m-1;
        }
        result.push_back(m);
        temp=temp-x;
         }
   return result;
}
big operator %(big &a,big&b){
big c=a/b;
big res=c*b;
res=a-res;
return res;

}
big fact(big &a)
{
    big res;
    res.push_back(1);
    big i;
    i.push_back(2);

    while(!(i==a+1))
    {
        res= res*i;
        i=i+1;

    }
    return res;
}
big gcd(big &a,big &b)
{
    big result;
    big temp;
    temp.push_back(0);
    if(b==temp)
    return a;

    else
    {
        big x;
        x=a%b;
        result=gcd(b,x);
    }
return result;
}
big power(big &a,big &b)
{
    big res;
    big check;
    big two;

    if(two.empty())
    {
    two.push_back(2);
    check.push_back(0);
    }
    if(b==check)
    {

        res.push_back(1);
        return res;
    }
    big temp=b/two;
    big ans=power(a,temp);
    big t;
    if((b%two)==check)
    {
        return (ans*ans);
    }
    t=ans*ans;
    res=a*t;
    return (res);


}
int main()
{

    int t,k;
    cin>>t;
    while(t--)
    {
        cin>>k;
        if(k==1)
        {
            big a,b,c;
            cin>>a;
            cin>>b;
            cout<<power(a,b);
        }
        else if(k==2)
        {
            big a,b,c;
            cin>>a;
            cin>>b;
            cout<<gcd(a,b);
        }
        else if(k==3)
        {
            big a,b,c;
            cin>>a;
            cout<<fact(a);
        }
        else
        {
            cout<<"invalid input";
        }
    }

    return 0;
}
