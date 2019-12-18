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

/* Variables and functions */
 int /*<<< orphan*/  sout_StreamIdDel (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void Del( sout_stream_t *p_stream, void *id )
{
    sout_StreamIdDel( p_stream->p_next, id );
}