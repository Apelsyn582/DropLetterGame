#include "Game.h"

long int getCurrentSecondsFrom1970()
{
	return (long int)time(NULL);
}

char Game::getLetter()
{
    SetRand_Letters();

    return rand_letters[getCurrentSecondsFrom1970() % rand_letters.size()];
}

void Game::AddObjectToScene()
{
    char value = next_value;

    next_value = getLetter();

    scene.AddObject(new Object(value, 0, 2));
}

void Game::SetRand_Letters()
{
    if (rand_letters.size() == 3 && scene.GetScore() > 5)
    {
        rand_letters.push_back('E');
    }
    else if (rand_letters.size() == 4 && scene.GetScore() > 10)
    {
        rand_letters.push_back('F');
    }
    else if (rand_letters.size() == 5 && scene.GetScore() > 15)
    {
        rand_letters.push_back('G');
    }
    else if (rand_letters.size() == 6 && scene.GetScore() > 20)
    {
        rand_letters.push_back('H');
    }
}

void Game::StartGame()
{

	long int previousUpdateTime = getCurrentSecondsFrom1970();

    while (true)
    {
        long int currentTime = getCurrentSecondsFrom1970();

        if ((currentTime - previousUpdateTime) >= 1)
        {

            system("cls");

            scene.UpdateScene(next_value);

            if (scene.PossibilityToAddNewObject())
            {
                AddObjectToScene();
            }

            scene.UpdateObject(scene.GetNumberOfObjects() - 1);

            previousUpdateTime = currentTime;
        }

        if (GetAsyncKeyState(VK_ESCAPE)) 
        {
            if (scene.GameOver())
            {
                exit(EXIT_FAILURE);
            }
        }

    }
}