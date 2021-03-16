#include <iostream>
#include <cstdlib> // rand, srand
#include <vector>
#include <thread> // sleep_for
#include <chrono> // seconds
#include <conio.h> // getch

enum direction { left = 75, right = 77, up = 72, down = 80 };

struct point
{
	point():
		x(0), y(0)
	{
	
	}

	point(int x, int y) :
		x(x), y(y)
	{

	}

	bool operator==(point const& other)const
	{
		return (this->x == other.x) && (this->y == other.y);
	}

	int x;
	int y;

};

int main()
{
	std::vector<point> snake{ point(39, 10), point(40, 10), point(41, 10) };
	point head = snake.front();
	point food = point(0, 0);
	direction dir = left;

	int const width = 59, height = 29;

	srand((int)time(0));

	while (1)
	{
		if (kbhit())
		{
			int const key = getch();

			// Для стрелок возвращается два кода. Сперва код откуда была нажата стрелка
			// 224 для непосредственно стрелок и 0 для numpad'а. Поток код стрелки. Эти
			// коды не являются универсальными и могут отличаться на других платформах.
			if (key == 224 || key == 0)
			{
				continue;
			}

			// Запрещаем противоположные направления.
			if ((key == left && dir != right) ||
				(key == right && dir != left) ||
				(key == up && dir != down) ||
				(key == down && dir != up))
			{
				dir = (direction)key;
			}
		}

		if (dir == left)
		{
			head.x -= 1;
		}
		else if (dir == right)
		{
			head.x += 1;
		}
		else if (dir == up)
		{
			head.y -= 1;
		}
		else if (dir == down)
		{
			head.y += 1;
		}

		snake.insert(snake.begin(), head);

		if (head == food)
		{
			food = point(0, 0);
		}
		else
		{
			snake.pop_back();	
		}

		if (food == point(0, 0))
		{
			point const food_drop = point(1 + rand() % (width - 2), 1 + rand() % (height - 2));

			if (std::find(snake.begin(), snake.end(), food_drop) == snake.end())
			{
				food = food_drop;
			}
		}
		
		// Не кросс-платформенное решение, но лучше пока не наёдено.
		std::system("cls");

		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				if (y == 0 || y == height - 1)
				{
					if (x > 0 && x < width - 1)
					{
						std::cout << '-';
					}
					else
					{
						std::cout << '+';
					}
				}
				else if (x == 0 || x == width - 1)
				{
					if (y > 0 && y < height)
					{
						std::cout << '|';
					}
				}
				else if (x == food.x&&y == food.y)
				{
					std::cout << 'o';
				}
				else if (x == head.x && y == head.y)
				{
					if (dir == left)
					{
						std::cout << '<';
					}
					else if (dir == right)
					{
						std::cout << '>';
					}
					else if (dir == up)
					{
						std::cout << 'A';
					}
					else if (dir == down)
					{
						std::cout << 'V';
					}
				}
				else if (std::find(snake.begin(), snake.end(), point(x, y)) != snake.end())
				{
					if (snake.back() == point(x, y))
					{
						std::cout << '?';
					}
					else
					{
						std::cout << '.';
					}
				}
				else
				{
					std::cout << ' ';
				}
			}

			std::cout << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
