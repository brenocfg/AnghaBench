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
struct TYPE_4__ {scalar_t__ refcount; } ;
typedef  TYPE_1__ Jbig2Image ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  jbig2_image_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
jbig2_image_release(Jbig2Ctx *ctx, Jbig2Image *image)
{
    if (image == NULL)
        return;
    image->refcount--;
    if (image->refcount == 0)
        jbig2_image_free(ctx, image);
}