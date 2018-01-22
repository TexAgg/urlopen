#include <iostream>
#include <string>
#include <stdlib.h>
#include <getopt.h>  

#include <argparse.h>

#include "urlfile.hpp"

int main(int argc, const char** argv)
{
	static const char *const usage[] = {
		"urlopen [options] <filename>",
		NULL,
		NULL,
	};
	bool print_url = false;
	char* c_fname = NULL;
	argparse_option options[] = {
		OPT_HELP(),
		OPT_GROUP("Options"),
		OPT_BOOLEAN('p', "print-url", &print_url, "Display the url and quit"),
		OPT_END()
	};

	argparse ap;
	argparse_init(&ap, options, usage, 0);
	argc = argparse_parse(&ap, argc, argv);
	std::cout << argc << std::endl;

	int i;
	if (argc != 0) 
	{
        for (i = 0; i < argc; i++) 
		{
        	// Do nothing: just let i increment.
        }
    }
	else
	{
		std::cerr << "No filename given!" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string fname(argv[i-1]);
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