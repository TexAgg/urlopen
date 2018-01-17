#ifndef URLFILE_HPP
#define URLFILE_HPP

#include <unordered_map>
#include <string>

/*
* Class for representing the structure of a .url file.
*
* I couldn't find an official standard for url files but
* this guide was useful: http://bit.ly/2m6FiAi
*/
class UrlFile
{
	/*
	* Dictionary mapping the keys to the values from the file.
	* Only one entry is used so most of this is wasted space and overhead.
	*/
	std::unordered_map<std::string, std::string> _entries;
	// I'm not sure what this means but we don't need it.
	std::string _group;

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