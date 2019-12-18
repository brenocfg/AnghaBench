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
struct TYPE_6__ {int platform_id; } ;
struct TYPE_5__ {int num_charmaps; TYPE_2__** charmaps; } ;
typedef  TYPE_1__* FT_Face ;
typedef  TYPE_2__* FT_CharMap ;

/* Variables and functions */

__attribute__((used)) static FT_CharMap
select_type1_cmap(FT_Face face)
{
	int i;
	for (i = 0; i < face->num_charmaps; i++)
		if (face->charmaps[i]->platform_id == 7)
			return face->charmaps[i];
	if (face->num_charmaps > 0)
		return face->charmaps[0];
	return NULL;
}