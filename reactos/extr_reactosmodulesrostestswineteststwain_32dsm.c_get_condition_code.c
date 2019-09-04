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
typedef  scalar_t__ TW_UINT16 ;
typedef  int /*<<< orphan*/  TW_STATUS ;
typedef  int /*<<< orphan*/  TW_IDENTITY ;

/* Variables and functions */
 int /*<<< orphan*/  DAT_STATUS ; 
 int /*<<< orphan*/  DG_CONTROL ; 
 int /*<<< orphan*/  MSG_GET ; 
 scalar_t__ TWRC_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pDSM_Entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_condition_code(TW_IDENTITY *appid, TW_IDENTITY *source, TW_STATUS *status)
{
    TW_UINT16 rc;
    rc = pDSM_Entry(appid, source, DG_CONTROL, DAT_STATUS, MSG_GET, status);
    ok(rc == TWRC_SUCCESS, "Condition code not available, rc %d\n", rc);
}