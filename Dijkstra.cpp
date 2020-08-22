#include <iostream>
#include <vector>
#include "PriorityQueue.h"
#include <algorithm>

using namespace std;

class Neighbour {
	public:
  		int komsu;
 	    int agirlik;
  		Neighbour(int k, int a): komsu(k), agirlik(a) {
	}
};

// tata(N)
vector<int> extract_path(const vector<int>& p, int h) {
	vector<int> result;
	result.push_back(h);
	while(p[h] != -1) {
    	result.push_back(p[h]);
    	h = p[h];
  	}
	reverse(result.begin(), result.end());
	return result;
}

/*
* Graph'ta k nodeundan h nodeuna olan en kisa yolu bul
*
* int => kden hye en kisa yolun uzunlugu
* vector<int> => nodelar
*/
pair<int, vector<int> > Dijkstra(
	const vector<vector<Neighbour> >& Graph, int k, int h, bool& exists) {
	int N = Graph.size(); //graphtaki node sayisi
	//teta(N)
  	vector<bool> A(N, false);
 	vector<int> d(N);
 	vector<int> p(N);
  	PriorityQueue Q;

  	// teta(1)
 	Q.add(k, 0);
 	p[k] = -1;

  	// N kere donen bir dongu
  	// O(NlogN)
  	while(!Q.isEmpty()) {
  		// O(logN)
    	auto item = Q.getMin();
    	Q.deleteMin();
    	int n = item.obj;
    	int u = item.priority;
    	d[n] = u;
    	A[n] = true;
    	// Toplamda M kere donuyor
    	// O(MlogN) < tomplamda
    	for(auto& neigh: Graph[n]) {
     		int x = neigh.komsu;
     		int cnx = neigh.agirlik;
     		if(A[x] == true) {
        		continue;
    		}
			// O(logn)	
    		if(Q.objExists(x) == false) {
    			// x objesini Q kuyruguna ekle
       			// x objesine n nodeu uzerinden gelmeliyiz.
       	 		Q.add(x, d[n] + cnx);
    			p[x] = n;
    		} else {
        		if(Q.getPriority(x) > d[n] + cnx) {
          			Q.changePriority(x, d[n] + cnx);
          			p[x] = n;
        		}
    		}
    	}
   }
   // N tane node' umuz varsa max N^2 tane edgemiz olabilir.
   // en kotu durumda M = N^2
   
   // O(MlogN + NlogN)
   // O(N^2logN + NlogN)
   // O(MlogN)
   if(A[h]==false){
   		// k' den h' ye bir yol yok ise
   		exists=false;
		return make_pair(-1,vector<int>());
   }
   
   exists=true;
   return make_pair(d[h], extract_path(p, h));
}

int main() {
	int n; // node sayisi
  	int m; // edge sayisi

 	cin >> n >> m;

    vector<vector<Neighbour> > Graph(n);

  	for(int i = 0; i < m; i++) {
    	int x, y, w;
    	cin >> x >> y >> w;
    	Graph[x].push_back(Neighbour(y, w));
   }

  	int k, h;
  	cin >> k >> h;

	bool exists;
  	pair<int, vector<int> > res = Dijkstra(Graph, k, h, exists);

	if(exists) {
		cout << res.first << endl;
  	for(auto& node: res.second) {
    	cout << node << " ";
 	}
  	cout << endl;
	} else {
		cout<<"k' den h' ye gitmek mumkun degildir!";
	}

  	return 0;
}
