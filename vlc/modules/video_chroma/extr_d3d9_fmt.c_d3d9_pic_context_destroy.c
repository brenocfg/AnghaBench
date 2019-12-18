#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct d3d9_pic_context {int /*<<< orphan*/  picsys; } ;
typedef  int /*<<< orphan*/  picture_context_t ;

/* Variables and functions */
 struct d3d9_pic_context* D3D9_PICCONTEXT_FROM_PICCTX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseD3D9PictureSys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct d3d9_pic_context*) ; 

void d3d9_pic_context_destroy(picture_context_t *ctx)
{
    struct d3d9_pic_context *pic_ctx = D3D9_PICCONTEXT_FROM_PICCTX(ctx);
    ReleaseD3D9PictureSys(&pic_ctx->picsys);
    free(pic_ctx);
}