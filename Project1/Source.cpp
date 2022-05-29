#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>

class gcode
{
private:
	int x, y, z;
public:
	gcode(int a, int b, int c)
	{
		x = a;
		y = b;
		z = c;
	}

	void Sx(int a)
	{
		x += a;
	}
	void Sy(int b)
	{
		y += b;
	}
	void Sz(int c)
	{
		z += c;
	}
	int GetX()
	{
		return x;
	}
	int GetY()
	{
		return y;
	}
	int GetZ()
	{
		return z;
	}

	friend std::ostream& operator<< (std::ostream& out, const gcode& code);
};

std::ostream& operator<<(std::ostream& out, const gcode& code)
{
	std::cout << code.x << ' ' << code.y << ' ' << code.z << std::endl;
	return out;
}

int main()
{
	std::vector<gcode> vec;
	char c;
	std::cout << " <s> Set start point <a> Add gcode point <c> Do count <p> Print result <t> Text info <e> Exit";
	std::cout << " --> ";
	std::cin >> c;
	gcode gc(0,0,0);

	while (c != 'e')
	{
		if (c == 's') // set start point
		{
			int x, y, z;
			std::cout << "Enter x - ";
			std::cin >> x;
			
			std::cout << "Enter y - ";
			std::cin >> y;
			
			std::cout << "Enter z - ";
			std::cin >> z;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "\nDefault values\n";
			}
			else
			{
				gc.Sx(x);
				gc.Sy(y);
				gc.Sz(z);
			}

		}
		if (c == 'a') // add gcode instruction in console
		{
			
			int x, y, z;
			
				std::cout << "Enter x - ";
				std::cin >> x;
				std::cout << "Enter y - ";
				std::cin >> y;
				std::cout << "Enter z - ";
				std::cin >> z;
		
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "\nERROR SCRIPT\n";
			}
			else
			{
				gcode g(x, y, z);
				vec.push_back(g);
			}
		}
		if (c == 'c')
		{
			for (int i = 0; i < vec.size(); i++)
			{
				int x, y, z;
				x = vec[i].GetX();
				y = vec[i].GetY();
				z = vec[i].GetZ();
				gc.Sx(x);
				gc.Sy(y);
				gc.Sz(z);
			}
			vec.clear();
			std::cout << "Done\n";
		}
		if (c == 'p')
		{
			std::cout << gc;
		}
		if (c == 't')
		{
			bool f = 0;
			std::ifstream fileread;
			fileread.open("gcode.txt");

			if (!fileread)
			{
				fileread.close();
				return 0;
			}

			while (!fileread.eof())
			{
				int x, y, z;
				
				
				if (fileread >> x and fileread >> y and fileread >> z)
				{	
					gcode g(x, y, z);
					vec.push_back(g);
				}
				else
				{
						std::cin.clear();
						std::cin.ignore(32767, '\n');
						std::cout << "\nERROR SCRIPT\n";
						goto exit;
				}

			}
			
		}
	exit:
		std::cout << " --> ";
		std::cin >> c;
	}


	

}


