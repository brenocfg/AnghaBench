#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {int num_charmaps; } ;
typedef  TYPE_1__* FT_Face ;

/* Variables and functions */
 TYPE_1__* fz_font_ft_face (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xps_count_font_encodings(fz_context *ctx, fz_font *font)
{
	FT_Face face = fz_font_ft_face(ctx, font);
	return face->num_charmaps;
}