#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <regex>

#include "urlfile.hpp"

using namespace std;

namespace urlopen
{

const string UrlFile::TOP_SECTION = "InternetShortcut";

/*
* Regex for parsing a url, from
* https://regexr.com/3k0ob
* The source has more documentation on the different groups.
*/
const regex url_pattern("^(?:(http[s]?|ftp[s]):\\/\\/)?([^:\\/\\s]+)(:[0-9]+)?((?:\\/\\w+)*\\/)([\\w\\-\\.]+[^#?\\s]+)([^#\\s]*)?(#[\\w\\-]+)?$");

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