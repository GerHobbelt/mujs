
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int mujs_example_main(int argc, const char** argv);
int mujs_prettyprint_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
