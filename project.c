/* project 코드파일
   2017.5.25
   20170263 김동현 */
#include <stdio.h>
#include <termio.h>
char getch();
int main(void)
{
	// map 파일 읽어오고 map_file에 저장
	FILE *read_map;
	char map_file[1201], map[5][30][30] = {0};
	int n, x, y;
	int num_box, num_slot, map_error = 0;
	read_map = fopen("map.txt", "r");
	for (int i = 0; i < 1201; i++)
	{
		fscanf(read_map, "%c", &map_file[i]);
	}
	fclose(read_map);

	n = 0, x = 0, y = 0; // map1 을 map[0][x][y]에 저장
	for (int i = 5; i < 268; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		//printf("%c", map[n][x][y]); // 입력상태 확인, 확인 후 삭제
		x++;
	}

	n = 1, x = 0, y = 0; // map2 을 map[1][x][y]에 저장
	for (int i = 274; i < 433; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		//printf("%c", map[n][x][y]); // 입력상태 확인, 확인 후 삭제
		x++;
	}

	n = 2, x = 0, y = 0; // map3 을 map[2][x][y]에 저장
	for (int i = 439; i < 628; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		//printf("%c", map[n][x][y]); // 입력상태 확인, 확인 후 삭제
		x++;
	}

	n = 3, x = 0, y = 0; // map4 을 map[3][x][y]에 저장
	for (int i = 634; i < 945; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		//printf("%c", map[n][x][y]); // 입력상태 확인, 확인 후 삭제
		x++;
	}

	n = 4, x = 0, y = 0; // map5 을 map[4][x][y]에 저장
	for (int i = 951; i < 1197; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		//printf("%c", map[n][x][y]); // 입력상태 확인, 확인 후 삭제
		x++;
	}

	/*for (n = 0; n < 4; n++) // map 츨력 확인, 확인 후 삭제
	{
		printf("\nmap%d\n", n + 1);
		for (y = 0; y < 30; y++)
			for (x = 0; x< 30; x++)
			{
				printf("%c", map[n][x][y]);
			}
	}
	printf("\n\n");*/

	// map 파일 오류 검사
	for (n = 0; n < 5; n++)
	{
		num_box = 0;
		num_slot = 0;
		for (y = 0; y < 30; y++)
			for (x = 0; x < 30; x++)
			{
				if (map[n][x][y] == '$')
					num_box++;
				else if (map[n][x][y] == 'O')
					num_slot++;
			}
		if (num_box != num_slot)
		{
			printf("오류 : map%d 파일에 문제가 있습니다.\n", n+1);
			map_error++;
		}
	}
	if (map_error > 0)
		return 0;

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
char getch(void)
{
	char ch;

	struct termios buf;
	struct termios save;

	tcgetattr(0, &save);
	buf = save;

	buf.c_lflag&=~(ICANON|ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;

	tcsetattr(0, TCSAFLUSH, &save);

	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);

	return ch;
}
