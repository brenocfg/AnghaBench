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
typedef  int uint8_t ;
struct TYPE_10__ {TYPE_2__* p_stream; } ;
struct TYPE_11__ {TYPE_3__ u; } ;
typedef  TYPE_4__ ts_pid_t ;
typedef  int /*<<< orphan*/  tail ;
struct TYPE_12__ {int i_buffer; struct TYPE_12__* p_next; } ;
typedef  TYPE_5__ block_t ;
struct TYPE_8__ {TYPE_5__* p_data; } ;
struct TYPE_9__ {TYPE_1__ gather; } ;

/* Variables and functions */
 int block_ChainExtract (TYPE_5__*,int*,int) ; 

__attribute__((used)) static int IsVideoEnd( ts_pid_t *p_pid )
{
    /* jump to near end of PES packet */
    block_t *p = p_pid->u.p_stream->gather.p_data;
    if( !p || !p->p_next )
        return 0;
    while( p->p_next->p_next )
        p = p->p_next;
    if( p->p_next->i_buffer > 4)
        p = p->p_next;

    /* extract last bytes */
    uint8_t tail[ 188 ];
    const int i_tail = block_ChainExtract( p, tail, sizeof( tail ) );
    if( i_tail < 4 )
        return 0;

    /* check for start code at end */
    return ( tail[ i_tail - 4 ] == 0 && tail[ i_tail - 3 ] == 0 && tail[ i_tail - 2 ] == 1 &&
             ( tail[ i_tail - 1 ] == 0xb7 ||  tail[ i_tail - 1 ] == 0x0a ) );
}