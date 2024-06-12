#pragma once
#include<windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <Lmcons.h>
using namespace std;


void SaveScore(string score);

vector<pair<string, string>> GetScoreBoard();

void PrintScoreBoard();

