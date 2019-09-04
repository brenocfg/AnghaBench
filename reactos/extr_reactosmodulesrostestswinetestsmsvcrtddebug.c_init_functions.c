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
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * pMSVCRTD_operator_delete ; 
 int /*<<< orphan*/ * pMSVCRTD_operator_new_dbg ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL init_functions(void)
{
  HMODULE hModule = LoadLibraryA("msvcrtd.dll");

  if (!hModule) {
    trace("LoadLibraryA failed to load msvcrtd.dll with GLE=%d\n", GetLastError());
    return FALSE;
  }

  if (sizeof(void *) > sizeof(int))  /* 64-bit has a different mangled name */
  {
      SET(pMSVCRTD_operator_new_dbg, "??2@YAPEAX_KHPEBDH@Z");
      SET(pMSVCRTD_operator_delete, "??3@YAXPEAX@Z");
  }
  else
  {
      SET(pMSVCRTD_operator_new_dbg, "??2@YAPAXIHPBDH@Z");
      SET(pMSVCRTD_operator_delete, "??3@YAXPAX@Z");
  }

  if (pMSVCRTD_operator_new_dbg == NULL)
    return FALSE;

  return TRUE;
}