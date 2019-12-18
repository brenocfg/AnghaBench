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
struct TYPE_4__ {scalar_t__ shade; scalar_t__ pattern; scalar_t__ colorspace; } ;
typedef  TYPE_1__ pdf_material ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_keep_colorspace (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fz_keep_shade (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pdf_keep_pattern (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static pdf_material *
pdf_keep_material(fz_context *ctx, pdf_material *mat)
{
	if (mat->colorspace)
		fz_keep_colorspace(ctx, mat->colorspace);
	if (mat->pattern)
		pdf_keep_pattern(ctx, mat->pattern);
	if (mat->shade)
		fz_keep_shade(ctx, mat->shade);
	return mat;
}