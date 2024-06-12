#include"Game.h"
#include <conio.h>

#define RESET   "\033[0m"
#define YELLOW  "\033[93m"   
#define BLUE    "\033[94m" 
#define MAGENTA "\033[95m" 

int main()
{
    Game* game_2048 = new Game();

	cout << BLUE << "Hi," << " Welcome" << RESET  " to \""<< MAGENTA << "Drop letters" << RESET <<"\" game" << "!" << endl << endl;

	char keyPressed;

	while (true)
	{
		cout << "Press \"" << YELLOW << "1" << RESET << "\" to start game" << endl;
		cout << "Press \"" << YELLOW << "2" << RESET << "\" to see Your best results...";

		keyPressed = _getch();

		if (keyPressed == '1')
		{
			game_2048->StartGame();
		}
		else if (keyPressed == '2')
		{
			PrintScoreBoard();
		}
	}

    
	return 0;
}


