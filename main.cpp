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
	int print_domain = 0;
	const char* browser = NULL;
	argparse_option options[] = {
		OPT_HELP(),
		OPT_BOOLEAN('v', "version", &print_version, "Display the version and exit."),
		OPT_GROUP("Options"),
		OPT_BOOLEAN('p', "print-url", &print_url, "Display the url and exit."),
		OPT_BOOLEAN(NULL, "print-domain", &print_domain, "Display the domain name."),
		OPT_STRING(NULL, "private-window", &browser, "Open the url in a private/incognito window using <browser>. Acceptable values are 'CHROME' and 'FIREFOX'."),
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
	urlopen::UrlFile uf(fname);

	if (print_url)
	{
		std::cout << uf.get_url() << std::endl;
	}
	else if (print_domain)
	{
		std::cout << uf.get_domain() << std::endl;
	}
	else if (browser)
	{
		std::string s(browser);
		urlopen::Browser b_type;
		if (s == "FIREFOX")
		{
			b_type = urlopen::Browser::FIREFOX;
		}
		else if (s == "CHROME")
		{
			b_type = urlopen::Browser::CHROME;
		}
		else
		{
			std::cerr << "Invalid option for --private-window: " << s << std::endl;
			std::cerr << "Valid options are 'CHROME' and 'FIREFOX'" << std::endl;
			exit(EXIT_FAILURE);
		}

		std::cout << "Cool" << std::endl;
		uf.open_private_window(b_type);
	}
	else
	{
		uf.open_shortcut();
	}
}