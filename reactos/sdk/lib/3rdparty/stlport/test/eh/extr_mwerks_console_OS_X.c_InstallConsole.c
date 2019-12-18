#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * WritePtr ;
struct TYPE_2__ {int isLoaded; int /*<<< orphan*/ * theBundle; int /*<<< orphan*/ * theWrite; int /*<<< orphan*/ * theRead; } ;
typedef  int /*<<< orphan*/ * ReadPtr ;
typedef  scalar_t__ OSErr ;

/* Variables and functions */
 scalar_t__ CFBundleGetFunctionPointerForName (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int CFBundleLoadExecutable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFSTR (char*) ; 
 scalar_t__ __msl_CreateFrameworkBundleFromName (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_1__ __msl_os_x ; 
 scalar_t__ noErr ; 

short InstallConsole(short fd)
  {
  #pragma unused (fd)
    OSErr theErr;
    short theResult;

    theResult = -1;

    /* Start with no bundle */
    __msl_os_x.isLoaded = false;
    __msl_os_x.theBundle = NULL;
    __msl_os_x.theRead = NULL;
    __msl_os_x.theWrite = NULL;

    /* Create a bundle reference based on its name */
    theErr = __msl_CreateFrameworkBundleFromName(CFSTR("System.framework"),
      &__msl_os_x.theBundle);

    if ((theErr == noErr) && (__msl_os_x.theBundle != NULL))
    {
      theResult = 0;

      __msl_os_x.isLoaded = CFBundleLoadExecutable(__msl_os_x.theBundle);

      if (__msl_os_x.isLoaded)
      {
        /* Lookup the functions in the bundle by name */
        __msl_os_x.theRead = (ReadPtr)
          CFBundleGetFunctionPointerForName(__msl_os_x.theBundle, CFSTR("read"));
        __msl_os_x.theWrite = (WritePtr)
          CFBundleGetFunctionPointerForName(__msl_os_x.theBundle, CFSTR("write"));
      }
    }

    return theResult;
  }