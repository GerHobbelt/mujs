
#define BUILD_MONOLITHIC 1
#include "monolithic_examples.h"

#define USAGE_NAME   "misctools"

#include "monolithic_main_internal_defs.h"

MONOLITHIC_CMD_TABLE_START()
	{ "example", {.fa = mujs_example_main } },
	{ "prettyprint", {.fa = mujs_prettyprint_main } },
MONOLITHIC_CMD_TABLE_END();

#include "monolithic_main_tpl.h"
