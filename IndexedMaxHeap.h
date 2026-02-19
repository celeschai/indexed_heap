#include <vector>
#include <algorithm>

#ifndef INDEXED_MAX_HEAP
#define INDEXED_MAX_HEAP

using namespace std;

class IndexedMaxHeap {
    private:        
        // maxHeap[pos] = {id, priority}
        vector<pair<int, int>> maxHeap;

        int MAX_ID;

        // if the max id is known and small, use vector
        // index[id] = pos
        vector<int> index;

        void swap_nodes(int i, int j) {
            swap(maxHeap[i], maxHeap[j]);
            index[maxHeap[i].first] = i;
            index[maxHeap[j].first] = j;
        }

        void sift_up(int curr_pos) {
            while(0 < curr_pos && maxHeap[curr_pos].second > maxHeap[(curr_pos - 1) / 2].second) {
                swap_nodes(curr_pos, (curr_pos - 1) / 2);
                curr_pos = (curr_pos - 1) / 2;
            }
        }

        void sift_down(int curr_pos) {
            int left = curr_pos * 2 + 1;
            int right = curr_pos * 2 + 2;
            int next_pos = curr_pos;

            if(left < maxHeap.size() && maxHeap[next_pos].second < maxHeap[left].second) {
                next_pos = left;
            } 
            if(right < maxHeap.size() && maxHeap[next_pos].second < maxHeap[right].second) {
                next_pos = right; // finds the max
            } 
            if(next_pos == curr_pos) return;

            swap_nodes(next_pos, curr_pos);
            sift_down(next_pos);
        }

    public:
        IndexedMaxHeap(int max_id): MAX_ID(max_id), index(max_id, -1) {};

        void push(int new_id, int new_priority) {
            maxHeap.push_back({new_id, new_priority});
            index[new_id] = maxHeap.size() - 1;
            sift_up(maxHeap.size() - 1);
        }

        int pop_max() {
            int root = maxHeap[0].first;
            swap_nodes(0, maxHeap.size() - 1);
            maxHeap.pop_back();
            index[root] = -1;
            if(!maxHeap.empty()) sift_down(0);
            return root;
        }

        void update(int id, int new_priority) {
            int pos = index[id];
            int curr_priority = maxHeap[pos].second;
            maxHeap[pos].second = new_priority;
            if(curr_priority == new_priority) return;
            else if(curr_priority < new_priority) sift_up(pos);
            else sift_down(pos);
        }

        bool contains(int id) {
            return index[id] >= 0;
        }

        int size() {
            return maxHeap.size();
        }

};

#endif