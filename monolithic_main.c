
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif
#include <errno.h>

#define BUILD_MONOLITHIC 1
#include "monolithic_examples.h"


typedef int tool_f();
typedef int tool_fa(int argc, const char** argv);

static int usage();


static struct cmd_info
{
	const char* cmd;
	union
	{
		tool_f* f;
		tool_fa* fa;
	} f;
} commands[] = {
	{ "example", {.fa = mujs_example_main } },
	{ "prettyprint", {.fa = mujs_prettyprint_main } },

	{ "?", {.f = usage } },
	{ "h", {.f = usage } },
	{ "help", {.f = usage } },
	{ "-?", {.f = usage } },
	{ "-h", {.f = usage } },
	{ "--help", {.f = usage } },
};


static void help(void)
{
	fprintf(stderr, "Commands:\n");
	for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
	{
		struct cmd_info el = commands[i];
		fprintf(stderr, "  %s\n", el.cmd);
	}
}


static int usage()
{
	fprintf(stderr, "Usage: mujs_demo [command]\n");
	help();
	return 1;
}


static int parse(const char* source, int argc, const char** argv)
{
	if (source)
	{
		for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
		{
			struct cmd_info el = commands[i];
			size_t cmd_len = strlen(el.cmd);
			char sentinel = 0;

			if (strlen(source) >= cmd_len)
				sentinel = source[cmd_len];

			if (strncmp(source, el.cmd, cmd_len) == 0 && (sentinel == 0 || isspace(sentinel)))
			{
				return el.f.fa(argc, argv);
			}
		}

		fprintf(stderr, "Unknown command '%s'.\n\nUse 'h' or 'help' command to get a list of supported commands.\n", source);
		return 1;
	}
	else
	{
		return usage();
	}
}

int main(int argc, const char** argv)
{
	return parse(argv[1], argc - 1, argv + 1);
}

