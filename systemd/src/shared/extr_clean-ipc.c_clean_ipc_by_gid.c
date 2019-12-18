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
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  UID_INVALID ; 
 int clean_ipc_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int clean_ipc_by_gid(gid_t gid) {
        return clean_ipc_internal(UID_INVALID, gid, true);
}