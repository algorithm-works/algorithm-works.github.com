#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define mod 1000000007
#define maxint 2147483648ll
#define nc1
#define rg register
#define rgv
#define rg1 rgv
#define rg2 rgv
#define rg3 rgv
#define rg4 rgv
#define rg5 rg
#define rg6 rg
#define sorc
#define psh(a,l,p) (a)[(l)++]=(p)
typedef long long ll;
namespace basicmath{
	inline ll mp(ll a,ll b,ll p){
	#ifdef __int128
		return (__int128)a*(__int128)b%p;
	#else
		if(p<3037000000ll) return a*b%p;
#ifdef nc1
		if(p<1099511627776ll) return (((a*(b>>20)%p)<<20)+(a*(b&((1<<20)-1))))%p;
#endif
		ll d=(ll)(a*(long double)b/p+0.5); ll ret=(a*b-d*p)%p;
		if (ret<0) ret+=p;
		return ret;
	#endif
	}
	inline ll fp(int a,int b,int p){ a%=p,b%=p-1; int ans=1; for(;b;b>>=1,a=(ll)a*a%p) if(b&1) ans=(ll)ans*a%p; return ans; }
	inline ll fp(ll a,ll b,ll p){ a%=p,b%=p-1; ll ans=1ll; for(;b;b>>=1,a=mp(a,a,p)) if(b&1) ans=mp(a,ans,p); return ans; }
	template<int max=10000007> struct sieve{
		int q[max+5]; int pr[max/4],pl,rxsiz;
		inline void generate(rg3 int n=max){
			if(n<=rxsiz) return; if(n>max) return;
			rxsiz=n;
			for(rg1 int i=2;i<=n;++i){
				if(!q[i]) pr[pl++]=i,q[i]=i;
				for(rg2 int j=0;j<pl;++j){
					rg4 int t=i*pr[j];
					if(t>n) break;
					q[t]=pr[j]; if(q[i]==pr[j]) break;
				}
			}
		}
		inline int operator()(int n){
			#ifdef sorc
			if(n>=pl) return 0;
			if(n<0) return 0;
			#endif
			return pr[n];
		}
		#ifdef sorc
		int sbcc;
		inline int operator[](int n){
			if(n>rxsiz) return sbcc;
			if(n<0) return sbcc;
			return q[n];
		}
		#else
		inline int operator[](int n){
			return q[n];
		}
		#endif
	};
	namespace primeTesting{
		const int llrtm=7;
		ll q[llrtm]={2, 325, 9375, 28178, 450775, 9780504, 1795265022ll};//for numbers less than 2^64 test these seven numbers are enough
		inline bool witness(ll a,rg5 ll n){
			a%=n;
			if(!a) return 0;
			rg5 int t=0; ll u=n-1; for(;~u&1;u>>=1) ++t;
			rg5 ll x=fp(a,u,n),xx=0; while(t--){
				xx=mp(x,x,n); if(xx==1 && x!=1 && x!=n-1) return 1;
				x=xx;
			}
			return xx!=1;
		}
		inline bool miller(ll n){
			if(!n) return 0;
			if(n==2) return 1;
			for(int i=0;i<llrtm;++i) if(witness(q[i],n)) return 0;
			return 1;
		}
		template<class T> inline bool miller(ll n,T& sv){//T should have the same API as sieve
			if(n<=sv.rxsiz && sv[n]==n) return 1;
			return miller(n);
		}
		//the both miller tests are deterministic
		struct pmt{
			virtual inline bool operator()(ll n){
				return 1;
			}
		};
		struct mr_s100k:public pmt{
			sieve<100000> sv;
			inline mr_s100k(){
				sv.generate(100000);
			}
			inline bool operator()(ll n){
				return miller(n,sv);
			}
		};
		struct mr_0:public pmt{
			inline bool operator()(ll n){
				return miller(n);
			}
		};
	}
	using namespace primeTesting;
	namespace gcd{
		inline ll euclid(ll a,ll b){return a?euclid(b%a,a):b;}
		inline ll stein (rg6 ll a,rg6 ll b){
//			if(a<0) a=-a;
			rg6 ll ret=1;
			while(a){
				if((~a&1)&&(~b&1)) ret<<=1,a>>=1,b>>=1; else
				if(~a&1) a>>=1; else if(~b&1) b>>=1; else
				{ if(a<b) std::swap(a,b); a-=b; }
			}
			return b*ret;
		}
	}
	namespace qmutils{
		inline ll qm1(rg ll a,rg ll q){//if a < 0 a+=q
			return a+((-((unsigned long long)a>>63))&q);
		}
		inline ll qm2(rg ll a,rg ll q){//if a>= q a-=q
			return a-((-((unsigned long long)(q+(~a))>>63))&q);
		}
	}
	using namespace qmutils;
	#define dgcd gcd::stein
	namespace factor{
		struct factr{
			ll q[30],p[30],c[30];
			int tl;
			virtual inline int operator()(ll a,pmt& q){
				return 0;
			}
		};
		struct rho:public factr{
			ll sq[70],sql;
			private:
				ll rhox(ll n,ll c,ll u){
					ll i=1,k=2,y=u,x0=u;
					while(1){
						++i; x0=qm2(mp(x0,x0,n)+c,n);
						ll d=dgcd(y-x0,n);
						if(d!=1 && d!=n) return d;
						if(y==x0) return n;
						if(i==k) y=x0,k<<=1;
					}
				}
				void fact_f(ll a,pmt& q){
					if(q(a)) psh(sq,sql,a); else
					{
						ll x=a;
						while(x==a){
							ll c=rand()%a,d=(rand()&31)+3;
							x=rhox(a,d,c);
						}
						fact_f(x,q),fact_f(a/x,q);
					}
				}
				inline void norm(){
					std::sort(sq,sq+sql);
					tl=0;
					for(rg int i=0,j=1;i<sql;i=(j++)){
						q[tl]=sq[i],p[tl]=1,c[tl]=sq[i];
						while(sq[j]==sq[i] && j<sql) c[tl]*=sq[j++],++p[tl];
						++tl;
					}
				}
			public:
				inline int operator()(ll a,pmt& q){
					sql=0;
					fact_f(a,q);
					norm();
					return tl;
				}
		};
		template<int nx=1000000> struct rhos:public factr{
			ll sq[70],sql;
			sieve<nx> sv;
			private:
				ll rhox(ll n,ll c,ll u){
					ll i=1,k=2,y=u,x0=u;
					while(1){
						++i; x0=qm2(mp(x0,x0,n)+c,n);
						ll d=dgcd(y-x0,n);
						if(d!=1 && d!=n) return d;
						if(y==x0) return n;
						if(i==k) y=x0,k<<=1;
					}
				}
				void fact_f(ll a,pmt& q){
					if(a<=nx){//directly factor a
						while(a!=1){
							psh(sq,sql,sv[a]);
							a/=sv[a];
						}
						return;
					}
					if(q(a)) psh(sq,sql,a); else
					{
						ll x=a;
						while(x==a){
							ll c=rand()%a,d=(rand()&31)+3;
							x=rhox(a,d,c);
						}
						fact_f(x,q),fact_f(a/x,q);
					}
				}
				inline void norm(){
					std::sort(sq,sq+sql);
					tl=0;
					for(rg int i=0,j=1;i<sql;i=(j++)){
						q[tl]=sq[i],p[tl]=1,c[tl]=sq[i];
						while(sq[j]==sq[i] && j<sql) c[tl]*=sq[j++],++p[tl];
						++tl;
					}
				}
			public:
				rhos(){
					sv.generate(nx);
				}
				inline int operator()(ll a,pmt& q){
					sql=0;
					fact_f(a,q);
//					for(int i=0;i<sql;++i) printf("%d ",sq[i]);
					norm();
					return tl;
				}
		};
		//maybe EC method will be added
	}
	using namespace factor;
	struct factorsGetter{
		//get all factors
		std::vector<ll> fac;
		void get(ll q,int le,factr& p){
			if(le==p.tl) fac.push_back(q); else{
				get(q,le+1,p);
				for(int i=1;i<=p.p[le];++i) get((q*=p.q[le]),le+1,p);
			}
		}
		int operator()(factr& p){
			fac.clear();
			get(1,0,p);
			return fac.size();
		}
	};
}
int main(){
	return 0;
}
