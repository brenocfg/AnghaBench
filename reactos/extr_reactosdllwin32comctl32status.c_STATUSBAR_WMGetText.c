#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {TYPE_1__* parts; } ;
struct TYPE_4__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_2__ STATUS_INFO ;
typedef  scalar_t__* LPWSTR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT
STATUSBAR_WMGetText (const STATUS_INFO *infoPtr, INT size, LPWSTR buf)
{
    INT len;

    TRACE("\n");
    if (!(infoPtr->parts[0].text))
        return 0;

    len = strlenW (infoPtr->parts[0].text);

    if (!size)
        return len;
    else if (size > len) {
        strcpyW (buf, infoPtr->parts[0].text);
	return len;
    }
    else {
        memcpy (buf, infoPtr->parts[0].text, (size - 1) * sizeof(WCHAR));
        buf[size - 1] = 0;
        return size - 1;
    }
}