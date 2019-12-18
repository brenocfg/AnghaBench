#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  p_next; } ;
typedef  TYPE_1__ sout_stream_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int sout_StreamIdSend (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Send( sout_stream_t *p_stream, void *id, block_t *p_buffer )
{
    return sout_StreamIdSend( p_stream->p_next, id, p_buffer );
}