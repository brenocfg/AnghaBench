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
struct TYPE_3__ {int iString; } ;
typedef  TYPE_1__ TBUTTON_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ HIWORD (int) ; 

__attribute__((used)) static inline BOOL
TOOLBAR_ButtonHasString(const TBUTTON_INFO *btnPtr)
{
    return HIWORD(btnPtr->iString) && btnPtr->iString != -1;
}