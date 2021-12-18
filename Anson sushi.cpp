#include <cstdio>

struct sushi
{
	int smallest,size;
	sushi *next;
};

int main()
{
	int N,K,Q;
	bool full = true;
	
	scanf("%d%d%d",&N,&K,&Q);
	
	sushi *now = new sushi;
	
	now->next = now;
	now->smallest = 1;
	now->size = N;
	
	for(int i = 1;i <= Q;i++)
	{		
		char C;
		
		scanf("%c",&C);
		
		if(C == 'T')
		{
			full = false;
			
			if(now->smallest == -1)
				printf("-1\n");
			else
			{
				printf("%d\n",(now->smallest+K-1));
				
				sushi *tmp = new sushi;
				
				if(K == now->size)
					delete tmp;
				else
				{
					tmp->size = now->size - K;
					tmp->smallest = now->smallest+K;
					tmp->next = now->next;
					now->next = tmp;
				}
				
				if(K != 1)
				{
					tmp = new sushi;
					
					now->size = K-1;
					tmp->next = now->next;
					now->next = tmp;
					now = now->next;
				}
			}
			now->smallest = -1;
			now->size = 1;
			K = 1;
			now = now->next;
		}
		else if(C == 'B')
		{
			if(now->smallest == -1)
			{
				now = now->next;
				K = 1;
			}
			else if(!full)
			{
				sushi *tmp = new sushi;
				
				if(K != 1)
				{
					tmp->size = now->size-K+1;
					tmp->smallest = now->smallest+K-1;
					tmp->next = now->next;
					now->next = tmp;
					now->size = K-1;
					now = now->next;
					tmp = new sushi;
				}
				
				tmp->size = now->size;
				tmp->smallest = now->smallest;
				tmp->next = now->next;
				now->next = tmp;
				now->smallest = -1;
				now->size = 1;
				now = now->next;
				K = 1;
				
				sushi *findSpace = now,*replace;
				
				while(findSpace->next->smallest != -1)
					findSpace = findSpace->next;
				
				replace = findSpace->next;
				findSpace->next = replace->next;
				delete replace;
			}
		}
		else
		{
			K++;
			if(K > now->size)
			{
				K = 1;
				now = now->next;
			}
		}
	}
	
	return 0;
}
