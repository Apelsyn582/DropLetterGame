#pragma once
#include <vector>
#include "Object.h"
#include "foo.h"
#include <conio.h>
#include <iomanip>

class Scene
{
private:
    char** field;
    int row = 8;
    int column = 5;
    vector<Object*> objects;
    int score = 0;

    void UpdateField();

    void HandleObject(int i, int j);

    void HandlePosition1(int i, int j);

    void HandlePosition2(int i, int j, char operation);

    void HandlePosition3(int i, int j, char operation);

    void HandlePosition4(int i, int j);

public:
    Scene();

    ~Scene();

    void UpdateObject(int index);

    void AddObject(Object* ob);

    void UpdateScene(char next);

    int GetIndexOfObjectByCoordinates(int x, int y);

    int GetNumberOfObjects();

    bool PossibilityToAddNewObject();

    bool GameOver();

    int GetScore();

    void SetScore();
    
};

