#include "PriorityQueue.h"
#include <iostream>

using namespace std;
// Karmasiklik: O(nlogn)
// Karmasiklik: teta(nlogn)
int main() {
  PriorityQueue Q;
  int N;
  cin >> N;

  // O(nlogn)
  for(int i = 0; i < N; i++) {
    int a;
    cin >> a;

    Q.add(a, a);
  }

  // O(nlogn)
  while(!Q.isEmpty()){
    PriorityQueue::Item item = Q.getMin();
    cout << item.obj << " ";
    Q.deleteMin();
  }

  cout << endl;


  return 0;
}
