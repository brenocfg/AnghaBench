#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int i_entries; } ;
struct TYPE_11__ {TYPE_7__ palette; scalar_t__ y_end; scalar_t__ x_end; scalar_t__ y_start; scalar_t__ x_start; } ;
typedef  TYPE_2__ vlc_spu_highlight_t ;
struct TYPE_12__ {TYPE_4__* p; } ;
typedef  TYPE_3__ spu_t ;
struct TYPE_14__ {scalar_t__ i_entries; } ;
struct TYPE_10__ {scalar_t__ height; scalar_t__ width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_13__ {int force_crop; TYPE_6__ palette; TYPE_1__ crop; int /*<<< orphan*/  lock; } ;
typedef  TYPE_4__ spu_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_6__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void UpdateSPU(spu_t *spu, const vlc_spu_highlight_t *hl)
{
    spu_private_t *sys = spu->p;

    vlc_mutex_assert(&sys->lock);

    sys->palette.i_entries = 0;
    sys->force_crop = false;

    if (hl == NULL)
        return;

    sys->force_crop = true;
    sys->crop.x      = hl->x_start;
    sys->crop.y      = hl->y_start;
    sys->crop.width  = hl->x_end - sys->crop.x;
    sys->crop.height = hl->y_end - sys->crop.y;

    if (hl->palette.i_entries == 4) /* XXX: Only DVD palette for now */
        memcpy(&sys->palette, &hl->palette, sizeof(sys->palette));

    msg_Dbg(spu, "crop: %i,%i,%i,%i, palette forced: %i",
            sys->crop.x, sys->crop.y,
            sys->crop.width, sys->crop.height,
            sys->palette.i_entries);
}