#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_1__ fz_shade ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 scalar_t__ FZ_FUNCTION_BASED ; 
 scalar_t__ FZ_LINEAR ; 
 scalar_t__ FZ_MESH_TYPE4 ; 
 scalar_t__ FZ_MESH_TYPE5 ; 
 scalar_t__ FZ_MESH_TYPE6 ; 
 scalar_t__ FZ_MESH_TYPE7 ; 
 scalar_t__ FZ_RADIAL ; 
 int /*<<< orphan*/  fz_bound_mesh_type1 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_bound_mesh_type2 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_bound_mesh_type3 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_bound_mesh_type4567 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static fz_rect
fz_bound_mesh(fz_context *ctx, fz_shade *shade)
{
	if (shade->type == FZ_FUNCTION_BASED)
		return fz_bound_mesh_type1(ctx, shade);
	else if (shade->type == FZ_LINEAR)
		return fz_bound_mesh_type2(ctx, shade);
	else if (shade->type == FZ_RADIAL)
		return fz_bound_mesh_type3(ctx, shade);
	else if (shade->type == FZ_MESH_TYPE4 ||
		shade->type == FZ_MESH_TYPE5 ||
		shade->type == FZ_MESH_TYPE6 ||
		shade->type == FZ_MESH_TYPE7)
		return fz_bound_mesh_type4567(ctx, shade);
	else
		fz_throw(ctx, FZ_ERROR_GENERIC, "Unexpected mesh type %d\n", shade->type);
}