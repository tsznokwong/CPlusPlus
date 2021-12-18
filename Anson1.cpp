#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;

struct node
{
	int value;
	node *samePile;
};

int mx = 0;

void patienceSort(int t,node *head[])
{
	int low = 0,hi = mx;
	
	while(low != hi)
	{
		int ave = (low + hi) / 2;
		
		if(head[ave]->value >= t)
			hi = ave;
		else
			low = ave+1;
	}
	
	if(head[hi]->value == 1999999999)
		mx++;
	
	node *tmp = new node;
	tmp->value = t;
	tmp->samePile = head[hi];
	head[hi] = tmp;
}

int main()
{
	char mode;
	int N;
	stack<int> binary;
	
	scanf("%c",&mode);
	scanf("%d",&N);
	
	int size = (mode == 'A') ? N : 2*N;
	node *head[size];
	
	
	for(int i = 0;i < size;i++)
	{
		node *tmp = new node;
		tmp->value = 1999999999;
		tmp->samePile = NULL;
		head[i] = tmp;
	}
	
	if(mode == 'A')
	{
		for(int i = 0;i < N;i++)
		{
			int t;
			scanf("%d",&t);
			
			patienceSort(t,head);
		}
		
		for(int i = mx-1;i >= 0;i--)
		{
			int q = head[i]->value;
			
			for(int j = 0;j < 20;j++)
			{
				binary.push(q%2);
				q /= 2;
			}
		}
		
		printf("%d\n",binary.size());
		while(!binary.empty())
		{
			printf("%d",binary.top());
			binary.pop();
		}
		printf("\n");
	}
	else
	{
		int arr[N],l;
		
		for(int i = 0;i < N;i++)
			scanf("%d",&arr[i]);
		
		scanf("%d",&l);
		
		char str[l+1];
		mx = l/20;
		scanf("%s",str);
		
		for(int i = 0;i < l/20;i++)
		{
			int k = 0;
			
			for(int j = 0;j < 20;j++)
				k = k*2 + (str[i*20+j] - '0');
			
			node *tmp = new node;
			tmp->value = k;
			tmp->samePile = head[i];
			head[i] = tmp;
		}
		
		for(int i = 0;i < N;i++)
			patienceSort(arr[i],head);
		
		printf("%d\n",mx);
	}
	
	return 0;
}
