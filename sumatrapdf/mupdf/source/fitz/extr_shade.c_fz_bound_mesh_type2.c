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
typedef  int /*<<< orphan*/  fz_shade ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_infinite_rect ; 

__attribute__((used)) static fz_rect
fz_bound_mesh_type2(fz_context *ctx, fz_shade *shade)
{
	/* FIXME: If axis aligned and not extended, the bbox may only be
	 * infinite in one direction */
	return fz_infinite_rect;
}