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
typedef  int /*<<< orphan*/ * PBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  _ValidateImageBase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __ImageBase ; 

PBYTE
_GetPEImageBase (void)
{
  PBYTE pImageBase;
  pImageBase = (PBYTE) &__ImageBase;
  if (! _ValidateImageBase (pImageBase))
    return NULL;
  return pImageBase;
}