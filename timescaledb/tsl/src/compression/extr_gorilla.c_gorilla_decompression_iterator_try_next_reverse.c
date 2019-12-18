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
struct TYPE_3__ {scalar_t__ compression_algorithm; int /*<<< orphan*/  element_type; int /*<<< orphan*/  forward; } ;
typedef  int /*<<< orphan*/  GorillaDecompressionIterator ;
typedef  TYPE_1__ DecompressionIterator ;
typedef  int /*<<< orphan*/  DecompressResult ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ COMPRESSION_ALGORITHM_GORILLA ; 
 int /*<<< orphan*/  convert_from_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gorilla_decompression_iterator_try_next_reverse_internal (int /*<<< orphan*/ *) ; 

DecompressResult
gorilla_decompression_iterator_try_next_reverse(DecompressionIterator *iter_base)
{
	Assert(iter_base->compression_algorithm == COMPRESSION_ALGORITHM_GORILLA &&
		   !iter_base->forward);
	return convert_from_internal(gorilla_decompression_iterator_try_next_reverse_internal(
									 (GorillaDecompressionIterator *) iter_base),
								 iter_base->element_type);
}