//2019 round2 csp problem 2
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define ull unsigned long long
ull Pow(ull a)//用位运算或者pow会炸
{
	ull ans=1;
	for(ull register i=1;i<=a;++i)
		ans*=2;
	return ans;
}
void code(int n,unsigned long long k,string &s){
    if(n==1){
        if(k==1){
            s+="0";
            return;
        }
        else if(k==2){
            s+="1";
            return;
        }
    }
    else{
        if(k<=Pow(n-1)){
            s+="0";
            code(n-1,k,s);
        }
        else if(k>Pow(n-1)){
            s+="1";
            code(n-1,(Pow(n)-k)+1,s);
        }
    }
}
int main()
{
    int n;
    ull k;
    cin>>n>>k;
    string s="";
    if(k==Pow(64)-1)
        s="1000000000000000000000000000000000000000000000000000000000000000";
    else
        code(n,k+1,s);
    cout<<s<<endl;
}


