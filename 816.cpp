#include <cstdint>
#include<iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

int main(int argc,char** argv){
	uint32_t s0=290797,s1;
	uint32_t M=50515093;
	std::vector<std::pair<uint32_t,uint32_t>> A[472][472];
	uint32_t len=M/472+1;
	uint64_t size=2*(uint64_t)len*len;
	uint64_t distance=INT64_MAX;
	for(int i=0;i<2000000;i++){
		s1=((uint64_t)s0*s0)%M;
		auto a0=s0/len,a1=s1/len;
		A[a0][a1].push_back(std::make_pair(s0,s1));
		s0=((uint64_t)s1*s1)%M;
	}
	for(int i=0;i<472;i++){
		for(int j=0;j<472;j++){
			for(auto a:A[i][j]){
				for(auto b:A[i][j]){
					if(a!=b){
						int32_t i1=a.first-b.first,i2=a.second-b.second;
						distance=std::min((uint64_t)((int64_t)i1*i1+(int64_t)i2*i2),distance);
					}
				}
			}
		}
	}
	auto lambda=[&](int i,int j,int k,int l){
		for(auto a:A[i][j]){
			for(auto b:A[k][l]){
				int32_t i1=a.first-b.first,i2=a.second-b.second;
				distance=std::min((uint64_t)((int64_t)i1*i1+(int64_t)i2*i2),distance);
			}
		}
	};
	for(int i=0;i<472;i++){
		for(int j=0;j<472;j++){
			uint16_t k=0;
			do{
				k++;
				int i1=i+k;
				if(i1<472){
					lambda(i,j,i1,j);
				}
				int j1=j+k;
				if(j1<472){
					lambda(i,j,i,j1);
				}
				if(i1<472 && j1<472){
					lambda(i,j,i1,j1);
				}
			}
			while(distance>k*k*size);
		}
	}
	std::cout<<std::setprecision(9)<<std::sqrt((double)distance)<<'\n';
}
