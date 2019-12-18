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
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_matrix ;
struct TYPE_4__ {int /*<<< orphan*/  ft_face; } ;
typedef  TYPE_1__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_outline_ft_glyph (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

fz_path *
fz_outline_glyph(fz_context *ctx, fz_font *font, int gid, fz_matrix ctm)
{
	if (!font->ft_face)
		return NULL;
	return fz_outline_ft_glyph(ctx, font, gid, ctm);
}