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
typedef  int /*<<< orphan*/  APPHELPCACHESERVICECLASS ;

/* Variables and functions */
 int /*<<< orphan*/  CallApphelpWithImage (char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xprintf (char*) ; 

int HandleImageArg(int argc, char* argv[], int* pn, char MapItChar,
                    APPHELPCACHESERVICECLASS Service, char* ServiceName)
{
    int n = *pn;
    if (n+1 < argc)
    {
        int MapIt = argv[n][1] == MapItChar;
        CallApphelpWithImage(argv[n+1], MapIt, Service, ServiceName);
        (*pn) += 1;
        return 0;
    }
    xprintf("Error: no image name specified\n");
    return 1;
}