#ifndef URLFILE_HPP
#define URLFILE_HPP

#include <string>

#include <SimpleIni.h>

namespace urlopen
{

/*
* Class for representing the structure of a .url file.
*
* I couldn't find an official standard for url files but
* this guide was useful: http://bit.ly/2m6FiAi
*/
class UrlFile
{
	CSimpleIniA _ini;

	std::string get_property(std::string key);

public:

	static const std::string TOP_SECTION;

	/*
	* Constructs a url file given the url.
	*/
	UrlFile(std::string fname);

	/*
	* Open the url in the default browser.
	* Requires `xdg-open`.
	*/
	void open_shortcut();

	std::string get_url();
};

}

#endif