#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  sout_access_out_t ;
struct TYPE_4__ {struct TYPE_4__* p_next; scalar_t__ i_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (TYPE_1__*) ; 

__attribute__((used)) static ssize_t Write( sout_access_out_t *p_access, block_t *p_buffer )
{
    size_t i_write = 0;
    block_t *b = p_buffer;

    while( b )
    {
        i_write += b->i_buffer;

        b = b->p_next;
    }

    block_ChainRelease( p_buffer );

    (void)p_access;
    return i_write;
}