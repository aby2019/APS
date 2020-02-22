#include<bits/stdc++.h>
using namespace std;

struct node {
int data;
struct node *left;
struct node *right;
 int height;
 int nleft;//no. of nodes in left subtree
 int nright;//no. of nodes in right subtree
};

int get_height(node *temp)
{
    if (!temp)
        return -1;
    else
    return temp->height;
}

node * rightrotate(node *temp)
{
    node * t1=temp->left;
    node * t2=t1->right;
    temp->left=t2;
    t1->right=temp;

    t1->nright=t1->nright+1+temp->nright;
    temp->nleft=temp->nleft-1-t1->nleft;
    temp->height=1+max(get_height(temp->left),get_height(temp->right));
    t1->height=1+max(get_height(t1->left),get_height(t1->right));
    
    return t1;
}
node *leftrotate(node *temp)
{
    node *t1=temp->right;
    node *t2=t1->left;
    temp->right=t2;
    t1->left=temp;

    temp->height=1+max(get_height(temp->left),get_height(temp->right));
    t1->height=1+max(get_height(t1->left),  get_height(t1->right));

    t1->nleft=1+temp->nleft+t1->nleft;
    temp->nright=temp->nright-1-t1->nright;

   
    return t1;
}
node* leftrightrotate(node *temp)
{
    temp->left=leftrotate(temp->left);//left of original node;
    return (rightrotate(temp)); 
   
}
node *rightleftrotate(node *temp)
{
    temp->right=rightrotate(temp->right);
    return (leftrotate(temp));
}
int getdiff(node *temp)
{
    if(!temp)
        return -1;
    else
        return (get_height(temp->left)-get_height(temp->right));
}
node * insert_element(node *temp,int x)
{

    if(!temp)
    {
        node *newnode = new node();
        newnode->right =NULL;
        newnode->left=NULL;
        newnode->data=x;
        newnode->height=0;
        newnode->nright=0;
        newnode->nleft=0;
        return newnode;
    }

    else if(x>temp->data)
       {
        temp->right=insert_element(temp->right,x);
        temp->nright+=1;
       }
    else if(x<temp->data)
    {
        temp->left=insert_element(temp->left,x);
       temp->nleft+=1;
    }
    else 
    {
        return temp;
    }
    

    int lh=get_height(temp->left);
    int rh=get_height(temp->right);
    temp->height=1+max(lh,rh);
    //cout<<temp->height;
   // printf("hi\n" );
    //int diff= (temp->left->height)-(temp->right->height);
    int diff=getdiff(temp);
    //cout<<diff;
    if(diff>1)//that means it is left heavy
    {
            if(x<(temp->left->data))
                return rightrotate(temp);
            else
                return leftrightrotate(temp);
    }
    if(diff<-1)//that means it is right heavy
    {
        if(x>(temp->right->data))
            return leftrotate(temp);
        else
            return rightleftrotate(temp);
    }
    return temp;

}
void inorder(node *temp)
{
    if(!temp)e
    return;
    inorder(temp->left);
    //cout<<"temp= "<<temp->data<<" height= "<<temp->height<<" "<<endl;//<<"left count= "<<temp->nleft<<"right count ="<<temp->nright<<endl;
    //cout<<temp->data<<" \t ";
    cout<<"temp= "<<temp->data<<" height= "<<temp->height<<"left count= "<<temp->nleft<<"right count ="<<temp->nright<<endl;

    inorder(temp->right);
}

int smallest(node *temp,int x)
{
    if(temp->nleft+1==x)//||temp->nleft==temp->nright)
        return temp->data;

    else if(x<=temp->nleft)
       return smallest(temp->left,x);
    else
        return smallest(temp->right,x-temp->nleft-1);
}
float findmedian(node * temp,int c)
{

    int x;
    float a,b;
    // if(!c%2)
    if(c==1)
        return temp->data;
    if(c%2==0)
    {
         a=smallest(temp,c/2);
         b=smallest(temp,c/2+1);
         
       // cout<<"median ="<<a<<" "<<b<<" "<<endl;
        return (float)((a+b)/2);
    }
        else

        {
            int  median= smallest(temp,c/2+1);
       // cout<<"median ="<<median<<endl;
        return ((float)median);
        }
}
node *get_max(node *temp)//max element in left subtree
{
   
    node *t1=temp;
    while(t1->right)
        t1=t1->right;
    return t1;
}

