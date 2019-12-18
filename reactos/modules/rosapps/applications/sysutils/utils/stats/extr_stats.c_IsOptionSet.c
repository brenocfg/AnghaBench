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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MAX_OPTIONS ; 
 int /*<<< orphan*/ * Options ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _tcscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

BOOLEAN
IsOptionSet(TCHAR *Option)
{
  int i;
  for(i = 0; i < MAX_OPTIONS; i++)
  {
    if(!Options[i])
      continue;

    if(!_tcscmp(Options[i], Option))
      return TRUE;
  }
  return FALSE;
}