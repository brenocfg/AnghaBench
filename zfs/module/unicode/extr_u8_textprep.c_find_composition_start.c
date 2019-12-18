#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  size_t uchar_t ;
struct TYPE_2__ {size_t tbl_id; size_t base; } ;

/* Variables and functions */
 size_t U8_16BIT_TABLE_INDICATOR ; 
 size_t U8_TBL_ELEMENT_NOT_DEF ; 
 size_t** u8_composition_b1_tbl ; 
 size_t*** u8_composition_b2_tbl ; 
 TYPE_1__*** u8_composition_b3_tbl ; 
 size_t*** u8_composition_b4_16bit_tbl ; 
 size_t*** u8_composition_b4_tbl ; 
 int /*<<< orphan*/ ** u8_composition_final_tbl ; 

__attribute__((used)) static uchar_t *
find_composition_start(size_t uv, uchar_t *s, size_t sz)
{
	uint16_t b1 = 0;
	uint16_t b2 = 0;
	uint16_t b3 = 0;
	uint16_t b3_tbl;
	uint16_t b3_base;
	uint16_t b4 = 0;
	size_t start_id;
	size_t end_id;

	if (sz == 1) {
		b4 = s[0];
	} else if (sz == 2) {
		b3 = s[0];
		b4 = s[1];
	} else if (sz == 3) {
		b2 = s[0];
		b3 = s[1];
		b4 = s[2];
	} else if (sz == 4) {
		b1 = s[0];
		b2 = s[1];
		b3 = s[2];
		b4 = s[3];
	} else {
		/*
		 * This is a fallback and should not happen if the function
		 * was called properly.
		 */
		return (NULL);
	}

	b1 = u8_composition_b1_tbl[uv][b1];
	if (b1 == U8_TBL_ELEMENT_NOT_DEF)
		return (NULL);

	b2 = u8_composition_b2_tbl[uv][b1][b2];
	if (b2 == U8_TBL_ELEMENT_NOT_DEF)
		return (NULL);

	b3_tbl = u8_composition_b3_tbl[uv][b2][b3].tbl_id;
	if (b3_tbl == U8_TBL_ELEMENT_NOT_DEF)
		return (NULL);

	if (b3_tbl >= U8_16BIT_TABLE_INDICATOR) {
		b3_tbl -= U8_16BIT_TABLE_INDICATOR;
		start_id = u8_composition_b4_16bit_tbl[uv][b3_tbl][b4];
		end_id = u8_composition_b4_16bit_tbl[uv][b3_tbl][b4 + 1];
	} else {
		start_id = u8_composition_b4_tbl[uv][b3_tbl][b4];
		end_id = u8_composition_b4_tbl[uv][b3_tbl][b4 + 1];
	}

	if (start_id >= end_id)
		return (NULL);

	b3_base = u8_composition_b3_tbl[uv][b2][b3].base;

	return ((uchar_t *)&(u8_composition_final_tbl[uv][b3_base + start_id]));
}