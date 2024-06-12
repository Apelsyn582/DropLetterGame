#include "foo.h"

bool PredForSort(const pair<string, string>& a, const pair<string, string>& b)
{
     return a.first > b.first;
}

void SaveScore(string score)
{

	time_t now = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &now);

	string date = to_string(local_time.tm_mday) + "." + to_string(local_time.tm_mon + 1) + "." + to_string(local_time.tm_year + 1900);

	string FileName = "file.txt";

	ofstream FileToWrite(FileName, ios::app);

	if (FileToWrite.is_open())
	{
		FileToWrite << score << " " << date << endl;;

		FileToWrite.close();
		cout << "Done!" << endl;
	}
	else
	{
		cout << "File couldn't be open" << endl;
	}

}

vector<pair<string, string>> GetScoreBoard()
{
	string FileName = "file.txt";

	ifstream FileToRead(FileName);

	string score;

	string date;

	vector<pair<string, string>> records;


	if (FileToRead.is_open())
	{
		while (FileToRead >> score >> date)
		{
			records.push_back(pair<string, string>(score, date));
		}
	}
	else
	{
		cout << "File couldn't be open" << endl;
	}

	sort(records.begin(), records.end(), PredForSort);
	

	return records;
}

void PrintScoreBoard()
{
	system("cls");

	vector<pair<string, string>> records = GetScoreBoard();

	vector<pair<string, string>>::iterator itr;

	cout << " | -- Best scores -- | " << endl;
	cout << " __________________________" << endl;

	for (itr = records.begin(); itr != records.end(); ++itr)
	{
		cout << " score: " << itr->first << " |     date: " << itr->second << endl;
	}
	cout << " __________________________" << endl;
}