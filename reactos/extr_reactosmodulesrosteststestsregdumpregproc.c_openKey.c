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
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 scalar_t__ RegCreateKeyEx (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bTheKeyIsOpen ; 
 scalar_t__ currentKeyClass ; 
 int /*<<< orphan*/  currentKeyHandle ; 
 int /*<<< orphan*/ * currentKeyName ; 
 scalar_t__ getRegClass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getRegKeyName (int /*<<< orphan*/ *) ; 

HRESULT openKey(LPTSTR stdInput)
{
  DWORD   dwDisp;
  HRESULT hRes;

  /* Sanity checks */
  if (stdInput == NULL)
    return ERROR_INVALID_PARAMETER;

  /* Get the registry class */
  currentKeyClass = getRegClass(stdInput); /* Sets global variable */
  if (currentKeyClass == (HKEY)ERROR_INVALID_PARAMETER)
    return (HRESULT)ERROR_INVALID_PARAMETER;

  /* Get the key name */
  currentKeyName = getRegKeyName(stdInput); /* Sets global variable */
  if (currentKeyName == NULL)
    return ERROR_INVALID_PARAMETER;

  hRes = RegCreateKeyEx(
          currentKeyClass,          /* Class     */
          currentKeyName,           /* Sub Key   */
          0,                        /* MUST BE 0 */
          NULL,                     /* object type */
          REG_OPTION_NON_VOLATILE,  /* option, REG_OPTION_NON_VOLATILE ... */
          KEY_ALL_ACCESS,           /* access mask, KEY_ALL_ACCESS */
          NULL,                     /* security attribute */
          &currentKeyHandle,        /* result */
          &dwDisp);                 /* disposition, REG_CREATED_NEW_KEY or
                                                    REG_OPENED_EXISTING_KEY */

  if (hRes == ERROR_SUCCESS)
    bTheKeyIsOpen = TRUE;

  return hRes;

}