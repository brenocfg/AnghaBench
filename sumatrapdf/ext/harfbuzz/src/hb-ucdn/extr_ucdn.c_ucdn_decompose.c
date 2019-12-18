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
 scalar_t__ hangul_pair_decompose (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ucdn_decompose(uint32_t code, uint32_t *a, uint32_t *b)
{
    const unsigned short *rec;
    int len;

    if (hangul_pair_decompose(code, a, b))
        return 1;

    rec = get_decomp_record(code);
    len = rec[0] >> 8;

    if ((rec[0] & 0xff) != 0 || len == 0)
        return 0;

    rec++;
    *a = decode_utf16(&rec);
    if (len > 1)
        *b = decode_utf16(&rec);
    else
        *b = 0;

    return 1;
}