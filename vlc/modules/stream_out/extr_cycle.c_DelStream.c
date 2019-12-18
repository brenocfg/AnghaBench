#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_6__ {int /*<<< orphan*/ * stream; TYPE_3__* first; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
struct TYPE_7__ {int /*<<< orphan*/ * id; struct TYPE_7__* next; } ;
typedef  TYPE_3__ sout_stream_id_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  sout_StreamChainDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sout_StreamIdDel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DelStream(sout_stream_t *stream)
{
    sout_stream_sys_t *sys = stream->p_sys;

    if (sys->stream == NULL)
        return;

    for (sout_stream_id_sys_t *id = sys->first; id != NULL; id = id->next)
        if (id->id != NULL)
            sout_StreamIdDel(sys->stream, id->id);

    sout_StreamChainDelete(sys->stream, NULL);
    sys->stream = NULL;
}