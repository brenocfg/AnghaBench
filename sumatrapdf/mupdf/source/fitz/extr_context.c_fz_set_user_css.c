#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* style; } ;
typedef  TYPE_2__ fz_context ;
struct TYPE_6__ {int /*<<< orphan*/ * user_css; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_strdup (TYPE_2__*,char const*) ; 

void fz_set_user_css(fz_context *ctx, const char *user_css)
{
	fz_free(ctx, ctx->style->user_css);
	ctx->style->user_css = user_css ? fz_strdup(ctx, user_css) : NULL;
}