#include <stdexcept>
#include <unistd.h>
#include <iostream>

#include "urlfile.hpp"

using namespace std;

const string TOP_SECTION = "InternetShortcut";

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
	
	const char* url_char = _ini.GetValue(TOP_SECTION.c_str(), "URL", NULL);

	if (!url_char)
		throw invalid_argument("File contained no URL field");
	
	string url(url_char);

	pid_t process = fork();
	if (process < 0)
	{
		cerr << "Error" << endl;
	}
	if (process == 0)
	{
		cout << url << endl;
		// https://stackoverflow.com/a/12596877/5415895
		execl("/usr/bin/xdg-open", "xdg-open", url.c_str(), (char*) NULL);
	}
	else
	{
		// There's really nothing to do here.
	}
}