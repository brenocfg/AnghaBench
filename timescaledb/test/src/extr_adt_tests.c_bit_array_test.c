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
typedef  int /*<<< orphan*/  BitArrayIterator ;
typedef  int /*<<< orphan*/  BitArray ;

/* Variables and functions */
 int /*<<< orphan*/  AssertInt64Eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bit_array_append (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  bit_array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bit_array_iter_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bit_array_iter_next_rev (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bit_array_iterator_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bit_array_iterator_init_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bit_array_test(void)
{
	BitArray bits;
	BitArrayIterator iter;
	int i;
	bit_array_init(&bits);

	for (i = 0; i < 65; i++)
		bit_array_append(&bits, i, i);

	bit_array_append(&bits, 0, 0);
	bit_array_append(&bits, 0, 0);
	bit_array_append(&bits, 64, 0x9069060909009090);
	bit_array_append(&bits, 1, 0);
	bit_array_append(&bits, 64, ~0x9069060909009090);
	bit_array_append(&bits, 1, 1);

	bit_array_iterator_init(&iter, &bits);
	for (i = 0; i < 65; i++)
		AssertInt64Eq(bit_array_iter_next(&iter, i), i);

	AssertInt64Eq(bit_array_iter_next(&iter, 0), 0);
	AssertInt64Eq(bit_array_iter_next(&iter, 0), 0);
	AssertInt64Eq(bit_array_iter_next(&iter, 64), 0x9069060909009090);
	AssertInt64Eq(bit_array_iter_next(&iter, 1), 0);
	AssertInt64Eq(bit_array_iter_next(&iter, 64), ~0x9069060909009090);
	AssertInt64Eq(bit_array_iter_next(&iter, 1), 1);

	bit_array_iterator_init_rev(&iter, &bits);
	AssertInt64Eq(bit_array_iter_next_rev(&iter, 1), 1);
	AssertInt64Eq(bit_array_iter_next_rev(&iter, 64), ~0x9069060909009090);
	AssertInt64Eq(bit_array_iter_next_rev(&iter, 1), 0);
	AssertInt64Eq(bit_array_iter_next_rev(&iter, 64), 0x9069060909009090);
	AssertInt64Eq(bit_array_iter_next_rev(&iter, 0), 0);
	AssertInt64Eq(bit_array_iter_next_rev(&iter, 0), 0);
	for (i = 64; i >= 0; i--)
		AssertInt64Eq(bit_array_iter_next_rev(&iter, i), i);
}