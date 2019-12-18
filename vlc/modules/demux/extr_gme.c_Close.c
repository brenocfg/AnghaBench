#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {unsigned int titlec; int /*<<< orphan*/  emu; struct TYPE_6__* titlev; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  gme_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_input_title_Delete (TYPE_2__) ; 

__attribute__((used)) static void Close (vlc_object_t *obj)
{
    demux_t *demux = (demux_t *)obj;
    demux_sys_t *sys = demux->p_sys;

    for (unsigned i = 0, n = sys->titlec; i < n; i++)
        vlc_input_title_Delete (sys->titlev[i]);
    free (sys->titlev);
    gme_delete (sys->emu);
    free (sys);
}