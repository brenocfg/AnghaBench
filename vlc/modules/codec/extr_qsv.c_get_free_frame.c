#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* work_frames; } ;
typedef  TYPE_1__ encoder_sys_t ;
struct TYPE_8__ {int used; struct TYPE_8__* next; } ;
typedef  TYPE_2__ QSVFrame ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  clear_unused_frames (TYPE_1__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_free_frame(encoder_sys_t *sys, QSVFrame **out)
{
    QSVFrame *frame, **last;

    clear_unused_frames(sys);

    frame = sys->work_frames;
    last  = &sys->work_frames;
    while (frame) {
        if (!frame->used) {
            *out = frame;
            frame->used = 1;
            return VLC_SUCCESS;
        }

        last  = &frame->next;
        frame = frame->next;
    }

    frame = calloc(1,sizeof(QSVFrame));
    if (unlikely(frame==NULL))
        return VLC_ENOMEM;
    *last = frame;

    *out = frame;
    frame->used = 1;

    return VLC_SUCCESS;
}