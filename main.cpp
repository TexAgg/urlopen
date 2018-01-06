#include <iostream>
#include <string>
#include <stdlib.h>  

#include "urlfile.hpp"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "No file passed." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string fname(argv[1]);
	UrlFile uf (fname);
	uf.open_shortcut();
}