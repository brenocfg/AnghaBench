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
struct TYPE_5__ {int /*<<< orphan*/  (* insert ) (int /*<<< orphan*/ *,TYPE_2__*,float,float,float,float,int) ;} ;
struct TYPE_6__ {TYPE_1__ fns; } ;
typedef  TYPE_2__ fz_rasterizer ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,float,float,float,float,int) ; 

__attribute__((used)) static inline void fz_insert_rasterizer(fz_context *ctx, fz_rasterizer *r, float x0, float y0, float x1, float y1, int rev)
{
	r->fns.insert(ctx, r, x0, y0, x1, y1, rev);
}