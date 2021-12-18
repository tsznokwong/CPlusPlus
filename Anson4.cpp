#include <bits/stdc++.h>

using namespace std;

vector<int> heap;
vector< pair<int, int> > edge[100001];
vector< pair<long long int, int> > cost; //	< diamond, time >
int nodePos[100001];

int compare(pair<long long int, int>& pair1, pair<long long int, int>& pair2) {
	if(pair1.first > pair2.first || (pair1.first == pair2.first && pair1.second > pair2.second))
		return 1;
	if(pair1.first == pair2.first && pair1.second == pair2.second)
		return 0;
	return -1;
}

void traverseDown(int loc) {
	if(2*loc < heap.size()) {
		int swapPos = -1;
		if(compare(cost[heap[2*loc]], cost[heap[loc]]) <= 0) {
			swapPos = 2*loc;
			if(2*loc+1 < heap.size() && compare(cost[heap[2*loc+1]], cost[heap[2*loc]]) <= 0)
				swapPos = 2*loc+1;
		}
		if(swapPos != -1) {
			swap(nodePos[heap[swapPos]], nodePos[heap[loc]]);
			swap(heap[swapPos], heap[loc]);
			traverseDown(swapPos);
		}
	}
}

void traverseUp(int loc) {
	if(loc > 1 && compare(cost[heap[loc]], cost[heap[loc/2]]) <= 0) {
		swap(nodePos[heap[loc]], nodePos[heap[loc/2]]);
		swap(heap[loc], heap[loc/2]);
		traverseUp(loc/2);
	}
}

void dijkstra(int N, int L) {
	bool visited[N+1];
	for(int i = 0; i < N+1; i++) {
		visited[i] = false;
		nodePos[i] = i;
		cost.push_back({LLONG_MAX, INT_MAX});
	}
	cost[1] = {1, 0};
	for(int i = 0; i < N+1; i++) {
		heap.push_back(i);
		traverseUp(i);
	}
	while(heap.size() > 1) {
		int node = heap[1];
		visited[node] = true;
		swap(nodePos[heap[heap.size()-1]], nodePos[heap[1]]);
		swap(heap[heap.size()-1], heap[1]);
		heap.pop_back();
		traverseDown(1);
		int numOfEdges = edge[node].size();
		for(int i = 0; i < numOfEdges; i++) {
			if(!visited[edge[node][i].first]) {
				pair<long long int, int> newCost;
				newCost.first = cost[node].first;
				newCost.second = cost[node].second + edge[node][i].second;
				if(newCost.second > L) {
					newCost.first++;
					newCost.second = edge[node][i].second;
				}
				if(compare(newCost, cost[edge[node][i].first]) <= 0) {
					cost[edge[node][i].first] = newCost;
					traverseUp(nodePos[edge[node][i].first]);
				}
			}
		}
	}
}

int main() {
	int N, M, L;
	scanf("%d%d%d", &N, &M, &L);
	for(int i = 0; i < M; i++) {
		int X, Y, Z;
		scanf("%d%d%d", &X, &Y, &Z);
		edge[X].push_back({Y, Z});
		edge[Y].push_back({X, Z});
	}
	dijkstra(N, L);
	for(int i = 2; i <= N; i++)
		printf("%lld\n", cost[i].first);
	return 0;
}

