#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
struct TYPE_10__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_3__ picture_t ;
struct TYPE_8__ {int /*<<< orphan*/  original; int /*<<< orphan*/  display_pool; int /*<<< orphan*/  dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_Reset (TYPE_3__*) ; 
 TYPE_3__* picture_pool_Wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_format_CopyCropAr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

picture_t *vout_GetPicture(vout_thread_t *vout)
{
    assert(!vout->p->dummy);
    picture_t *picture = picture_pool_Wait(vout->p->display_pool);
    if (likely(picture != NULL)) {
        picture_Reset(picture);
        video_format_CopyCropAr(&picture->format, &vout->p->original);
    }
    return picture;
}