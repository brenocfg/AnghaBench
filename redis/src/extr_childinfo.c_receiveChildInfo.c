#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {scalar_t__ magic; scalar_t__ process_type; int /*<<< orphan*/  cow_size; } ;
struct TYPE_3__ {int* child_info_pipe; TYPE_2__ child_info_data; int /*<<< orphan*/  stat_module_cow_bytes; int /*<<< orphan*/  stat_aof_cow_bytes; int /*<<< orphan*/  stat_rdb_cow_bytes; } ;

/* Variables and functions */
 scalar_t__ CHILD_INFO_MAGIC ; 
 scalar_t__ CHILD_INFO_TYPE_AOF ; 
 scalar_t__ CHILD_INFO_TYPE_MODULE ; 
 scalar_t__ CHILD_INFO_TYPE_RDB ; 
 scalar_t__ read (int,TYPE_2__*,scalar_t__) ; 
 TYPE_1__ server ; 

void receiveChildInfo(void) {
    if (server.child_info_pipe[0] == -1) return;
    ssize_t wlen = sizeof(server.child_info_data);
    if (read(server.child_info_pipe[0],&server.child_info_data,wlen) == wlen &&
        server.child_info_data.magic == CHILD_INFO_MAGIC)
    {
        if (server.child_info_data.process_type == CHILD_INFO_TYPE_RDB) {
            server.stat_rdb_cow_bytes = server.child_info_data.cow_size;
        } else if (server.child_info_data.process_type == CHILD_INFO_TYPE_AOF) {
            server.stat_aof_cow_bytes = server.child_info_data.cow_size;
        } else if (server.child_info_data.process_type == CHILD_INFO_TYPE_MODULE) {
            server.stat_module_cow_bytes = server.child_info_data.cow_size;
        }
    }
}