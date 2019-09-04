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
struct TYPE_3__ {scalar_t__ iVersion; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  int LRESULT ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ COMCTL32_VERSION ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 

__attribute__((used)) static LRESULT
REBAR_SetVersion (REBAR_INFO *infoPtr, INT iVersion)
{
    INT iOldVersion = infoPtr->iVersion;

    if (iVersion > COMCTL32_VERSION)
	return -1;

    infoPtr->iVersion = iVersion;

    TRACE("new version %d\n", iVersion);

    return iOldVersion;
}