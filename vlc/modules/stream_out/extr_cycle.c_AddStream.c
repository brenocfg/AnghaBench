#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  p_next; int /*<<< orphan*/  p_sout; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_7__ {int /*<<< orphan*/ * stream; TYPE_3__* first; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
struct TYPE_8__ {int /*<<< orphan*/  fmt; int /*<<< orphan*/  id; struct TYPE_8__* next; } ;
typedef  TYPE_3__ sout_stream_id_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/ * sout_StreamChainNew (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sout_StreamIdAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int AddStream(sout_stream_t *stream, char *chain)
{
    sout_stream_sys_t *sys = stream->p_sys;

    msg_Dbg(stream, "starting new phase \"%s\"", chain);
    /* TODO format */
    sys->stream = sout_StreamChainNew(stream->p_sout, chain,
                                      stream->p_next, NULL);
    if (sys->stream == NULL)
        return -1;

    for (sout_stream_id_sys_t *id = sys->first; id != NULL; id = id->next)
        id->id = sout_StreamIdAdd(sys->stream, &id->fmt);

    return 0;
}