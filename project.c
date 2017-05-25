// project sokoban
#include <stdio.h>
int main(void)
{
	// 맵파일을 읽고 map_data에 저장
	FILE *read_map;
	char map_data[30][30];
	int n, x, y;
	read_map = fopen("map.txt", "r");
	for (n = 0; n < 5; n++)
		for (y = 0; y < 30; y++)
			for (x = 0; (map[n][x-1][y] != '\n') && (x < 30); x++)
			{
				fscanf(read_map, "%c", &map_data[n][x][y]);
				printf("%c", map_data[n][x][y]);
			}
	fclose(read_map);

	// 사용자 이름을 player_name에 입력받음
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
