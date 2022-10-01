/**
 * @author #meBhalendra
 * @version 0.1
 * @date 2022-10-02
 *
 * @copyright Copyright (c) 2022 MeStudio.live
 *
 */
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Please enter file path.";
		return 1;
	}
	string filename{argv[1]};
	fstream edl(filename);
	string text{""};
	for (string line; getline(edl, line);)
	{
		text += line + '\n';
	}
	if (text == "")
	{
		cout << "File content not found.";
		return 1;
	}
	smatch found;
	regex pattern{R"(M:(.*)\|)"};
	string subject = text;
	vector<string> titles;
	titles.push_back("Intro");
	while (regex_search(subject, found, pattern))
	{
		titles.push_back(found[1]);
		subject = found.suffix().str();
	}
	subject = text;
	pattern = R"(C\s+.*:(\d+:\d+):\d+\s)";
	vector<string> timings;
	timings.push_back("00:00");
	while (regex_search(subject, found, pattern))
	{
		timings.push_back(found[1]);
		subject = found.suffix().str();
	}
	for (int i = 0; i < titles.size(); i++)
	{
		cout << timings[i] << " " << titles[i] << endl;
	}
}
