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
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hSetupAPI ; 
 void* pSetupEnumInfSectionsA ; 
 void* pSetupGetFieldA ; 
 void* pSetupGetFieldW ; 

__attribute__((used)) static void init_function_pointers(void)
{
    hSetupAPI = GetModuleHandleA("setupapi.dll");

    /* Nice, pSetupGetField is either A or W depending on the Windows version! The actual test
     * takes care of this difference */
    pSetupGetFieldA = (void *)GetProcAddress(hSetupAPI, "pSetupGetField");
    pSetupGetFieldW = (void *)GetProcAddress(hSetupAPI, "pSetupGetField");
    pSetupEnumInfSectionsA = (void *)GetProcAddress(hSetupAPI, "SetupEnumInfSectionsA" );
}