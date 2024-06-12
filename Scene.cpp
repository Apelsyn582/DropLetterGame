#include "Scene.h"
#define RESET   "\033[0m"
#define YELLOW      "\033[33m"      
#define CYAN    "\033[36m"

Scene::Scene()
{
    field = new char* [row];

    for (int i = 0; i < row; ++i) 
    {
       field[i] = new char[column];
    }

}

Scene::~Scene()
{
    for (int i = 0; i < row; ++i) 
    {
        delete[] field[i];
    }

    delete[] field;
}

void Scene::HandlePosition1(int i, int j)
{
    objects[GetIndexOfObjectByCoordinates(i + 1, j)]->ChangeValue(); SetScore();

    objects.erase(objects.begin() + GetIndexOfObjectByCoordinates(i, j));

    field[i][j] = ' ';
}

void Scene::HandlePosition2(int i, int j, char operation)
{
    int res_of_operation = 0;

    if (operation == '+')
    {
        res_of_operation = j + 1;
    }
    else if (operation == '-')
    {
        res_of_operation = j - 1;
    }

    objects[GetIndexOfObjectByCoordinates(i, res_of_operation)]->ChangeValue(); SetScore();

    objects.erase(objects.begin() + GetIndexOfObjectByCoordinates(i, j));

    field[i][j] = ' ';
}

void Scene::HandlePosition3(int i, int j, char operation)
{
    int res_of_operation = 0;

    if (operation == '+')
    {
        res_of_operation = j + 1;
    }
    else if (operation == '-')
    {
        res_of_operation = j - 1;
    }

    objects[GetIndexOfObjectByCoordinates(i + 1, j)]->ChangeValue(); SetScore();
    objects[GetIndexOfObjectByCoordinates(i + 1, j)]->ChangeValue(); SetScore();

    objects.erase(objects.begin() + GetIndexOfObjectByCoordinates(i, res_of_operation));
    objects.erase(objects.begin() + GetIndexOfObjectByCoordinates(i, j));

    field[i][j] = ' ';
    field[i][res_of_operation] = ' ';  
}

void Scene::HandlePosition4(int i, int j)
{
    objects[GetIndexOfObjectByCoordinates(i, j - 1)]->ChangeValue(); SetScore();
    objects[GetIndexOfObjectByCoordinates(i, j - 1)]->ChangeValue(); SetScore();

    objects.erase(objects.begin() + GetIndexOfObjectByCoordinates(i, j));
    objects.erase(objects.begin() + GetIndexOfObjectByCoordinates(i, j - 2));

    field[i][j] = ' ';
    field[i][j - 2] = ' ';
}

void Scene::UpdateField()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            field[i][j] = ' ';
        }
    }

    for (int i = 0; i < objects.size(); i++) {
        field[objects[i]->x][objects[i]->y] = objects[i]->value;
    }
}

