#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  row ;
struct TYPE_4__ {int dwIndex; } ;
typedef  TYPE_1__ MIB_IFROW ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_DATA ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pGetIfEntry (TYPE_1__*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void testGetIfEntry(DWORD index)
{
  if (pGetIfEntry) {
    DWORD apiReturn;
    MIB_IFROW row;

    memset(&row, 0, sizeof(row));
    apiReturn = pGetIfEntry(NULL);
    if (apiReturn == ERROR_NOT_SUPPORTED) {
      skip("GetIfEntry is not supported\n");
      return;
    }
    ok(apiReturn == ERROR_INVALID_PARAMETER,
     "GetIfEntry(NULL) returned %d, expected ERROR_INVALID_PARAMETER\n",
     apiReturn);
    row.dwIndex = -1; /* hope that's always bogus! */
    apiReturn = pGetIfEntry(&row);
    ok(apiReturn == ERROR_INVALID_DATA ||
     apiReturn == ERROR_FILE_NOT_FOUND /* Vista */,
     "GetIfEntry(bogus row) returned %d, expected ERROR_INVALID_DATA or ERROR_FILE_NOT_FOUND\n",
     apiReturn);
    row.dwIndex = index;
    apiReturn = pGetIfEntry(&row);
    ok(apiReturn == NO_ERROR, 
     "GetIfEntry returned %d, expected NO_ERROR\n", apiReturn);
  }
}