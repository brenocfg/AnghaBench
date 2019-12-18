#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
print_usage(void)
{
    fprintf(stderr,
            "Usage: jbig2dec [options] <file.jbig2>\n"
            "   or  jbig2dec [options] <global_stream> <page_stream>\n"
            "\n"
            "  When invoked with a single file, it attempts to parse it as\n"
            "  a normal jbig2 file. Invoked with two files, it treats the\n"
            "  first as the global segments, and the second as the segment\n"
            "  stream for a particular page. This is useful for examining\n"
            "  embedded streams.\n"
            "\n"
            "  available options:\n"
            "    -h --help      this usage summary\n"
            "    -q --quiet     suppress diagnostic output\n"
            "    -v --verbose   set the verbosity level\n"
            "    -d --dump      print the structure of the jbig2 file\n"
            "                   rather than explicitly decoding\n"
            "       --version   program name and version information\n"
            "       --hash      print a hash of the decoded document\n"
            "    -e --embedded  expect embedded bit stream without file header\n"
            "    -o <file>      send decoded output to <file>\n"
            "                   Defaults to the the input with a different\n"
            "                   extension. Pass '-' for stdout.\n"
            "    -t <type>      force a particular output file format\n"
#ifdef HAVE_LIBPNG
            "                   supported options are 'png' and 'pbm'\n"
#else
            "                   the only supported option is 'pbm'\n"
#endif
            "\n");

    return 1;
}