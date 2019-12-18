#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
struct TYPE_11__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_12__ {TYPE_7__* context; } ;
typedef  TYPE_2__ sout_access_out_sys_t ;
struct TYPE_13__ {scalar_t__ i_buffer; int /*<<< orphan*/  p_buffer; struct TYPE_13__* p_next; } ;
typedef  TYPE_3__ block_t ;
struct TYPE_14__ {int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVUNERROR (int) ; 
 int /*<<< orphan*/  avio_flush (TYPE_7__*) ; 
 int /*<<< orphan*/  avio_write (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  block_ChainRelease (TYPE_3__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t Write(sout_access_out_t *p_access, block_t *p_buffer)
{
    sout_access_out_sys_t *p_sys = (sout_access_out_sys_t*)p_access->p_sys;
    size_t i_write = 0;
    int val;

    while (p_buffer != NULL) {
        block_t *p_next = p_buffer->p_next;

        avio_write(p_sys->context, p_buffer->p_buffer, p_buffer->i_buffer);
        avio_flush(p_sys->context);
        if ((val = p_sys->context->error) != 0) {
            p_sys->context->error = 0; /* FIXME? */
            goto error;
        }
        i_write += p_buffer->i_buffer;

        block_Release(p_buffer);

        p_buffer = p_next;
    }

    return i_write;

error:
    msg_Err(p_access, "Wrote only %zu bytes: %s", i_write,
            vlc_strerror_c(AVUNERROR(val)));
    block_ChainRelease( p_buffer );
    return i_write;
}