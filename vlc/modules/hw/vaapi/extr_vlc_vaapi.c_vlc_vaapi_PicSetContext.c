#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vaapi_pic_context {int /*<<< orphan*/  s; } ;
struct TYPE_4__ {int /*<<< orphan*/ * context; } ;
typedef  TYPE_1__ picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VAAPI_CHROMA (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
vlc_vaapi_PicSetContext(picture_t *pic, struct vaapi_pic_context *vaapi_ctx)
{
    ASSERT_VAAPI_CHROMA(pic);
    assert(pic->context == NULL);

    pic->context = &vaapi_ctx->s;
}