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
struct TYPE_4__ {int /*<<< orphan*/  shade; int /*<<< orphan*/  pattern; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_1__ pdf_material ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_shade (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_drop_pattern (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pdf_material *
pdf_drop_material(fz_context *ctx, pdf_material *mat)
{
	fz_drop_colorspace(ctx, mat->colorspace);
	pdf_drop_pattern(ctx, mat->pattern);
	fz_drop_shade(ctx, mat->shade);
	return mat;
}