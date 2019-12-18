#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {TYPE_1__** charmaps; } ;
struct TYPE_4__ {int platform_id; int encoding_id; } ;
typedef  TYPE_2__* FT_Face ;

/* Variables and functions */
 TYPE_2__* fz_font_ft_face (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
xps_identify_font_encoding(fz_context *ctx, fz_font *font, int idx, int *pid, int *eid)
{
	FT_Face face = fz_font_ft_face(ctx, font);
	*pid = face->charmaps[idx]->platform_id;
	*eid = face->charmaps[idx]->encoding_id;
}