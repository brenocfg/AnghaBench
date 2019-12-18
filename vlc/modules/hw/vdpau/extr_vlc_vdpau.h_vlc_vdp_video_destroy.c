#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* destroy ) (TYPE_3__*) ;} ;
struct TYPE_4__ {TYPE_3__ context; } ;
typedef  TYPE_1__ vlc_vdp_video_field_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static inline void vlc_vdp_video_destroy(vlc_vdp_video_field_t *f)
{
    f->context.destroy(&f->context);
}