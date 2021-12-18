#include <cstdio>
#include <cstring>

int main()
{
	int N;
	
	scanf("%d\n",&N);
	
	char original[N][101],changed[101];
	int menu[N];
	
	for(int i = 0;i < N;i++)
	{
		gets(original[i]);
		
		int ol = strlen(original[i]);
		
		for(int j = 0;j < ol;j++)
			if(original[i][j] >= 'A' && original[i][j] <= 'Z')
				original[i][j] = original[i][j]-'A'+'a';
	}
	
	for(int i = 0;i < N;i++)
	{
		gets(changed);
		
		int cl = strlen(changed);
		bool subString = false;
		
		for(int j = 0;j < cl;j++)
			if(changed[j] >= 'A' && changed[j] <= 'Z')
				changed[j] = changed[j]-'A'+'a';
		
		for(int j = 0;j < N;j++)
		{			
			int oldPtr = 0,newPtr = 0,ol = strlen(original[j]);
			bool space = true;
			
			for(int k = 0;k < cl;k++)
			{
				if(changed[k] == ' ')
				{
					space = true;
					oldPtr = newPtr;
				}
				else
				{
					if(changed[k] == original[j][newPtr] && space)
					{
						newPtr++;
						
						if(newPtr == ol - 1)
						{
							menu[i] = j+1;
							goto kill;
						}
						else if(original[j][newPtr] == ' ')
							newPtr++;
					}
					else
					{
						space = false;
						newPtr = oldPtr;
					}
				}
			}
			kill:;
		}
	}
	
	for(int i = 0;i < N;i++)
		printf("%d\n",menu[i]);
	
	return 0;
}
