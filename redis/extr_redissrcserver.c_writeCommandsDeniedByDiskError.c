#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ saveparamslen; scalar_t__ lastbgsave_status; scalar_t__ aof_state; scalar_t__ aof_last_write_status; scalar_t__ stop_writes_on_bgsave_err; } ;

/* Variables and functions */
 scalar_t__ AOF_OFF ; 
 scalar_t__ C_ERR ; 
 int DISK_ERROR_TYPE_AOF ; 
 int DISK_ERROR_TYPE_NONE ; 
 int DISK_ERROR_TYPE_RDB ; 
 TYPE_1__ server ; 

int writeCommandsDeniedByDiskError(void) {
    if (server.stop_writes_on_bgsave_err &&
        server.saveparamslen > 0 &&
        server.lastbgsave_status == C_ERR)
    {
        return DISK_ERROR_TYPE_RDB;
    } else if (server.aof_state != AOF_OFF &&
               server.aof_last_write_status == C_ERR)
    {
        return DISK_ERROR_TYPE_AOF;
    } else {
        return DISK_ERROR_TYPE_NONE;
    }
}