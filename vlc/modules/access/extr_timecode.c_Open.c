#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  es_format_t ;
struct TYPE_6__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; TYPE_2__* p_sys; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {int /*<<< orphan*/  next_time; int /*<<< orphan*/  date; int /*<<< orphan*/  es; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Demux ; 
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  VLC_CODEC_ITU_T140 ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_0 ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ var_InheritURational (TYPE_1__*,unsigned int*,unsigned int*,char*) ; 
 TYPE_2__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int Open (vlc_object_t *obj)
{
    demux_t *demux = (demux_t *)obj;
    if (demux->out == NULL)
        return VLC_EGENERIC;

    demux_sys_t *sys = vlc_obj_malloc(obj, sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    es_format_t fmt;
    es_format_Init (&fmt, SPU_ES, VLC_CODEC_ITU_T140);
    sys->es = es_out_Add (demux->out, &fmt);

    unsigned num, den;
    if (var_InheritURational (demux, &num, &den, "timecode-fps")
     || !num || !den)
    {
        msg_Err (demux, "invalid frame rate");
        return VLC_EGENERIC;
    }

    date_Init (&sys->date, num, den);
    date_Set (&sys->date, VLC_TICK_0);
    sys->next_time = VLC_TICK_INVALID;

    demux->p_sys = sys;
    demux->pf_demux   = Demux;
    demux->pf_control = Control;
    return VLC_SUCCESS;
}