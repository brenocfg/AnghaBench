#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {scalar_t__ uNumTools; } ;
struct TYPE_7__ {scalar_t__ cbSize; } ;
typedef  TYPE_1__ TTTOOLINFOW ;
typedef  TYPE_2__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TOOLTIPS_CopyInfoT (TYPE_2__ const*,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TTTOOLINFOW_V1_SIZE ; 

__attribute__((used)) static LRESULT
TOOLTIPS_EnumToolsT (const TOOLTIPS_INFO *infoPtr, UINT uIndex, TTTOOLINFOW *ti,
                     BOOL isW)
{
    if (!ti || ti->cbSize < TTTOOLINFOW_V1_SIZE)
	return FALSE;
    if (uIndex >= infoPtr->uNumTools)
	return FALSE;

    TRACE("index=%u\n", uIndex);

    TOOLTIPS_CopyInfoT (infoPtr, uIndex, ti, isW);

    return TRUE;
}