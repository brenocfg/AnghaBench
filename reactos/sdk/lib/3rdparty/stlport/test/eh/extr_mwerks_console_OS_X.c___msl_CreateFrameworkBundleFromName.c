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
typedef  scalar_t__ OSErr ;
typedef  int /*<<< orphan*/  FSRef ;
typedef  int /*<<< orphan*/ * CFURLRef ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  CFBundleRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFBundleCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFURLCreateCopyAppendingPathComponent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CFURLCreateFromFSRef (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FSFindFolder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kCFAllocatorSystemDefault ; 
 int /*<<< orphan*/  kFrameworksFolderType ; 
 int /*<<< orphan*/  kOnAppropriateDisk ; 
 scalar_t__ noErr ; 

__attribute__((used)) static OSErr __msl_CreateFrameworkBundleFromName(CFStringRef theFrameworkName,
    CFBundleRef *theBundle)
  {
    OSErr theErr;
    FSRef theRef;
    CFURLRef theFrameworkURL;
    CFURLRef theBundleURL;

    /* Find the folder containing all the frameworks */
    theErr = FSFindFolder(kOnAppropriateDisk, kFrameworksFolderType, false, &theRef);

    if (theErr == noErr)
    {
      /* Turn the framework folder FSRef into a CFURL */
      theFrameworkURL = CFURLCreateFromFSRef(kCFAllocatorSystemDefault, &theRef);

      if (theFrameworkURL != NULL)
      {
        /* Create a CFURL pointing to the desired framework */
        theBundleURL = CFURLCreateCopyAppendingPathComponent(kCFAllocatorSystemDefault,
          theFrameworkURL, theFrameworkName, false);

        CFRelease(theFrameworkURL);

        if (theBundleURL != NULL)
        {
          /* Turn the CFURL into a bundle reference */
          *theBundle = CFBundleCreate(kCFAllocatorSystemDefault, theBundleURL);

          CFRelease(theBundleURL);
        }
      }
    }

    return theErr;
  }