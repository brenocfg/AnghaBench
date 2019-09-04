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
struct TYPE_3__ {scalar_t__ clrBk; scalar_t__ clrBtnFace; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  scalar_t__ LRESULT ;
typedef  scalar_t__ COLORREF ;

/* Variables and functions */
 scalar_t__ CLR_DEFAULT ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 

__attribute__((used)) static inline LRESULT
REBAR_GetBkColor (const REBAR_INFO *infoPtr)
{
    COLORREF clr = infoPtr->clrBk;

    if (clr == CLR_DEFAULT)
      clr = infoPtr->clrBtnFace;

    TRACE("background color 0x%06x!\n", clr);

    return clr;
}