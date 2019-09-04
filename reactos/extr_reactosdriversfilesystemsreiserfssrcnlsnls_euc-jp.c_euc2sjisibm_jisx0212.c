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
struct TYPE_3__ {unsigned short euc; unsigned char* sjis; } ;

/* Variables and functions */
 int MAP_ELEMENT_OF (TYPE_1__*) ; 
 TYPE_1__* euc2sjisibm_jisx0212_map ; 

__attribute__((used)) static inline int euc2sjisibm_jisx0212(unsigned char *sjis, const unsigned char euc_hi,
				       const unsigned char euc_lo)
{
	int index, min_index, max_index;
	unsigned short euc;

	min_index = 0;
	max_index = MAP_ELEMENT_OF(euc2sjisibm_jisx0212_map) - 1;
	euc = (euc_hi << 8) | euc_lo;

	while (min_index <= max_index) {
		index = (min_index + max_index) / 2;
		if (euc < euc2sjisibm_jisx0212_map[index].euc)
			max_index = index - 1;
		else
			min_index = index + 1;
		if (euc == euc2sjisibm_jisx0212_map[index].euc) {
			sjis[0] = euc2sjisibm_jisx0212_map[index].sjis[0];
			sjis[1] = euc2sjisibm_jisx0212_map[index].sjis[1];
			return 3;
		}
	}
	return 0;
}