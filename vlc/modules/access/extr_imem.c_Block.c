#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ p_sys; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  cookie; int /*<<< orphan*/  data; int /*<<< orphan*/  (* release ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,void*) ;scalar_t__ (* get ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,size_t*,void**) ;} ;
struct TYPE_10__ {TYPE_1__ source; } ;
typedef  TYPE_3__ imem_sys_t ;
struct TYPE_11__ {int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 TYPE_4__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,size_t*,void**) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,void*) ; 

__attribute__((used)) static block_t *Block(stream_t *access, bool *restrict eof)
{
    imem_sys_t *sys = (imem_sys_t*)access->p_sys;

    unsigned flags;
    size_t buffer_size;
    void   *buffer;

    if (sys->source.get(sys->source.data, sys->source.cookie,
                        NULL, NULL, &flags, &buffer_size, &buffer)) {
        *eof = true;
        return NULL;
    }

    block_t *block = NULL;
    if (buffer_size > 0) {
        block = block_Alloc(buffer_size);
        if (block)
            memcpy(block->p_buffer, buffer, buffer_size);
    }

    sys->source.release(sys->source.data, sys->source.cookie,
                        buffer_size, buffer);
    return block;
}