#include<cstdio>
#include<vector>
using namespace std;

#define rep(i,__l,__r) for(int i=__l,i##_end_=__r;i<=i##_end_;++i)
#define fep(i,__l,__r) for(int i=__l,i##_end_=__r;i>=i##_end_;--i)
#define writc(a,b) fwrit(a),putchar(b)
#define mp(a,b) make_pair(a,b)
#define ft first
#define sd second
#define LL long long
#define ull unsigned long long
#define pii pair<int,int>
// #define FILEOI

#define cg (c=getchar())
template<class T>inline void qread(T& x){
	char c;bool f=0;
	while(cg<'0'||'9'<c)if(c=='-')f=1;
	for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
	if(f)x=-x;
}
inline int qread(){
	int x=0;char c;bool f=0;
	while(cg<'0'||'9'<c)if(c=='-')f=-1;
	for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
	return f?-x:x;
}
#undef cg
template<class T,class... Args>inline void qread(T& x,Args&... args){qread(x),qread(args...);}
template<class T>inline T Max(const T x,const T y){return x>y?x:y;}
template<class T>inline T Min(const T x,const T y){return x<y?x:y;}
template<class T>inline T fab(const T x){return x>0?x:-x;}
inline void getInv(int inv[],const int lim,const int MOD){
	inv[0]=inv[1]=1;for(int i=2;i<=lim;++i)inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
}
template<class T>void fwrit(const T x){
	if(x<0)return (void)(putchar('-'),fwrit(-x));
	if(x>9)fwrit(x/10);putchar(x%10^48);
}

const int MAXN=2000;

struct edge{
	int to,nxt;
	edge(){}
	edge(const int T,const int N):to(T),nxt(N){}
}e[(MAXN<<1)+5];
int tail[MAXN+5],ecnt,siz[MAXN+5];
inline void add_edge(const int u,const int v){
	++siz[u],++siz[v];
	e[++ecnt]=edge(v,tail[u]);tail[u]=ecnt;
	e[++ecnt]=edge(u,tail[v]);tail[v]=ecnt;
}

int N,minp;
int pt[MAXN+5];
int pre[MAXN+5][MAXN+5],nxt[MAXN+5][MAXN+5];
//这条边的 前驱,后继
int rt[MAXN+5][MAXN+5][2];
//点 u 的某一条边的 前根节点、后根节点
int len[MAXN+5][MAXN+5];
//这条边 所在链 的链表长度

inline void init(){
	qread(N);
	ecnt=0;
	rep(i,1,N)qread(pt[i]),tail[i]=siz[i]=0;
	rep(i,1,N+1)rep(j,1,N+1)len[i][j]=pre[i][j]=nxt[i][j]=rt[i][j][0]=rt[i][j][1]=0;

	int u,v;
	rep(i,1,N-1){
		qread(u,v);
		add_edge(u,v);
		pre[u][v]=pre[v][u]=nxt[u][v]=nxt[v][u]=0;
		rt[u][v][0]=rt[u][v][1]=v;
		rt[v][u][0]=rt[v][u][1]=u;
		len[u][v]=len[v][u]=1;
	}
}

void findPath(const int u,const int p){//当前节点、前一个节点
	int a=rt[u][p][0],b=rt[u][p][1],ta,tb;
	//a:来的边的前根 ; b:来的边的后根
	if(p==N+1){//这是起点
		for(int i=tail[u],v;i;i=e[i].nxt){//从哪条边起飞
			v=e[i].to;
			ta=rt[u][v][0],tb=rt[u][v][1];
			if(ta!=v || (pre[u][p]==tb && len[u][ta]<siz[u]))
			//条件一:如果这条边已经有一个起点且不是自己
			//条件二:如果后面的那条边已经连接尾端, 且这条链的长度无法满足将所有边连起来
				continue;//那么就不能把 边{u,p} 与 边{u,v} 连在一起
			findPath(v,u);//否则可行
		}
	}
	else{
		if(p==b){//如果 边{u,p} 的后面还暂时没有指定必须删哪一条边, 那么就可以考虑枚举一条边接在后面
			if(pre[u][N+1]==0 && (nxt[u][N+1]!=a || len[u][a]==siz[u]))//则可以考虑在点 u 进行降落, 满足以下条件:
			//如果这个点的末删边还没有被指定(必须满足)
			//并且:
			//1.如果这条链接上开头，那么如果必须满足所有的边都在这条链上
			//2.如果没有接上开头，那么长度随意
				minp=Min(minp,u);//如果满足, 则 u 可以作为一个降落点

			for(int i=tail[u],v;i;i=e[i].nxt){//假定 u 为一个中转点, 则再枚举一条边作为 边{u,p} 的出边，与其尾相连
				v=e[i].to;
				ta=rt[u][v][0],tb=rt[u][v][1];
				if(a==ta || ta!=v || nxt[u][N+1]==v)//第一种大情况
				//如果这两条边已经在同一条链上
				//或者这个边不是一个起始边, 即枚举边的前面还有东西
				//或者枚举边是一条起飞边, 即保证它是所有对于 u 的边必须最先删除的边
					continue;//那么 当前 边{u,p} 都不能接在这条枚举边之上
				
				if(nxt[u][N+1]==a && pre[u][N+1]==tb && len[u][a]+len[u][ta]<siz[u])
				//如果这两条边分别属于这个点 最先删除、最后删除 的链表上的 尾、头
				//那么它们组合起来必须等于所有边的数量之和
				//否则, 这就是 提前自闭 的情况
					continue;

				findPath(v,u);//如果以上都不满足, 那么这条边是合法的
			}
		}
		else findPath(nxt[u][p],u);//否则我们只能按照之前的规定访问这条边
	}
}

