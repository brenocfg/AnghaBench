#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_11__ {scalar_t__ i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_2__ block_t ;
struct TYPE_12__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  blocksize; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 scalar_t__ AccessPoll (TYPE_1__*) ; 
 TYPE_2__* block_Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *ReadBlock (stream_t *access, bool *restrict eof)
{
    access_sys_t *sys = access->p_sys;

    if (AccessPoll (access))
        return NULL;

    block_t *block = block_Alloc (sys->blocksize);
    if (unlikely(block == NULL))
        return NULL;

    ssize_t val = v4l2_read (sys->fd, block->p_buffer, block->i_buffer);
    if (val < 0)
    {
        block_Release (block);
        msg_Err (access, "cannot read buffer: %s", vlc_strerror_c(errno));
        *eof = true;
        return NULL;
    }

    block->i_buffer = val;
    return block;
}