#include <iostream>
#include <list>
#include <vector>
#include <numeric>

uint32_t xormul(uint32_t m,uint32_t n){
	uint32_t res = 0;
    uint32_t i = 1;
	while(i <=n ){
            res ^= m * (n & i);
            i *= 2; 
	}
	return res;
}
void sieve(std::vector<bool> &prime, uint32_t num, uint32_t val){
    uint32_t i = 0;
    uint32_t j, x;
    uint32_t c = 0;
    i = 2;
    while(i < num - 3){
        if (!prime[i]){
            j =2;
            c++;
			if(c == val){
				std::cout<<i<<' ';
            }
            while (true){
                x = xormul(i,j);
                if (x >= num) break;
                prime[x] = true;
                j += 1;
            }
        }
        i += 1;
    }
}
int main(int argc,char** argv){
    uint32_t num = 1<<(atoi(argv[1]));
    std::vector<bool> prime(num, 0);
    sieve(prime, num,atoi(argv[2]));
}
