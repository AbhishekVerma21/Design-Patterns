#include<iostream>
#include<string>

template<typename T, typename ref> std::string Print(T a, ref b){
	std::cout<<"a : "<<a<<" size of : "<<sizeof(a)<<std::endl;
	std::cout<<"b : "<<b<<" size of : "<<sizeof(b)<<std::endl;
	return "abc";
}


int main(){
	std::cout<<"in main : "<<Print(4, 3.2f)<<std::endl;
	std::cout<<"in main : "<<Print(3.2f, 5)<<std::endl;
	std::cout<<"in main : "<<Print("Neelesh Verma, Abhishek Verma : Family", 555.555f)<<std::endl;
	getchar();
	return 0;
}