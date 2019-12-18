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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/ * PIP_INTERFACE_INFO ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pGetInterfaceInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void testGetInterfaceInfo(void)
{
  if (pGetInterfaceInfo) {
    DWORD apiReturn;
    ULONG len = 0;

    apiReturn = pGetInterfaceInfo(NULL, NULL);
    if (apiReturn == ERROR_NOT_SUPPORTED) {
      skip("GetInterfaceInfo is not supported\n");
      return;
    }
    ok(apiReturn == ERROR_INVALID_PARAMETER,
     "GetInterfaceInfo returned %d, expected ERROR_INVALID_PARAMETER\n",
     apiReturn);
    apiReturn = pGetInterfaceInfo(NULL, &len);
    ok(apiReturn == ERROR_INSUFFICIENT_BUFFER,
     "GetInterfaceInfo returned %d, expected ERROR_INSUFFICIENT_BUFFER\n",
     apiReturn);
    if (apiReturn == ERROR_INSUFFICIENT_BUFFER) {
      PIP_INTERFACE_INFO buf = HeapAlloc(GetProcessHeap(), 0, len);

      apiReturn = pGetInterfaceInfo(buf, &len);
      ok(apiReturn == NO_ERROR,
       "GetInterfaceInfo(buf, &dwSize) returned %d, expected NO_ERROR\n",
       apiReturn);
      HeapFree(GetProcessHeap(), 0, buf);
    }
  }
}