node * delete_element(node *temp,int x)
{
    if(!temp)
        return temp;
    else if(x>temp->data)
    {
        temp->nright--;
        temp->right=delete_element(temp->right,x);
    }
    else if(x<temp->data)
    {
        temp->nleft--;
        temp->left=delete_element(temp->left,x);
    }
    else
    {
        if(!temp->left&&!temp->right)
        {
            free(temp);
            temp=NULL;
            return temp;
        }
        else if(!temp->left&&temp->right)
        {
            node *aux=temp->right;
            free(temp);
            temp=NULL;
            return aux;
        }
        else if(!temp->right&&temp->left)
        {
            node *aux=temp->left;
            free(temp);
            temp=NULL;
            return aux;
        }
        else
        {
            node *aux=get_max(temp->left); //only data is enough 
            temp->data=aux->data;
            temp->nleft--;
            temp->left=delete_element(temp->left,temp->data); 

        }
    }
    int lh=get_height(temp->left);
    int rh=get_height(temp->right);
    temp->height=1+max(lh,rh);
    
    int diff=getdiff(temp);
    if(diff>1)//that means it is left heavy
    {
           if(get_height(temp->left->left)-get_height(temp->left->right)>0)
                return rightrotate(temp);
            else
                return leftrightrotate(temp);
    }
    if(diff<-1)//that means it is right heavy
    {
      if(get_height(temp->right->right)-get_height(temp->right->left)>0)
            return leftrotate(temp);
        else
            return rightleftrotate(temp);
    }
    return temp;

}
bool check (node *temp,int x)
{
    if(temp==NULL)
        return false;
    else if(x>temp->data)
        check(temp->right,x);
          else if(x<temp->data)
        check(temp->left,x);
    else return true;
}
int  find_closest(node * temp,int x)
{
    while(temp!=NULL)
    {
        int current=temp->data;
        int diff=abs(current-x);
        if(x>temp->data)
            {
                if(!temp->right)
                    return current;
                    temp=temp->right;
                if((abs(temp->data)-x)<diff)
                    current=abs(temp->data);
                else
                    return current;
            }
        else if(x<temp->data)
           {
            if(!temp->left)
                return current;
            temp=temp->left;
            if((abs(temp->data)-x)<diff)
                    current=abs(temp->data);
                else
                    return current;
           } 
             else
            return temp->data;
    }
}
int largest(node * temp,int x)
{
    if(x==temp->nright+1)
        return temp->data;
    else if(x<=temp->nright)
        return largest(temp->right,x);
    else 
        return largest(temp->left,x-1-temp->nright);

}
int range_left(node *temp,int a,int num)
{
    if(temp==NULL)
        return num;
    else if(a<temp->data)
        range_left(temp->left,a,num);
    else if(a>temp->data)
        range_left(temp->right,a,num-temp->nleft-1);
    else
        {   
            num=num-temp->nleft;
            return num;
        }
}
int range_right(node *temp,int a,int num)
{

    if(temp==NULL)
        return num;
    else if(a<temp->data)
        range_right(temp->left,a,num-1-temp->nright);
    else if(a>temp->data)
        range_right(temp->right,a,num);
    else
        {
            num=num-temp->nright;
            return num;
        }
}
int range(node * temp,int a,int b,int num)
{
    if(a<b)
    {
        int x=range_left(temp,a,num);
        //cout<<"left range = "<<x<<endl;
        int y=range_right(temp,b,x);

        return y;
    }
    else if(a>b)
    {
        int x=range_left(temp,b,num);
       // cout<<"left range = "<<x<<endl;
        int y=range_right(temp,a,x);
        return y;
    }
    else
    {
        if(check(temp,a))
            return 1;
        else return 0;
    }
}
int main()
{
    node * root=NULL;
    int num=0;
    int n;
    while(1)
    {
        cout<< "1:insert\n2:delete:\n3:inorder\n4:check if no. is present or not.\n5:find closest value to a num\n6:find kth largest element\n7:find the range between a and b\n";
        int c;
        cin>>c;
        cout<<endl;
        if(c==1)
        {
            cin>>n;
            if(!check(root,n))
            {
                num++;
                cout<<endl;
                root=insert_element(root,n);
                inorder(root);
                cout<<endl;
            }
            else 
                {
                    cout<<"number already exists"<<endl;
                }

        }
       else if(c==2)
        {
            cin>>n;
            cout<<endl;
            if(check(root,n))
            {
                num--;
                root=delete_element(root,n);
            }
        else
            cout<<"element not found"<<endl;
            inorder(root);
            cout<<endl;
            
        }
        else if(c==3)
            {inorder(root);
        cout<<endl;
         }
         else if(c==4)
         {
            cin>>n;
            if(check(root, n))
                cout<<"FOUND"<<endl;
            else 
                cout<<"NOT FOUND"<<endl;  
         }
         else if(c==5)
         {
            cin>>n;
            cout<<find_closest(root,n)<<endl;
         }
        else if (c==6)
        {
            cin>>n;
            cout<<"largest element ="<<largest(root,n)<<endl;

        }
        else if(c==7)
        {
            int a,b;
            cin>>a>>b;
            
            cout<<"no of elements = "<<range(root,a,b,num)<<endl;
        }
        else if(c==8)
        {
            cout<<"total count"<<num;
        }
        else
        {
                cout<<"wrong input";
        }

    }
    return 0;

}
