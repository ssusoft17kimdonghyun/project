// project sokoban
#include <stdio.h>
int main(void)
{
	char player_name[10];
	
	printf("Start....\ninput name : ");
	
	for (int i = 0; (player_name[i-1] != '\n') && (i < 10); i++)
	{
		player_name[i] = getchar();
	}

	printf("\nHello ");
	
	for (int i = 0; i < sizeof(player_name); i++)
	{
		putchar(player_name[i]);
	}
	
	printf("\n");
	
	return 0;
}
