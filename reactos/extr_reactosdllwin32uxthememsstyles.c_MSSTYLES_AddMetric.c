#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* metrics; } ;
struct TYPE_8__ {int iPrimitiveType; int iPropertyId; struct TYPE_8__* next; int /*<<< orphan*/  origin; int /*<<< orphan*/  dwValueLen; int /*<<< orphan*/  lpValue; } ;
typedef  int /*<<< orphan*/  THEME_PROPERTY ;
typedef  TYPE_1__* PTHEME_PROPERTY ;
typedef  TYPE_2__* PTHEME_FILE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* MSSTYLES_FindMetric (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  PO_GLOBAL ; 

__attribute__((used)) static PTHEME_PROPERTY MSSTYLES_AddMetric(PTHEME_FILE tf, int iPropertyPrimitive, int iPropertyId, LPCWSTR lpValue, DWORD dwValueLen)
{
    PTHEME_PROPERTY cur = MSSTYLES_FindMetric(tf, iPropertyPrimitive, iPropertyId);
    /* Should duplicate properties overwrite the original, or be ignored? */
    if(cur) return cur;

    cur = HeapAlloc(GetProcessHeap(), 0, sizeof(THEME_PROPERTY));
    cur->iPrimitiveType = iPropertyPrimitive;
    cur->iPropertyId = iPropertyId;
    cur->lpValue = lpValue;
    cur->dwValueLen = dwValueLen;

    cur->origin = PO_GLOBAL;

    cur->next = tf->metrics;
    tf->metrics = cur;
    return cur;
}