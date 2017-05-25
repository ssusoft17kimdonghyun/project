/* project 코드파일
   2017.5.25
   20170263 김동현 */
#include <stdio.h>
int main(void)
{
	// map 파일 읽어오고 map_file에 저장
	FILE *read_map;
	char map_file[1201], map[5][30][30] = {0};
	int n, x, y;
	read_map = fopen("map.txt", "r");
	for (int i = 0; i < 1201; i++)
	{
		fscanf(read_map, "%c", &map_file[i]);
		//printf("%c", map_file[i]); // 입력확인
	}
	fclose(read_map);

	n = 0, x = 0, y = 0; // map1 을 map[0][x][y]에 저장
	printf("\n=====map1input=====\n");
	for (int i = 5; i < 268; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		printf("%c", map[n][x][y]); // 입력상태 확인, 확인 후 삭제
		x++;
	}
	printf("\n===%c===\n", map[0][12][8]); // map1 플레이어 위치

	n = 1, x = 0, y = 0; // map2 을 map[1][x][y]에 저장
	printf("\n=====map2input=====\n");
	for (int i = 274; i < 433; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		printf("%c", map[n][x][y]); // 입력상태 확인, 확인 후 삭제
		x++;
	}
	printf("\n===%c===\n", map[1][7][4]); // map2 플레이어 위치

	n = 2, x = 0, y = 0; // map3 을 map[2][x][y]에 저장
	printf("\n=====map3input=====\n");
	for (int i = 439; i < 628; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		printf("%c", map[n][x][y]); // 입력상태 확인, 확인 후 삭제
		x++;
	}
	printf("\n===%c===\n", map[2][14][1]); // map3 플레이어 위치

	n = 3, x = 0, y = 0; // map4 을 map[3][x][y]에 저장
	printf("\n=====map4input=====\n");
	for (int i = 634; i < 945; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		printf("%c", map[n][x][y]); // 입력상태 확인, 확인 후 삭제
		x++;
	}
	printf("\n===%c===\n", map[3][8][10]); // map4 플레이어 위치

	n = 4, x = 0, y = 0; // map5 을 map[4][x][y]에 저장
	printf("\n=====map5input=====\n");
	for (int i = 951; i < 1197; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		printf("%c", map[n][x][y]);
		x++;
	}
	printf("\n===%c===\n", map[4][14][7]); // map5 플레이어 위치

	for (n = 0; n < 5; n++) // map 츨력 확인, 확인 후 삭제
	{
		printf("\nmap%d\n", n + 1);
		for (y = 0; y < 30; y++)
			for (x = 0; x< 30; x++)
			{
				printf("%c", map[n][x][y]);
			}
	}
	printf("\n\n");

	// 사용자 이름 입력
	char player_name[10];

	printf("Start....\ninput name : ");

	for (int i = 0; (i < 10) && (player_name[i-1] != '\n'); i++)
		player_name[i] = getchar();

	printf("\nHello ");

	for (int i = 0; i < sizeof(player_name); i++)
		putchar(player_name[i]);

	printf("\n");

	return 0;
}
