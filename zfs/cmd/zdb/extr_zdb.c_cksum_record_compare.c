#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * zc_word; } ;
struct TYPE_4__ {TYPE_1__ cksum; } ;
typedef  TYPE_2__ cksum_record_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int TREE_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cksum_record_compare(const void *x1, const void *x2)
{
	const cksum_record_t *l = (cksum_record_t *)x1;
	const cksum_record_t *r = (cksum_record_t *)x2;
	int arraysize = ARRAY_SIZE(l->cksum.zc_word);
	int difference;

	for (int i = 0; i < arraysize; i++) {
		difference = TREE_CMP(l->cksum.zc_word[i], r->cksum.zc_word[i]);
		if (difference)
			break;
	}

	return (difference);
}