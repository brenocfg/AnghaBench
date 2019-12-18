#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ i_cmd_w; scalar_t__ i_file_size; scalar_t__ i_file_max; scalar_t__ i_cmd_max; } ;
typedef  TYPE_4__ ts_storage_t ;
struct TYPE_9__ {TYPE_1__* p_block; } ;
struct TYPE_10__ {TYPE_2__ send; } ;
struct TYPE_12__ {scalar_t__ i_type; TYPE_3__ u; } ;
typedef  TYPE_5__ ts_cmd_t ;
struct TYPE_8__ {int i_buffer; } ;

/* Variables and functions */
 scalar_t__ C_SEND ; 

__attribute__((used)) static bool TsStorageIsFull( ts_storage_t *p_storage, const ts_cmd_t *p_cmd )
{
    if( p_cmd && p_cmd->i_type == C_SEND && p_storage->i_cmd_w > 0 )
    {
        size_t i_size = sizeof(*p_cmd->u.send.p_block) + p_cmd->u.send.p_block->i_buffer;

        if( p_storage->i_file_size + i_size >= p_storage->i_file_max )
            return true;
    }
    return p_storage->i_cmd_w >= p_storage->i_cmd_max;
}