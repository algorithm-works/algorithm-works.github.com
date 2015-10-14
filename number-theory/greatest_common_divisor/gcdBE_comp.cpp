#include <cstdio>
//better O(n^2) method
#include "algorithm"
inline long long gcd_binary(long long a,long long b){
	if(!b) return a;
	if(!a) return b;
	int qa=0,qb=0;
	while(!(a&1)) a>>=1,++qa;
	while(!(b&1)) b>>=1,++qb;
	if(qb<qa) qa=qb;
	if(a<b) std::swap(a,b);
	return gcd_binary(a-b,b)<<qa;
}
inline long long gcd_euclid(long long a,long long b){
	return a?gcd_euclid(b%a,a):b;
}
long long gcd_b[5010][5010],gcd_e[5010][5010];
typedef unsigned long long cycles_t;
inline cycles_t cc() {
    cycles_t result;
    __asm__ __volatile__ ("rdtsc" : "=A" (result));
    return result;
}
int main(){
	long long a,b;
	int xi=0,xj=0;
	cycles_t f=cc();
	for(long long i=1000000000000001ll;i<=2000000000000000ll;i+=333333333333ll){
		++xi;
		xj=0;
		for(long long j=1000000000000003ll;j<=2000000000000000ll;j+=777777777777ll){
			++xj;
			gcd_b[xi][xj]=gcd_binary(i,j);
		}
	}
	cycles_t e=cc();
	cycles_t xa=e-f;
	xi=0,xj=0;
	f=cc();
	for(long long i=1000000000000001ll;i<=2000000000000000ll;i+=333333333333ll){
		++xi;
		xj=0;
		for(long long j=1000000000000003ll;j<=2000000000000000ll;j+=777777777777ll){
			++xj;
			gcd_e[xi][xj]=gcd_euclid(i,j);
		}
	}
	e=cc();
	cycles_t xb=e-f;
	for(int i=1;i<=xi;++i) for(int j=1;j<=xj;++j) if(gcd_b[i][j]!=gcd_e[i][j]){
		printf("WRONG POINT AT %d %d,break\n",i,j);
		break;
	}
	printf("%lld %lld %lf\n",xa,xb,(double)xa/(double)xb);
	return 0;
}