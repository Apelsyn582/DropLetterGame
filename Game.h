#pragma once
#include "Scene.h"
#include <ctime>
#include <cstdlib>

class Game
{
private:
	Scene scene;

	vector<char> rand_letters = { 'A', 'B', 'C', 'D' };

	char next_value = 'A';

	void AddObjectToScene();

	char getLetter();

	void SetRand_Letters();
public:

	void StartGame();
};

