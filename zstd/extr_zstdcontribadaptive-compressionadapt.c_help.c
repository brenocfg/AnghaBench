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
 char const* DEFAULT_COMPRESSION_LEVEL ; 
 int /*<<< orphan*/  PRINT (char*,...) ; 
 char const* ZSTD_maxCLevel () ; 

__attribute__((used)) static void help(const char* progPath)
{
    PRINT("Usage:\n");
    PRINT("  %s [options] [file(s)]\n", progPath);
    PRINT("\n");
    PRINT("Options:\n");
    PRINT("  -oFILE : specify the output file name\n");
    PRINT("  -i#    : provide initial compression level -- default %d, must be in the range [L, U] where L and U are bound values (see below for defaults)\n", DEFAULT_COMPRESSION_LEVEL);
    PRINT("  -h     : display help/information\n");
    PRINT("  -f     : force the compression level to stay constant\n");
    PRINT("  -c     : force write to stdout\n");
    PRINT("  -p     : hide progress bar\n");
    PRINT("  -q     : quiet mode -- do not show progress bar or other information\n");
    PRINT("  -l#    : provide lower bound for compression level -- default 1\n");
    PRINT("  -u#    : provide upper bound for compression level -- default %u\n", ZSTD_maxCLevel());
}