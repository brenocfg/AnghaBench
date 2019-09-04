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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPWINE_MLD ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  MMDRV_Message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DWORD	MMDRV_Close(LPWINE_MLD mld, UINT wMsg)
{
    TRACE("(%p, %04x)\n", mld, wMsg);
    return MMDRV_Message(mld, wMsg, 0L, 0L);
}