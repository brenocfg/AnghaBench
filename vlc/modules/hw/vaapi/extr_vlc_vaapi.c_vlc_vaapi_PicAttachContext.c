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
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_7__ {int /*<<< orphan*/  ctx; TYPE_2__* picref; } ;
struct TYPE_9__ {TYPE_1__ ctx; } ;
typedef  TYPE_3__ picture_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VAAPI_CHROMA (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_vaapi_PicSetContext (TYPE_2__*,int /*<<< orphan*/ *) ; 

void
vlc_vaapi_PicAttachContext(picture_t *pic)
{
    ASSERT_VAAPI_CHROMA(pic);
    assert(pic->p_sys != NULL);

    picture_sys_t *p_sys = pic->p_sys;
    p_sys->ctx.picref = pic;
    vlc_vaapi_PicSetContext(pic, &p_sys->ctx.ctx);
}