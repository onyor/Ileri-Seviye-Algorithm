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
		/* Daha �nceden oldu�u gibi iki tane istek aras�ndaki s�ralamay� belirlemek i�in k���k bir operat�r kodluyoruz! */
		bool operator<(const Istek& rhs) {
    		/*�u anki objenin deadline' � rhs.deadline' �n dan k���kse, bu bundan k���kt�r �eklinde bir bilgi d�n�yor. 
			Sort fonksiyonun bu bilgiyi kullanarak b�t�n bu istek vekt�r�n� s�ralam�� oluyor.*/
			return deadline < rhs.deadline;
		}		
};
/* 2 farkl� de�eri pair class' �n� kullanarak d�n�yoruz.*/
pair<vector<double>, vector<double> >
/* C++' �n sort fonksiyonunu kullanabiliriz! */
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
	
	/* �stekleri ekliyoruz! */
	I.push_back(Istek(0,4,10));
	I.push_back(Istek(1,4,10));
	I.push_back(Istek(2,9,9));
	
	/* �lk array'imiz start time ikinci Array'imiz finish time */
	pair<vector<double>,vector<double>> res= DeadlineliZamanlama(I);
	
	
	
	vector<double>& s=res.first;
	vector<double>& f=res.second;
	
	for(int id=0;id<s.size();id++){
		cout<<s[id]<< " " <<f[id] << endl;
	}
	return 0;
}
