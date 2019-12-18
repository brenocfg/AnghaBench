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
 int COMPRESSIBILITY_DEFAULT ; 
 unsigned int DEFAULT_CLEVEL ; 
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 unsigned int NBLOOPS ; 
 scalar_t__ kSampleSizeDefault ; 
 int /*<<< orphan*/  usage (char const*) ; 

__attribute__((used)) static int usage_advanced(const char* exename)
{
    usage(exename);
    DISPLAY( "\nAdvanced options :\n");
    DISPLAY( " -b#    : test only function # \n");
    DISPLAY( " -l#    : benchmark functions at that compression level (default : %i)\n", DEFAULT_CLEVEL);
    DISPLAY( "--zstd= : custom parameter selection. Format same as zstdcli \n");
    DISPLAY( " -P#    : sample compressibility (default : %.1f%%)\n", COMPRESSIBILITY_DEFAULT * 100);
    DISPLAY( " -B#    : sample size (default : %u)\n", (unsigned)kSampleSizeDefault);
    DISPLAY( " -i#    : iteration loops [1-9](default : %i)\n", NBLOOPS);
    return 0;
}