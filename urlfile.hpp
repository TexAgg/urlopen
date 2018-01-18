#ifndef URLFILE_HPP
#define URLFILE_HPP

#include <string>
#include <SimpleIni.h>

/*
* Class for representing the structure of a .url file.
*
* I couldn't find an official standard for url files but
* this guide was useful: http://bit.ly/2m6FiAi
*/
class UrlFile
{
	CSimpleIniA _ini;

public:

	/*
	* Constructs a url file given the url.
	*/
	UrlFile(std::string fname);

	/*
	* Open the url in the default browser.
	* Requires `xdg-open`.
	*/
	void open_shortcut();
};

#endif