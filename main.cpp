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

	// If this is a bool, the parser doesn't handle it correctly every time.
	int print_version = 0;
	bool print_url = false;
	char* c_fname = NULL;
	argparse_option options[] = {
		OPT_HELP(),
		OPT_BOOLEAN('v', "version", &print_version, "Display the version and exit"),
		OPT_GROUP("Options"),
		OPT_BOOLEAN('p', "print-url", &print_url, "Display the url and exit"),
		OPT_END()
	};

	argparse ap;
	argparse_init(&ap, options, usage, 0);
	argc = argparse_parse(&ap, argc, argv);

	if (print_version)
	{
		std::string version = URLOPEN_VERSION;
		std::cout << version << std::endl;
		exit(EXIT_SUCCESS);
	}

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