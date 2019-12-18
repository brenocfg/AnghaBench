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
 scalar_t__ VT_NULL ; 
 scalar_t__ VT_RESERVED ; 
 scalar_t__ VT_VECTOR ; 
 scalar_t__ VT_VOID ; 

__attribute__((used)) static BOOL IsValidVariantCopyIndVT(VARTYPE vt, VARTYPE extraFlags)
{
  BOOL ret = FALSE;

  if ((extraFlags & VT_ARRAY) ||
     (vt > VT_NULL && vt != (VARTYPE)15 && vt < VT_VOID &&
     !(extraFlags & (VT_VECTOR|VT_RESERVED))))
  {
    ret = TRUE; /* ok */
  }
  return ret;
}