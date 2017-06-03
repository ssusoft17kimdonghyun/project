/* project 코드파일
   2017.5.25 - 5.31
   20170263 김동현 */
#include <stdio.h>
#include <termio.h> // getch() 함수를 위한 헤더 파일
#include <stdlib.h> //system() 함수를 위한 헤더 파일
#include <unistd.h> // sleep() 함수를 위한 헤더 파일
char map[5][30][30]; // 맵 파일을 저장하는 변수
int player_x, player_y; // 플레이어의 위치
int stage; //스테이지 번호 지정
int getch(); // 입력 함수
void movement(int, int); // 움직임 제어하는 함수
int main(void)
{
	FILE *read_map;
	char map_file[1500];
	int n = 0, x = 0, y = 0, clear = 0;
	int p = 0, m = 0, e = 0, num_p[5], num_m[5], num_e; // 파일 오류 검사 밎 맵 저장에 사용
	int map_slot[5], slot_x[25], slot_y[25]; // O의 개수와 위치 저장
	int input_ch; // movement 함수 매개 변수
	int num_box, num_slot = 0, map_error = 0; // 파일 오류 검사

	// map.txt 파일 읽어오고 map_file에 저장
	read_map = fopen("map.txt", "r");
	if (read_map == NULL) // 파일이 없을때의 에러
	{
		printf("오류 : map.txt 파일이 없습니다.\n");
		fclose(read_map);
		return 0;
	}
	for (int i = 0; map_file[i-1] != 'd'; i++)
	{
		fscanf(read_map, "%c", &map_file[i]);
	}
	fclose(read_map);

	for (int i = 0; i < sizeof(map_file); i++)
	{
		if (map_file[i] == 'p')
		{
			num_p[p] = i;
			p++;
		}
		else if (map_file[i] == 'm')
		{
			num_m[m] = i;
			m++;
		}
		else if (map_file[i] == 'e')
		{
			num_e = i;
			e++;
		}
	}
	if (p < 5) // 파일이 손상되었을때의 에러
	{
		printf("오류 : map.txt 파일이 손상되었습니다.\n");
		return 0;
	}
	else if (m < 5)
	{
		printf("오류 : map.txt 파일이 손상되었습니다.\n");
		return 0;
	}
	else if (e < 1)
	{
		printf("오류 : map.txt 파일이 손상되었습니다.\n");
		return 0;
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
		if (map[n][x][y] == 'O')
			map_slot[n]++;
		x++;
	}

	n = 1, x = 0, y = 0; // map2 을 map[1][x][y]에 저장
	for (int i = (num_p[1] + 3); i < num_m[2]; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		if (map[n][x][y] == 'O')
			map_slot[n]++;
		x++;
	}

	n = 2, x = 0, y = 0; // map3 을 map[2][x][y]에 저장
	for (int i = (num_p[2] + 3); i < num_m[3]; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		if (map[n][x][y] == 'O')
			map_slot[n]++;
		x++;
	}

	n = 3, x = 0, y = 0; // map4 을 map[3][x][y]에 저장
	for (int i = (num_p[3] + 3); i < num_m[4]; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		if (map[n][x][y] == 'O')
			map_slot[n]++;
		x++;
	}

	n = 4, x = 0, y = 0; // map5 을 map[4][x][y]에 저장
	for (int i = (num_p[4] + 3); i < num_e; i++)
	{
		if (map[n][x-1][y] == '\n')
		{
			y++;
			x = 0;
		}
		map[n][x][y] = map_file[i];
		if (map[n][x][y] == 'O')
			map_slot[n]++;
		x++;
	}

	// O와 $의 개수가 다를 경우의 에러
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
		else if (num_box == num_slot == 0)
		{
			printf("오류 : map%d 파일이 손상되었습니다.\n", n+1);
			map_error = 1;
		}
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

	// 게임 시작
	for (n = 0; n < 5; n++)
	{
		for (y = 0; y < 30; y++)
			for (x = 0; x < 30; x++)
				if (map[n][x][y] == 'O')
				{
					slot_x[num_slot] = x;
					slot_y[num_slot] = y;
					num_slot++;
				}
		printf("map%d start\n\n", n+1);
		sleep(2);
		system("clear");
		while (clear < map_slot[n])
		{
			system("clear");
			clear = 0;
			for (y = 0; y < 30; y++)
				for (x = 0; x < 30; x++)
				{
					printf("%c", map[n][x][y]);
					if (map[n][x][y] == '@')
					{
						player_x = x;
						player_y = y;
					}
				}
			printf("\n(Command) : ");
			input_ch = getch();
			printf("\n");
			if (((input_ch == 104) || (input_ch == 106)) || ((input_ch == 107) || (input_ch == 108)))
			{
				movement(n, input_ch);
				for (int i = 0; i < num_slot; i++)
				{
					if (map[n][slot_x[i]][slot_y[i]] == ' ')
						map[n][slot_x[i]][slot_y[i]] = 'O';
					if (map[n][slot_x[i]][slot_y[i]] == '$')
						clear++;
				}
			}//else if
		}
		printf("\nmap%d clear\n", n+1);
	}
	printf("all map clear!\nend program\n");
	return 0;
}
int getch(void) // 입력 함수
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
void movement(int n, int ch1) // 움직임 제어하는 함수
{
	char ch2, ch3;
	switch (ch1)
	{
		case (104) : // h 입력
			ch2 = map[n][player_x-1][player_y];
			ch3 = map[n][player_x-2][player_y];
			if (ch2 == ' ')
			{
				map[n][player_x-1][player_y] = map[n][player_x][player_y];
				map[n][player_x][player_y] = ' ';
				break;
			}
			else if (ch2 == 'O')
			{
				map[n][player_x-1][player_y] = map[n][player_x][player_y];
				map[n][player_x][player_y] = ' ';
				break;
			}
			else if (ch2 == '$')
			{
				if (ch3 == ' ')
				{
					map[n][player_x-2][player_y] = map[n][player_x-1][player_y];
					map[n][player_x-1][player_y] = map[n][player_x][player_y];
					map[n][player_x][player_y] = ' ';
					break;
				}
				else if (ch3 == 'O')
				{
					map[n][player_x-2][player_y] = map[n][player_x-1][player_y];
					map[n][player_x-1][player_y] = map[n][player_x][player_y];
					map[n][player_x][player_y] = ' ';
					break;
				}
				else
					break;
			}
			else
				break;
		case (106) : // j 입력 
			ch2 = map[n][player_x][player_y+1];
			ch3 = map[n][player_x][player_y+2];
			if (ch2 == ' ')
			{
				map[n][player_x][player_y+1] = map[n][player_x][player_y];
				map[n][player_x][player_y] = ' ';
				break;
			}
			else if (ch2 == 'O')
			{
				map[n][player_x][player_y+1] = map[n][player_x][player_y];
				map[n][player_x][player_y] = ' ';
				break;
			}
			else if (ch2 == '$')
			{
				if (ch3 == ' ')
				{
					map[n][player_x][player_y+2] = map[n][player_x][player_y+1];
					map[n][player_x][player_y+1] = map[n][player_x][player_y];
					map[n][player_x][player_y] = ' ';
					break;
				}
				else if (ch3 == 'O')
				{
					map[n][player_x][player_y+2] = map[n][player_x][player_y+1];
					map[n][player_x][player_y+1] = map[n][player_x][player_y];
					map[n][player_x][player_y] = ' ';
					break;
				}
				else
					break;
			}
			else
				break;
		case (107) : // k 입력
			ch2 = map[n][player_x][player_y-1];
			ch3 = map[n][player_x][player_y-2];
			if (ch2 == ' ')
			{
				map[n][player_x][player_y-1] = map[n][player_x][player_y];
				map[n][player_x][player_y] = ' ';
				break;
			}
			else if (ch2 == 'O')
			{
				map[n][player_x][player_y-1] = map[n][player_x][player_y];
				map[n][player_x][player_y] = ' ';
				break;
			}
			else if (ch2 == '$')
			{
				if (ch3 == ' ')
				{
					map[n][player_x][player_y-2] = map[n][player_x][player_y-1];
					map[n][player_x][player_y-1] = map[n][player_x][player_y];
					map[n][player_x][player_y] = ' ';
					break;
				}
				else if (ch3 == 'O')
				{
					map[n][player_x][player_y-2] = map[n][player_x][player_y-1];
					map[n][player_x][player_y-1] = map[n][player_x][player_y];
					map[n][player_x][player_y] = ' ';
					break;
				}
				else
					break;
			}
			else
				break;
		case (108) : // l 입력
			ch2 = map[n][player_x+1][player_y];
			ch3 = map[n][player_x+2][player_y];
			if (ch2 == ' ')
			{
				map[n][player_x+1][player_y] = map[n][player_x][player_y];
				map[n][player_x][player_y] = ' ';
				break;
			}
			else if (ch2 == 'O')
			{
				map[n][player_x+1][player_y] = map[n][player_x][player_y];
				map[n][player_x][player_y] = ' ';
				break;
			}
			else if (ch2 == '$')
			{
				if (ch3 == ' ')
				{
					map[n][player_x+2][player_y] = map[n][player_x+1][player_y];
					map[n][player_x+1][player_y] = map[n][player_x][player_y];
					map[n][player_x][player_y] = ' ';
					break;
				}
				else if (ch3 == 'O')
				{
					map[n][player_x+2][player_y] = map[n][player_x+1][player_y];
					map[n][player_x+1][player_y] = map[n][player_x][player_y];
					map[n][player_x][player_y] = ' ';
					break;
				}
				else
					break;
			}
			else
				break;
		default :
			break;
	}
	return;
}
