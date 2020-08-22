#include <vector>
#include <iostream>
#include <algorithm>
#include <iostream>
using namespace std;

/*
* Karmasiklik: Teta(nlogn)
*/


class Istek{
	public:
		double baslangic;
		double bitis;
		Istek(double s,double f):baslangic(s),bitis(f) {
			
		}		
		
		bool operator<(const Istek& rhs){
			return bitis<rhs.bitis;
		}
};

vector<Istek> AralikZamanlama(vector<Istek> I){
	sort(I.begin(),I.end());
	
	double sbz=-1;
	vector<Istek> A;
	for(auto& i: I){
		if(i.baslangic <sbz){
			continue;
		}
		A.push_back(i);
		sbz=i.bitis;
	}
	return A;
}

int main(){
	vector<Istek> I;
	/*I' ya eleman ekle */
	I.push_back(Istek(1,4));
	I.push_back(Istek(7,10));
	I.push_back(Istek(5,8));
	I.push_back(Istek(9,12));
	I.push_back(Istek(3,6));
	I.push_back(Istek(2,11));
	vector<Istek> A=AralikZamanlama(I);
	for(auto& i: A){
		cout <<i.baslangic << " " <<i.bitis<< endl;
	}
	return 0;
}
