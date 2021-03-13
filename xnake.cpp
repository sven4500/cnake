#include <iostream>
#include <vector>
#include <thread> // sleep_for
#include <chrono> // seconds

enum direction { left, right, up, down };

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
	direction dir = left;

	int const width = 119, height = 29;

	while (1)
	{
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				if (y == 0 || y == height - 1)
				{
					if (x > 0 && x < width - 1)
					{
						std::cout << '=';
					}
					else
					{
						std::cout << '+';
					}
				}
				else
					if (x == 0 || x == width - 1)
					{
						if (y > 0 && y < height)
						{
							std::cout << '|';
						}
					}
					else
						if (std::find(snake.begin(), snake.end(), point(x, y)) != snake.end())
						{
							std::cout << 'o';
						}
						else
						{
							std::cout << ' ';
						}
			}

			std::cout << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}
