#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int N=200,M=3000,P=998244353;//FFT（雾
int n,m;
ll ans=1;
ll cnt[N],w[N][M],f[N][M];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			scanf("%lld",&w[i][j]),cnt[i]=(cnt[i]+w[i][j])%P;
		ans=(ans*(cnt[i]+1))%P;//计算全部答案
	}
	ans=(ans+P-1)%P;//减去全部不选的情况
	for(int i=1;i<=m;i++)
	{
		memset(f,0,sizeof(f));
		f[0][0]=1;//DP初值
		for(int j=1;j<=n;j++)
			for(int k=0;k<=2*(j-1);k++)
			{
				f[j][k]=(f[j][k]+f[j-1][k]*(cnt[j]-w[j][i]))%P;
				f[j][k+1]=(f[j][k+1]+f[j-1][k])%P;
				f[j][k+2]=(f[j][k+2]+f[j-1][k]*w[j][i])%P;
			}
		for(int j=n+1;j<=2*n;j++)
			ans=(ans+P-f[n][j])%P;//减去当前枚举到的不合法方案
	}
	printf("%lld",ans);
	return 0;
}
