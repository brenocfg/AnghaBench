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
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {TYPE_1__* charmap; } ;
struct TYPE_5__ {int platform_id; scalar_t__ encoding_id; } ;
typedef  TYPE_2__* FT_Face ;

/* Variables and functions */
 int FT_Get_Char_Index (TYPE_2__*,int) ; 
 TYPE_2__* fz_font_ft_face (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xps_encode_font_char(fz_context *ctx, fz_font *font, int code)
{
	FT_Face face = fz_font_ft_face(ctx, font);
	int gid = FT_Get_Char_Index(face, code);
	if (gid == 0 && face->charmap && face->charmap->platform_id == 3 && face->charmap->encoding_id == 0)
		gid = FT_Get_Char_Index(face, 0xF000 | code);
	return gid;
}