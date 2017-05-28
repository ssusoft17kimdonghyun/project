/* project 코드파일
   2017.5.25
   20170263 김동현 */
#include <stdio.h>
#include <termio.h>
char map[5][30][30];
int player_x, player_y;
int getch();
void movement(int, int);
int main(void)
{
	// map 파일 읽어오고 map_file에 저장
	FILE *read_map;
	char map_file[1500];
	int n = 0, x = 0, y = 0, i, tmp = 0;
	int p = 0, m = 0, e = 0;
	int num_p[5], num_m[5], num_e;
	int input_ch;
	int num_box, num_slot, map_error = 0;

	if ((read_map = fopen("map.txt", "r")) == NULL)
		printf("오류 : map.txt 파일이 비었습니다.\n");
	//read_map = fopen("map.txt", "r");
	for (int i = 0; map_file[i-1] != 'd'; i++)
	{
		fscanf(read_map, "%c", &map_file[i]);
		//printf("%c", map_file[i]);
	}
	fclose(read_map);
	//printf("\n");

	for ( i = 0; i < sizeof(map_file); i++)
	{
		if (map_file[i] == 'p')
		{
			num_p[p] = i;
			//printf("p : %d %d\n", num_p[p], p);
			p++;
		}
		else if (map_file[i] == 'm')
		{
			num_m[m] = i;
			//printf("m : %d %d\n", num_m[m], m);
			m++;
		}
		else if (map_file[i] == 'e')
		{
			num_e = i;
			//printf("e : %d\n", num_e);
		}
	}

	n = 0, x = 0, y = 0; // map1 을 map[0][x][y]에 저장
	for (int i = (num_p[0] + 3); i < num_m[1]; i++)
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
	printf("\n===%c===\n", map[0][12][8]); // 플레이어 위치 확인

	n = 1, x = 0, y = 0; // map2 을 map[1][x][y]에 저장
	for (int i = (num_p[1] + 3); i < num_m[2]; i++)
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
	printf("\n===%c===\n", map[1][7][4]); // 플레이어 위치 확인

	n = 2, x = 0, y = 0; // map3 을 map[2][x][y]에 저장
	for (int i = (num_p[2] + 3); i < num_m[3]; i++)
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
	printf("\n===%c===\n", map[2][14][1]); // 플레이어 위치 확인

	n = 3, x = 0, y = 0; // map4 을 map[3][x][y]에 저장
	for (int i = (num_p[3] + 3); i < num_m[4]; i++)
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
	printf("\n===%c===\n", map[3][8][10]); // 플레이어 위치 확인


	n = 4, x = 0, y = 0; // map5 을 map[4][x][y]에 저장
	for (int i = (num_p[4] + 3); i < num_e; i++)
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
	printf("\n===%c===\n", map[4][14][7]); // 플레이어 위치 확인

	/*for (n = 0; n < 4; n++) // map 츨력 확인, 확인 후 삭제
	{
		printf("\nmap%d\n", n + 1);
		for (y = 0; y < 30; y++)
			for (x = 0; x< 30; x++)
			{
				printf("%c", map[n][x][y]);
			}
	}
	printf("\n\n");
*/
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
		if (num_box == num_slot)
			continue;
		else if (num_box != num_slot)
		{
			printf("오류 : map%d 파일에 문제가 있습니다.\n", n+1);
			map_error = 1;
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

	// map1 시작 미완성
	/*n = 0;
	num_slot = 1;
	player_x = 12;
	player_y = 8;
	printf("map%d start\n\n", n+1);
	while (num_slot > 0)
	{
		for (y = 0; y < 30; y++)
			for (x = 0; x < 30; x++)
				printf("%c", map[n][x][y]);
		printf("\n(Command) : ");
		input_ch = getch();
		if (((input_ch == 104) || (input_ch == 106)) || ((input_ch == 107) || (input_ch == 108)))
			movement(n, input_ch);
		//else if //명령어 입력시 사용
		num_slot = 0;
		for (y = 6; y < 9; y++)
			for (x = 19; x < 21; x++)
			{
				if ((map[n][x][y] != 64) || (map[n][x][y] != 36))
					map[n][x][y] = 79;
				if (map[n][x][y] == 79)
					num_slot++;
			}
	}
	printf("\nmap%d clear\n", n+1);
*/
	return 0;
}
int getch(void)
{
	int ch;

	struct termios buf;
	struct termios save;

	tcgetattr(0, &save);
	buf = save;

	buf.c_lflag&=~(ICANON|ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;

	tcsetattr(0, TCSAFLUSH, &buf);

	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);

	return ch;
}
/*void movement(int n, int ch1) // 움직임 제어하는 함수 미완성
{
	int tmp, ch2, ch3;
	switch (ch1)
	{
		case (104) : // h 입력
			ch2 = map[n][player_x-1][player_y];
			ch3 = map[n][player_x-2][player_y];
			switch (ch2)
			{
				case (32) :
					tmp = map[n][player_x-1][player_y];
					map[n][player_x-1][player_y] = map[n][player_x][player_y];
					map[n][player_x][player_y] = tmp;
					player_x--;
					break;
				case (79) :
					map[n][player_x-1][player_y] = map[n][player_x][player_y];
					map[n][player_x][player_y] = 32;
					player_x--;
					break;
				case (36) :
					switch (ch3)
					{
						case (32) :
							tmp = map[n][player_x-2][player_y];
							map[n][player_x-2][player_y] = map[n][player_x-1][player_y];
							map[n][player_x-1][player_y] = map[n][player_x][player_y];
							map[n][player_x][player_y] = tmp;
							player_x--;
							break;
						case (79) :
							map[n][player_x-2][player_y] = map[n][player_x-1][player_y];
							map[n][player_x-1][player_y] = map[n][player_x][player_y];
							map[n][player_x][player_y] = 32;
							player_x--;
							break;
						default :
							break;
					}
				default :
					break;
		}
		case (106) : // j 입력 
			ch2 = map[n][player_x][player_y+1];
			ch3 = map[n][player_x][player_y+2];
			switch (ch2)
			{
				case (32) :
					tmp = map[n][player_x][player_y+1];
					map[n][player_x][player_y+1] = map[n][player_x][player_y];
					map[n][player_x][player_y] = tmp;
					player_y++;
					break;
				case (79) :
					map[n][player_x][player_y+1] = map[n][player_x][player_y];
					map[n][player_x][player_y] = 32;
					player_y++;
					break;
				case (36) :
					switch (ch3)
					{
						case (32) :
							tmp = map[n][player_x][player_y+2];
							map[n][player_x][player_y+2] = map[n][player_x][player_y+1];
							map[n][player_x][player_y+1] = map[n][player_x][player_y];
							map[n][player_x][player_y] = tmp;
							player_y++;
							break;
						case (79) :
							map[n][player_x][player_y+2] = map[n][player_x][player_y+1];
							map[n][player_x][player_y+1] = map[n][player_x][player_y];
							map[n][player_x][player_y] = 32;
							player_y++;
							break;
						default :
							break;
					}
				default :
					break;
			}
		case (107) : // k 입력
			ch2 = map[n][player_x][player_y-1];
			ch3 = map[n][player_x][player_y-2];
			switch (ch2)
			{
				case (32) :
					tmp = map[n][player_x][player_y-1];
					map[n][player_x][player_y-1] = map[n][player_x][player_y];
					map[n][player_x][player_y] = tmp;
					player_y--;
					break;
				case (79) :
					map[n][player_x][player_y-1] = map[n][player_x][player_y];
					map[n][player_x][player_y] = 32;
					player_y--;
					break;
				case (36) :
					switch (ch3)
					{
						case (32) :
							tmp = map[n][player_x][player_y-2];
							map[n][player_x][player_y-2] = map[n][player_x][player_y-1];
							map[n][player_x][player_y-1] = map[n][player_x][player_y];
							map[n][player_x][player_y] = tmp;
							player_y--;
							break;
						case (79) :
							map[n][player_x][player_y-2] = map[n][player_x][player_y-1];
							map[n][player_x][player_y-1] = map[n][player_x][player_y];
							map[n][player_x][player_y] = 32;
							player_y--;
							break;
						default :
							break;
					}
				default :
					break;
			}
		case (108) : // l 입력
			ch2 = map[n][player_x+1][player_y];
			ch3 = map[n][player_x+2][player_y];
			switch (ch2)
			{
				case (32) :
					tmp = map[n][player_x+1][player_y];
					map[n][player_x+1][player_y] = map[n][player_x][player_y];
					map[n][player_x][player_y] = tmp;
					player_x++;
					break;
				case (79) :
					map[n][player_x+1][player_y] = map[n][player_x][player_y];
					map[n][player_x][player_y] = 32;
					player_x++;
					break;
				case (36) :
					switch (ch3)
					{
						case (32) :
							tmp = map[n][player_x+2][player_y];
							map[n][player_x+2][player_y] = map[n][player_x+1][player_y];
							map[n][player_x+1][player_y] = map[n][player_x][player_y];
							map[n][player_x][player_y] = tmp;
							player_x++;
							break;
						case (79) :
							map[n][player_x+2][player_y] = map[n][player_x+1][player_y];
							map[n][player_x+1][player_y] = map[n][player_x][player_y];
							map[n][player_x][player_y] = 32;
							player_x++;
							break;
						default :
							break;
					}
				default :
					break;
			}
		default :
			break;
	}
	return;
}*/
