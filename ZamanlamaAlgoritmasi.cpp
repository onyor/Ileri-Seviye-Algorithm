#include<vector>
#include<iostream>
#include<algorithm>

/*
* Karmasiklik: Teta(nlogn)
*/

using namespace std;

class Istek{
	public:
		double uzunluk;
		double deadline;
		int id;
		/* Constructor*/
		Istek(int i, double u, double d): id(i), uzunluk(u)
                              , deadline(d) {
                              	
		}		
		/* Daha önceden olduðu gibi iki tane istek arasýndaki sýralamayý belirlemek için küçük bir operatör kodluyoruz! */
		bool operator<(const Istek& rhs) {
    		/*Þu anki objenin deadline' ý rhs.deadline' ýn dan küçükse, bu bundan küçüktür þeklinde bir bilgi dönüyor. 
			Sort fonksiyonun bu bilgiyi kullanarak bütün bu istek vektörünü sýralamýþ oluyor.*/
			return deadline < rhs.deadline;
		}		
};
/* 2 farklý deðeri pair class' ýný kullanarak dönüyoruz.*/
pair<vector<double>, vector<double> >
/* C++' ýn sort fonksiyonunu kullanabiliriz! */
	DeadlineliZamanlama(vector<Istek> I) {
	//teta(nlogn)
	sort(I.begin(), I.end());
	
	// teta(n)
	vector<double> s(I.size());
	vector<double> f(I.size());

	double z = 0;

	// teta(n)
	for(int i=0; i<I.size(); i++) {
		int id = I[i].id;
    	double uzunluk = I[i].uzunluk;
    	double deadline = I[i].deadline;

    	s[id] = z;
    	f[id] = z + uzunluk;
   		z = z + uzunluk;
	}
  	return make_pair(s,f);
}

int main(){
	vector<Istek> I;
	
	/* Ýstekleri ekliyoruz! */
	I.push_back(Istek(0,4,10));
	I.push_back(Istek(1,4,10));
	I.push_back(Istek(2,9,9));
	
	/* Ýlk array'imiz start time ikinci Array'imiz finish time */
	pair<vector<double>,vector<double>> res= DeadlineliZamanlama(I);
	
	
	
	vector<double>& s=res.first;
	vector<double>& f=res.second;
	
	for(int id=0;id<s.size();id++){
		cout<<s[id]<< " " <<f[id] << endl;
	}
	return 0;
}
