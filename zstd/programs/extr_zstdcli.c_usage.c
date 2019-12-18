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
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int /*<<< orphan*/  ZSTDCLI_CLEVEL_DEFAULT ; 
 int /*<<< orphan*/  ZSTDCLI_CLEVEL_MAX ; 

__attribute__((used)) static int usage(const char* programName)
{
    DISPLAY( "Usage : \n");
    DISPLAY( "      %s [args] [FILE(s)] [-o file] \n", programName);
    DISPLAY( "\n");
    DISPLAY( "FILE    : a filename \n");
    DISPLAY( "          with no FILE, or when FILE is - , read standard input\n");
    DISPLAY( "Arguments : \n");
#ifndef ZSTD_NOCOMPRESS
    DISPLAY( " -#     : # compression level (1-%d, default: %d) \n", ZSTDCLI_CLEVEL_MAX, ZSTDCLI_CLEVEL_DEFAULT);
#endif
#ifndef ZSTD_NODECOMPRESS
    DISPLAY( " -d     : decompression \n");
#endif
    DISPLAY( " -D file: use `file` as Dictionary \n");
    DISPLAY( " -o file: result stored into `file` (only if 1 input file) \n");
    DISPLAY( " -f     : overwrite output without prompting and (de)compress links \n");
    DISPLAY( "--rm    : remove source file(s) after successful de/compression \n");
    DISPLAY( " -k     : preserve source file(s) (default) \n");
    DISPLAY( " -h/-H  : display help/long help and exit \n");
    return 0;
}