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
 int /*<<< orphan*/  COMPRESSIBILITY_DEFAULT ; 
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int /*<<< orphan*/  SEED_DEFAULT ; 
 int /*<<< orphan*/  SIZE_DEFAULT ; 

__attribute__((used)) static int usage(const char* programName)
{
    DISPLAY( "Compressible data generator\n");
    DISPLAY( "Usage :\n");
    DISPLAY( "      %s [args]\n", programName);
    DISPLAY( "\n");
    DISPLAY( "Arguments :\n");
    DISPLAY( " -g#    : generate # data (default:%i)\n", SIZE_DEFAULT);
    DISPLAY( " -s#    : Select seed (default:%i)\n", SEED_DEFAULT);
    DISPLAY( " -P#    : Select compressibility in %% (default:%i%%)\n",
                        COMPRESSIBILITY_DEFAULT);
    DISPLAY( " -h     : display help and exit\n");
    return 0;
}