#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Flags; scalar_t__ lpfnHook; } ;
typedef  TYPE_1__ CHOOSECOLORW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CC_ENABLEHOOK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL CC_HookCallChk( const CHOOSECOLORW *lpcc )
{
 if (lpcc)
  if(lpcc->Flags & CC_ENABLEHOOK)
   if (lpcc->lpfnHook)
    return TRUE;
 return FALSE;
}