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
typedef  scalar_t__ VARTYPE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VT_ARRAY ; 
 scalar_t__ VT_BYREF ; 
 scalar_t__ VT_CLSID ; 
 scalar_t__ VT_I8 ; 
 scalar_t__ VT_LPWSTR ; 
 scalar_t__ VT_NULL ; 
 scalar_t__ VT_RECORD ; 
 scalar_t__ VT_UI8 ; 
 int /*<<< orphan*/  has_i8 ; 

__attribute__((used)) static BOOL IsValidVariantClearVT(VARTYPE vt, VARTYPE extraFlags)
{
  BOOL ret = FALSE;

  /* Only the following flags/types are valid */
  if ((vt <= VT_LPWSTR || vt == VT_RECORD || vt == VT_CLSID) &&
      vt != (VARTYPE)15 &&
      (vt < (VARTYPE)24 || vt > (VARTYPE)31) &&
      (!(extraFlags & (VT_BYREF|VT_ARRAY)) || vt > VT_NULL) &&
      (extraFlags == 0 || extraFlags == VT_BYREF || extraFlags == VT_ARRAY ||
       extraFlags == (VT_ARRAY|VT_BYREF)))
    ret = TRUE; /* ok */

  if (!has_i8 && (vt == VT_I8 || vt == VT_UI8))
    ret = FALSE; /* Old versions of oleaut32 */
  return ret;
}