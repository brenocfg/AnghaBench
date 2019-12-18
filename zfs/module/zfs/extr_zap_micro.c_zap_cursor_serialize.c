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
struct TYPE_3__ {unsigned long long zc_hash; unsigned long long zc_serialized; int zc_cd; int /*<<< orphan*/ * zc_zap; } ;
typedef  TYPE_1__ zap_cursor_t ;
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned long long zap_hashbits (int /*<<< orphan*/ *) ; 
 int zap_maxcd (int /*<<< orphan*/ *) ; 

uint64_t
zap_cursor_serialize(zap_cursor_t *zc)
{
	if (zc->zc_hash == -1ULL)
		return (-1ULL);
	if (zc->zc_zap == NULL)
		return (zc->zc_serialized);
	ASSERT((zc->zc_hash & zap_maxcd(zc->zc_zap)) == 0);
	ASSERT(zc->zc_cd < zap_maxcd(zc->zc_zap));

	/*
	 * We want to keep the high 32 bits of the cursor zero if we can, so
	 * that 32-bit programs can access this.  So usually use a small
	 * (28-bit) hash value so we can fit 4 bits of cd into the low 32-bits
	 * of the cursor.
	 *
	 * [ collision differentiator | zap_hashbits()-bit hash value ]
	 */
	return ((zc->zc_hash >> (64 - zap_hashbits(zc->zc_zap))) |
	    ((uint64_t)zc->zc_cd << zap_hashbits(zc->zc_zap)));
}