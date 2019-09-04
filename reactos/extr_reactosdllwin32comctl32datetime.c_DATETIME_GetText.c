#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
struct TYPE_4__ {int nrFields; } ;
typedef  scalar_t__* LPWSTR ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ DATETIME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  DATETIME_ReturnTxt (TYPE_1__ const*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcatW (scalar_t__*,scalar_t__*) ; 
 scalar_t__ strlenW (scalar_t__*) ; 

__attribute__((used)) static INT
DATETIME_GetText (const DATETIME_INFO *infoPtr, INT count, LPWSTR dst)
{
    WCHAR buf[80];
    int i;

    if (!dst || (count <= 0)) return 0;

    dst[0] = 0;
    for (i = 0; i < infoPtr->nrFields; i++)
    {
        DATETIME_ReturnTxt(infoPtr, i, buf, ARRAY_SIZE(buf));
        if ((strlenW(dst) + strlenW(buf)) < count)
            strcatW(dst, buf);
        else break;
    }
    return strlenW(dst);
}