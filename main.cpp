#include <iostream>
#include <string>
#include <stdlib.h>
#include <getopt.h>  

#include <argparse.h>

#include "urlfile.hpp"

std::string concat_chars(int c, const char** v)
{
	std::string res = "";
	for (int i = 0; i < c; i++)
	{
		res += v[i];
	}
	return res;
}

int main(int argc, const char** argv)
{
	std::cout << concat_chars(argc, argv) << std::endl;

	bool print_url = false;
	char* c_fname = NULL;
	argparse_option options[] = {
		OPT_HELP(),
		OPT_GROUP("Options"),
		OPT_BOOLEAN('p', "print-url", &print_url, "Display the url and quit"),
		OPT_STRING('u', NULL, &c_fname, "The file name (required)"),
		OPT_END()
	};

	argparse ap;
	argparse_init(&ap, options, NULL, 0);
	argc = argparse_parse(&ap, argc, argv);

	if (!c_fname)
	{
		std::cerr << "No filename given!" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string fname(c_fname);
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