#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <regex>
#include <array>

#include "urlfile.hpp"

using namespace std;

namespace urlopen
{

/*
* Regex for parsing a url, from
* https://regexr.com/3k0ob
* The source has more documentation on the different groups.
*/
const regex url_pattern("^(?:(http[s]?|ftp[s]):\\/\\/)?([^:\\/\\s]+)(:[0-9]+)?((?:\\/\\w+)*\\/)([\\w\\-\\.]+[^#?\\s]+)([^#\\s]*)?(#[\\w\\-]+)?$");

const string FIREFOX_EXECUTABLE = "/usr/bin/firefox";
const string CHROME_EXECUTABLE = "google-chrome";

const string BROWSER_EXECUTABLE = "xdg-open";

const string UrlFile::TOP_SECTION = "InternetShortcut";

string UrlFile::get_property(string key)
{
	const char* temp = _ini.GetValue(TOP_SECTION.c_str(), key.c_str(), NULL);
	if (!temp)
	{
		stringstream ss;
		ss << "File does not contain key " << key << " in section " << TOP_SECTION;
		throw invalid_argument(ss.str());
	}
	string value(temp);
	return value;
}

UrlFile::UrlFile(string fname)
{
	_ini.SetUnicode();
	_ini.LoadFile(fname.c_str());
}

void UrlFile::open_shortcut()
{
	// https://askubuntu.com/a/8256/574988
	// https://stackoverflow.com/a/1950367/5415895
	// https://stackoverflow.com/q/8371363/5415895
	
	string url = get_property("URL");

	pid_t process = fork();
	if (process < 0)
	{
		cerr << "Error" << endl;
	}
	if (process == 0)
	{
		//cout << url << endl;
		// https://stackoverflow.com/a/12596877/5415895
		execl("/usr/bin/xdg-open", "xdg-open", url.c_str(), (char*) NULL);
	}
	else
	{
		// There's really nothing to do here.
	}
}

void UrlFile::open_private_window(Browser b)
{
	array<string, 3> args;
	string url = get_property("URL");

	switch (b)
	{
		case Browser::FIREFOX:
			args[0] = "/usr/bin/firefox";
			args[1] = "firefox";
			args[2] = "--private-window";
			break;
		case Browser::CHROME:
			args[0] = "/usr/bin/google-chrome";
			args[1] = "google-chrome";
			args[2] = "--incognito";
			break;
		default:
			throw invalid_argument("Invalid browser");
	}

	pid_t process = fork();
	if (process < 0)
	{
		cerr << "Error" << endl;
	}
	if (process == 0)
	{
		char *cc[] = {
			(char*) args[1].c_str(),
			(char*) args[2].c_str(),
			(char*) url.c_str(),
			NULL
		};
		execv(args[0].c_str(), cc);
	}
	else
	{
		// ???
	}
}

string UrlFile::get_url()
{
	return get_property("URL");
}

string UrlFile::get_domain()
{
	string url = get_url();
	smatch sm;
	regex_match(url, sm, url_pattern);

	return sm[2];
}

}