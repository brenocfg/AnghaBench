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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pGetNumberOfInterfaces (scalar_t__*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void testGetNumberOfInterfaces(void)
{
  if (pGetNumberOfInterfaces) {
    DWORD apiReturn, numInterfaces;

    /* Crashes on Vista */
    if (0) {
      apiReturn = pGetNumberOfInterfaces(NULL);
      if (apiReturn == ERROR_NOT_SUPPORTED)
        return;
      ok(apiReturn == ERROR_INVALID_PARAMETER,
       "GetNumberOfInterfaces(NULL) returned %d, expected ERROR_INVALID_PARAMETER\n",
       apiReturn);
    }

    apiReturn = pGetNumberOfInterfaces(&numInterfaces);
    if (apiReturn == ERROR_NOT_SUPPORTED) {
      skip("GetNumberOfInterfaces is not supported\n");
      return;
    }
    ok(apiReturn == NO_ERROR,
     "GetNumberOfInterfaces returned %d, expected 0\n", apiReturn);
  }
}