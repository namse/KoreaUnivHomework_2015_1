#include <unistd.h>
#include <iostream>

int main()
{
	while(true)
	{
		char ch;
		std::cout << "(E)nqueue or (D)equeue : ";
		std::cin >> ch;

		switch(ch)
		{
			case 'E':
			case 'e':
			{
				int value;
				std::cout << "value : ";
				std::cin >> value;
				syscall(338, value);
			}break;

			case 'D':
			case 'd':
			{
				int value = syscall(339);
				std::cout << "value : " << value << std::endl;
			}break;
			
			default:
			{
				std::cout << "wrong key." << std::endl;
			}break;
		}
	}
	return 0;
}
