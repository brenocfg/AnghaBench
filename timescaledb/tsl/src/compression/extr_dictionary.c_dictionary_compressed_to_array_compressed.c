#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  val; scalar_t__ is_null; int /*<<< orphan*/  is_done; } ;
struct TYPE_8__ {int /*<<< orphan*/  element_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ DictionaryDecompressionIterator ;
typedef  TYPE_2__ DictionaryCompressed ;
typedef  TYPE_3__ DecompressResult ;
typedef  int /*<<< orphan*/  ArrayCompressor ;
typedef  int /*<<< orphan*/  ArrayCompressed ;

/* Variables and functions */
 int /*<<< orphan*/ * array_compressor_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_compressor_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_compressor_append_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * array_compressor_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictionary_decompression_iterator_init (TYPE_1__*,void*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__ dictionary_decompression_iterator_try_next_forward (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ArrayCompressed *
dictionary_compressed_to_array_compressed(DictionaryCompressed *compressed)
{
	ArrayCompressor *compressor = array_compressor_alloc(compressed->element_type);
	DictionaryDecompressionIterator iterator;
	dictionary_decompression_iterator_init(&iterator,
										   (void *) compressed,
										   true,
										   compressed->element_type);

	for (DecompressResult res = dictionary_decompression_iterator_try_next_forward(&iterator.base);
		 !res.is_done;
		 res = dictionary_decompression_iterator_try_next_forward(&iterator.base))
	{
		if (res.is_null)
			array_compressor_append_null(compressor);
		else
			array_compressor_append(compressor, res.val);
	}

	return array_compressor_finish(compressor);
}