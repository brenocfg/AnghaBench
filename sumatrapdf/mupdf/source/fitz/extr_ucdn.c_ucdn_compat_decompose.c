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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  decode_utf16 (unsigned short const**) ; 
 unsigned short* get_decomp_record (int /*<<< orphan*/ ) ; 

int ucdn_compat_decompose(uint32_t code, uint32_t *decomposed)
{
	int i, len;
	const unsigned short *rec = get_decomp_record(code);
	len = rec[0] >> 8;

	if (len == 0)
		return 0;

	rec++;
	for (i = 0; i < len; i++)
		decomposed[i] = decode_utf16(&rec);

	return len;
}