inline void merge(const int u,const int a,const int b){
//函数条件:以 a 所在的链表为前链表
//并且满足 a 是前链表尾, b 是后链表头
	int ta=rt[u][a][0],tb=rt[u][b][1];
	nxt[u][a]=b;
	pre[u][b]=a;
	for(int i=ta;i && i!=N+1;i=nxt[u][i]){
	//访问链表的基本操作
		//更新每个点的前根、后根
		rt[u][i][0]=ta;
		rt[u][i][1]=tb;
	}
	len[u][ta]+=len[u][b];
}

bool getMark(const int u,const int p){//还原路径, 并且给路径打上标记
//如果这条路径找到终点, 返回 1, 否则返回 0
	if(u==minp){//如果找到了终点
		pre[u][N+1]=p;//把这条边设为最后删除的边
		nxt[u][p]=N+1;//并且把这条边的下一条边标记为 N+1, 表示这条边是最后删除的
		return 1;
	}
	int a=rt[u][p][0],b=rt[u][p][1],ta,tb;
	if(p==N+1){//这是起飞点
		for(int i=tail[u],v;i;i=e[i].nxt){
			v=e[i].to;
			ta=rt[u][v][0],tb=rt[u][v][1];
			if(ta!=v || (pre[u][N+1]==tb && len[u][ta]<siz[u]))
			//如果枚举边前面有东西, 那么这肯定不能接在起始边的后面, 因为它前面已经有个什么 逼 了
			//或者是枚举边连接到末尾, 但是这条单链长度不够将所有的边包含到链里面
				continue;//那么这条边肯定不在路径上面, 可直接跳过
			if(getMark(v,u)){//如果这就是正确的路径
				nxt[u][N+1]=v;//因为 u 点是起飞点, 所以把这条边记录为 u 的起飞边
				pre[u][v]=N+1;//同时标记这条边的前驱, 与前面的 if 相互呼应(这不是语文...)
				return 1;
			}
		}
	}
	else{//如果点 u 是中转点, 那么考虑枚举中转边
		if(p==b){//如果这条边在链上后面没有其他边的时候
			for(int i=tail[u],v;i;i=e[i].nxt){
				v=e[i].to;
				ta=rt[u][v][0],tb=rt[u][v][1];
				if(a==ta || ta!=v || nxt[u][N+1]==v)//参考 findPath() 中相同位置的注释
					continue;
				if(nxt[u][N+1]==a && pre[u][N+1]==tb && len[u][a]+len[u][ta]<siz[u])//同样参考 findPath() 中同样位置
					continue;
				if(getMark(v,u)){
					merge(u,p,v);//把链表合并为一个
					return 1;
				}
			}
		}
		else getMark(nxt[u][p],u);
	}
	return 0;
}

signed main(){
#ifdef FILEOI
	freopen("rdata.out","r",stdin);
	freopen("file.out","w",stdout);
#endif
	int T=qread();
	while(T--){
		init();
		if(N==1){
			writc(1,'\n');
			continue;
		}
		rep(i,1,N){
			minp=N+1;
			findPath(pt[i],N+1);
			// printf("%d\n",minp);
			getMark(pt[i],N+1);
			writc(minp,' ');
		}
		putchar('\n');
	}
	return 0;
}
