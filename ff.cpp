#include "IndexedMaxHeap.h"
#include <iostream>
using namespace std;

const int MAX_ID = 10e6;
const int MAX_REQ = 1e9;

void runFFCache() {
    int cache_size;
    int num_requests;
    cin >> cache_size;
    cin >> num_requests;

    vector<int> requests(num_requests, -1);
    for(int i=0; i<num_requests; i++) {
        cin >> requests[i];
    }

    // next occ of the same page id at pos i
    vector<int> next_occ(num_requests, MAX_REQ);

    // temp ds: last seen pos of this page id
    vector<int> last_seen(MAX_ID, MAX_REQ);
    for(int i=num_requests-1; i>=0; i--){
        next_occ[i] = last_seen[requests[i]];
        last_seen[requests[i]] = i;
    }

    IndexedMaxHeap maxHeap(MAX_ID);
    int page_faults = 0;
    // start processing requests;
    for(int i=0; i<num_requests; i++) {
        if(maxHeap.contains(requests[i])) {
            // cache hit
            maxHeap.update(requests[i], next_occ[i]);
        } else {
            // miss
            if (maxHeap.size() == cache_size) {
                maxHeap.pop_max();
            }
            maxHeap.push(requests[i], next_occ[i]);
            page_faults++;
        }
    }
    cout << page_faults << "\n";


}

int main() {
    int instances;
    cin >> instances;
    while(instances--) runFFCache();
    return 0; 
}