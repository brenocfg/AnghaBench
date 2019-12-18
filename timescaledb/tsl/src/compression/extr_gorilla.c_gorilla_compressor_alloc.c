#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int has_nulls; scalar_t__ prev_val; scalar_t__ prev_trailing_zeros; scalar_t__ prev_leading_zeroes; int /*<<< orphan*/  nulls; int /*<<< orphan*/  xors; int /*<<< orphan*/  bits_used_per_xor; int /*<<< orphan*/  leading_zeros; int /*<<< orphan*/  tag1s; int /*<<< orphan*/  tag0s; } ;
typedef  TYPE_1__ GorillaCompressor ;

/* Variables and functions */
 int /*<<< orphan*/  bit_array_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  simple8brle_compressor_init (int /*<<< orphan*/ *) ; 

GorillaCompressor *
gorilla_compressor_alloc(void)
{
	GorillaCompressor *compressor = palloc(sizeof(*compressor));
	simple8brle_compressor_init(&compressor->tag0s);
	simple8brle_compressor_init(&compressor->tag1s);
	bit_array_init(&compressor->leading_zeros);
	simple8brle_compressor_init(&compressor->bits_used_per_xor);
	bit_array_init(&compressor->xors);
	simple8brle_compressor_init(&compressor->nulls);
	compressor->has_nulls = false;
	compressor->prev_leading_zeroes = 0;
	compressor->prev_trailing_zeros = 0;
	compressor->prev_val = 0;
	return compressor;
}