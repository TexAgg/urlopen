#include <fstream>
#include <regex>
#include <stdexcept>
#include <unistd.h>
#include <iostream>

#include "urlfile.hpp"

using namespace std;

UrlFile::UrlFile(string fname)
{
	ifstream infile(fname);
	int line_count = 0;

	// https://stackoverflow.com/a/7868998/5415895
	string line;
	while (getline(infile, line))
	{
		regex pattern ("(.+)=(.+)[\r\n]*");

		if (line_count == 0)
		{
			regex group_pattern("\\[(.+)\\][\r\n]*");

			smatch sm;
			bool succeed = regex_match(line, sm, group_pattern);
			if (!succeed || sm.size() < 2)
				throw invalid_argument("Invalid syntax on line 0: " + line);
			
			_group = sm[1];
		}
		else
		{
			smatch sm;
			bool succeed = regex_match(line, sm, pattern);
			if (!succeed || sm.size() < 3)
				throw invalid_argument("Invalid syntax on line " + to_string(line_count) + ": " + line);
			
			string key = sm[1];
			string value = sm[2];
			_entries[key] = value;
		}

		line_count++;
	}
}

void UrlFile::open_shortcut()
{
	// https://askubuntu.com/a/8256/574988
	// https://stackoverflow.com/a/1950367/5415895
	// https://stackoverflow.com/q/8371363/5415895
	
	if (_entries.find("URL") == _entries.end())
		throw invalid_argument("File contained no URL field");

	pid_t process = fork();
	if (process < 0)
	{
		cerr << "Error" << endl;
	}
	if (process == 0)
	{
		cout << _entries["URL"] << endl;
		// https://stackoverflow.com/a/12596877/5415895
		execl("/usr/bin/xdg-open", "xdg-open", _entries["URL"].c_str(), (char*) NULL);
	}
	else
	{
		// hell yeah dude
	}
}