#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sout_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void Del( sout_stream_t *p_stream, void *id )
{
    msg_Dbg( p_stream, "Removing a stream" );
    /* NOTE: id should be freed by the input manager, not here. */
    (void) id;
}