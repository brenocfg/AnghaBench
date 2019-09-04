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
struct TYPE_3__ {scalar_t__ unicode; } ;
typedef  TYPE_1__ COMBOEX_INFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,char*,char*) ; 

__attribute__((used)) static BOOL COMBOEX_SetUnicodeFormat (COMBOEX_INFO *infoPtr, BOOL value)
{
    BOOL bTemp = infoPtr->unicode;

    TRACE("to %s, was %s\n", value ? "TRUE":"FALSE", bTemp ? "TRUE":"FALSE");

    infoPtr->unicode = value;

    return bTemp;
}