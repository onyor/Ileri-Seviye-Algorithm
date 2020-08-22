#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;


class PriorityQueue {
public:
  class Item {
  public:
    int obj;
    int priority;
    Item(int o, int p): obj(o), priority(p) {

    }

    bool operator>(const Item& rhs) {
      return priority > rhs.priority;
    }

    bool operator<(const Item& rhs) {
      return priority < rhs.priority;
    }
  };

  /*
  * obj objesini priority onceligiyle oncelik kuyruguna ekle.
  *
  * Karmasiklik: teta(logn)
  */
  void add(int obj, int priority) {
    // teta(1)
    assert(!objExists(obj));

    // teta(1)
    heap.push_back(Item(obj, priority));

    // teta(1)
    hash_table[obj] = heap.size() - 1;

    // teta(logn)
    bubbleUp(heap.size() - 1);
  }

  /*
  * Oncelik kuyrugu bossa TRUE, degilse FALSE don.
  *
  * Karmasiklik: teta(1)
  */
  bool isEmpty() const {
    return heap.size() == 0;
  }

  /*
  * Oncelik degeri minimum olan objeyi ve oncelik degerini don.
  *
  * Karmasiklik: teta(1)
  */
  Item getMin() const {
    // teta(1)
    assert(!isEmpty());
    //teta(1)
    return heap[0];
  }

  /*
  * Minimum oncelikli objeyi oncelik kuyrugundan sil.
  *
  * Karmasiklik: teta(logn)
  */
  void deleteMin() {
    // teta(1)
    assert(!isEmpty());

    // teta(1)
    hash_table.erase(heap[0].obj);

    // teta(1)
    heap[0] = heap[heap.size() - 1];

    // teta(1)
    hash_table[heap[0].obj] = 0;

    // teta(1)
    heap.pop_back();

    // teta(logn)
    bubbleDown(0);
  }

  /*
  * obj objesinin onceligini new_priority olarak degistir
  *
  * Karmasliklik: teta(logn)
  */
  void changePriority(int obj, int new_priority) {
    // teta(1)
    assert(objExists(obj));

    // teta(1)
    unsigned int idx = hash_table[obj];

    // teta(logn)lik bir blok
    if(heap[idx].priority > new_priority) {
      heap[idx].priority = new_priority;
      // teta(logn)
      bubbleUp(idx);
    } else if (heap[idx].priority < new_priority){
      heap[idx].priority = new_priority;
      // teta(logn)
      bubbleDown(idx);
    }
  }

  /*
  * obj objesinin onceligini don.
  *
  * Karmasiklik: teta(1)
  */
  int getPriority(int obj) const {
    // teta(1)
    assert(objExists(obj));

    // teta(1)
    unsigned int idx = hash_table.at(obj);

    // teta(1)
    return heap[idx].priority;
  }

  /*
  * obj objesini oncelik kuyrugunda varsa TRUE, yoksa FALSE don.
  *
  * Karmasiklik: teta(1)
  */
  bool objExists(int obj) const {
    return hash_table.find(obj) != hash_table.end();
  }
private:
  /*
  * idx indexinden baslayarak yukari dogru bubbleUp yap.
  *
  * Karmasiklik: teta(logn)
  */
  void bubbleUp(unsigned int idx) {
    unsigned int parent_idx = (idx - 1) / 2;
    while(idx != 0 && heap[parent_idx] > heap[idx]) {
      Item parent = heap[parent_idx];
      Item me = heap[idx];

      heap[parent_idx] = me;
      heap[idx] = parent;

      hash_table[me.obj] = parent_idx;
      hash_table[parent.obj] = idx;

      idx = parent_idx;
      parent_idx = (idx - 1) / 2;
    }
  }

  /*
  * idx indexinden baslayarak asagi dogru bubbleDown yap.
  *
  * Karmasiklik: teta(logn)
  */
  void bubbleDown(unsigned int idx) {
    unsigned int lchild_idx = 2 * idx + 1;
    unsigned int rchild_idx = 2 * idx + 2;

    while((lchild_idx < heap.size() && heap[lchild_idx] < heap[idx]) ||
          (rchild_idx < heap.size() && heap[rchild_idx] < heap[idx])) {

      unsigned int min_child_idx = lchild_idx;

      if(rchild_idx < heap.size()) {
        if(heap[rchild_idx] < heap[lchild_idx]) {
          min_child_idx = rchild_idx;
        }
      }

      // min_child_idx degiskeninde minimum oncelikli cocugumuz indexi
      // vardir.

      Item me = heap[idx];
      Item child = heap[min_child_idx];

      heap[idx] = child;
      heap[min_child_idx] = me;

      hash_table[me.obj] = min_child_idx;
      hash_table[child.obj] = idx;

      idx = min_child_idx;
      lchild_idx = 2 * idx + 1;
      rchild_idx = 2 * idx + 2;
    }
  }

  vector<Item> heap;
  unordered_map<int, unsigned int> hash_table;
};

#endif
