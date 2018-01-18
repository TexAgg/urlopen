#include <iostream>
#include <string>
#include <stdlib.h>
#include <getopt.h>  

#include "urlfile.hpp"

int main(int argc, char** argv)
{
	bool print_url = false;
	int c;
	while ((c = getopt(argc, argv, "u:")) != -1)
	{
		switch (c)
		{
			case 'u':
				print_url = true;
				break;
			default:
				break;

		}
	}
	if (!argv[optind]) 
	{
  		std::cerr << "No filename passed" << std::endl;
  		exit(EXIT_FAILURE);
	}

	std::string fname(argv[argc-1]);
	UrlFile uf(fname);
	if (print_url)
	{
		std::cout << uf.get_url() << std::endl;
	}
	else
	{
		uf.open_shortcut();
	}
}