void Scene::HandleObject(int i, int j)
{
    if (field[i][j] != ' ')
    {
        if (!objects[GetIndexOfObjectByCoordinates(i, j)]->is_static)
        {


            if (j != 0 && field[i][j - 1] != ' ')
            {
                objects[GetIndexOfObjectByCoordinates(i, j)]->enable_left_arrow = false;
            }
            else
            {
                objects[GetIndexOfObjectByCoordinates(i, j)]->enable_left_arrow = true;
            }

            if (j != column - 1 && field[i][j + 1] != ' ')
            {
                objects[GetIndexOfObjectByCoordinates(i, j)]->enable_right_arrow = false;
            }
            else
            {
                objects[GetIndexOfObjectByCoordinates(i, j)]->enable_right_arrow = true;
            }

            if (i == row - 1)
            {
                objects[GetIndexOfObjectByCoordinates(i, j)]->DoStatic();
            }            
            else if (field[i][j] == field[i + 1][j])
            {
                if (field[i][j] == field[i][j + 1])
                {
                    HandlePosition3(i, j, '+');
                }
                else if (field[i][j] == field[i][j - 1])
                {
                    HandlePosition3(i, j, '-');
                }
                else
                {
                    HandlePosition1(i, j);
                }
            }
            else if (field[i + 1][j] != ' ')
            {
                objects[GetIndexOfObjectByCoordinates(i, j)]->DoStatic();

            }


            if (field[1][j] != ' ' && field[2][j] != ' ')
            {
                cout << "dead line  :|";
                if (GameOver())
                {
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            if (i != row - 1)
            {
                if (field[i][j] == field[i + 1][j])
                {
                    if (field[i][j] == field[i][j + 1] && objects[GetIndexOfObjectByCoordinates(i, j + 1)]->is_static)
                    {
                        HandlePosition3(i, j, '+');
                    }
                    else if (field[i][j] == field[i][j - 1] && objects[GetIndexOfObjectByCoordinates(i, j - 1)]->is_static)
                    {
                        HandlePosition3(i, j, '-');
                    }
                    else
                    {
                        HandlePosition1(i, j);
                    }
                }
                if (field[i + 1][j] == ' ')
                {
                    objects[GetIndexOfObjectByCoordinates(i, j)]->x += 1;
                }
            }
            if (j != column + 1 && field[i][j] != ' ')
            {
                if (field[i][j] == field[i][j - 1] && objects[GetIndexOfObjectByCoordinates(i, j)]->is_static && objects[GetIndexOfObjectByCoordinates(i, j - 1)]->is_static)
                {
                    if (field[i][j - 1] == field[i][j - 2] && objects[GetIndexOfObjectByCoordinates(i, j - 2)]->is_static)
                    {
                        HandlePosition4(i, j);
                    }
                    else
                    {
                        HandlePosition2(i, j, '-');
                    }
                }
            }
            if (j != column - 1 && field[i][j] != ' ')
            {
                if (field[i][j] == field[i][j + 1] && objects[GetIndexOfObjectByCoordinates(i, j)]->is_static && objects[GetIndexOfObjectByCoordinates(i, j + 1)]->is_static)
                {
                    HandlePosition2(i, j, '+');
                }
            }
        }
    }
    cout << field[i][j];
}

void Scene::UpdateObject(int index)
{
    char BeginDirection = ' ';

    if (_kbhit())
    {
        BeginDirection = _getch();
    }
    switch (BeginDirection)
    {
    case ' ':
    {

        objects[index]->DownwardMovement();

        break;
    }
    case 'a':
    {
        objects[index]->LeftArrow();

        break;
    }
    case 'd':
    {
        objects[index]->RightArrow();

        break;
    }
    }
}

void Scene::AddObject(Object* ob)
{
    objects.push_back(ob);
}

void Scene::UpdateScene(char next_value)
{
    string title;

    if (score == 0)
    {
        title = "     ABCDE... Hooray! :) ";
    }
    else
    {
        title = "     Score: " + to_string(score);
    }

    UpdateField();

    for (int i = -1; i < row; i++)
    {
        if (i == -1)
        {
            cout << endl << CYAN << title << endl << endl << endl << YELLOW << setw(15) << "______" << "    Next: " << next_value << RESET;
        }
        else
        {
            cout << endl;
            for (int j = -1; j < column; j++)
            {
                if (j == -1)
                {
                    cout << setw(14) << YELLOW << "|" << RESET;
                }
                else
                {
                    HandleObject(i, j);
                }
            }
        }
    }
}

int Scene::GetIndexOfObjectByCoordinates(int x, int y)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->x == x && objects[i]->y == y)
        {
            return i;
        }
    }
}

int Scene::GetNumberOfObjects()
{
    return objects.size();
}

bool Scene::PossibilityToAddNewObject()
{
    if (!objects.empty())
    {
        if (objects.back()->is_static)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

bool Scene::GameOver()
{
    Sleep(2000);

    system("cls");

    cout << "Game over      Score: " << score << endl;

    cout << "Do you want to save results ? (y/n)" << endl;
    cout << "->";

    string choice ;
    cin >> choice;

    if (choice == "y" || choice == "Y")
    {
        SaveScore(to_string(score));
    }

    return true;
}

int Scene::GetScore()
{
    return score;
}

void Scene::SetScore()
{
    score++;
}