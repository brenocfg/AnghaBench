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
struct TYPE_5__ {TYPE_2__* context; } ;
typedef  TYPE_1__ picture_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ picture_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void PictureDestroyContext( picture_t *p_picture )
{
    picture_context_t *ctx = p_picture->context;
    if (ctx != NULL)
    {
        ctx->destroy(ctx);
        p_picture->context = NULL;
    }
}