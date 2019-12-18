#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {TYPE_2__* p_sys; int /*<<< orphan*/  pf_send; int /*<<< orphan*/  pf_del; int /*<<< orphan*/  pf_add; TYPE_3__* p_cfg; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_8__ {scalar_t__ period; int /*<<< orphan*/ * start; int /*<<< orphan*/ * next; int /*<<< orphan*/  clock; int /*<<< orphan*/ * last; int /*<<< orphan*/ * first; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
typedef  int /*<<< orphan*/  sout_cycle_t ;
struct TYPE_9__ {char* psz_value; int /*<<< orphan*/  psz_name; struct TYPE_9__* p_next; } ;
typedef  TYPE_3__ config_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  Add ; 
 int /*<<< orphan*/  AppendPhase (int /*<<< orphan*/ ***,scalar_t__,char const*) ; 
 int /*<<< orphan*/  Del ; 
 scalar_t__ ParseTime (char*) ; 
 int /*<<< orphan*/  Send ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  get_dts ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Open(vlc_object_t *obj)
{
    sout_stream_t *stream = (sout_stream_t *)obj;
    sout_stream_sys_t *sys = malloc(sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    sys->stream = NULL;
    sys->first = NULL;
    sys->last = NULL;
    sys->start = NULL;
    sys->clock = get_dts;

    vlc_tick_t offset = 0;
    sout_cycle_t **pp = &sys->start;
    const char *chain = "";

    for (const config_chain_t *cfg = stream->p_cfg;
         cfg != NULL;
         cfg = cfg->p_next)
    {
        if (!strcmp(cfg->psz_name, "dst"))
        {
            chain = cfg->psz_value;
        }
        else if (!strcmp(cfg->psz_name, "duration"))
        {
            vlc_tick_t t = ParseTime(cfg->psz_value);

            if (t > 0)
            {
                AppendPhase(&pp, offset, chain);
                offset += t;
            }

            chain = "";
        }
        else if (!strcmp(cfg->psz_name, "offset"))
        {
            vlc_tick_t t = ParseTime(cfg->psz_value);

            if (t > offset)
            {
                AppendPhase(&pp, offset, chain);
                offset = t;
            }

            chain = "";
        }
        else
        {
            msg_Err(stream, "unknown option \"%s\"", cfg->psz_name);
        }
    }

    if (sys->start == NULL || offset == 0)
    {
        free(sys);
        msg_Err(stream, "unknown or invalid cycle specification");
        return VLC_EGENERIC;
    }

    sys->next = sys->start;
    sys->period = offset;

    stream->pf_add = Add;
    stream->pf_del = Del;
    stream->pf_send = Send;
    stream->p_sys = sys;
    return VLC_SUCCESS;
}