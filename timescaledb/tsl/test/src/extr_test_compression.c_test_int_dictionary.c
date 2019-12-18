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
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  is_null; int /*<<< orphan*/  is_done; } ;
typedef  int /*<<< orphan*/  DictionaryCompressor ;
typedef  int /*<<< orphan*/  DictionaryCompressed ;
typedef  int /*<<< orphan*/  DecompressionIterator ;
typedef  TYPE_1__ DecompressResult ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AssertInt64Eq (int,int) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictionary_compressor_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictionary_compressor_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictionary_compressor_finish (int /*<<< orphan*/ *) ; 
 TYPE_1__ dictionary_decompression_iterator_try_next_forward (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsl_dictionary_decompression_iterator_from_datum_forward (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_int_dictionary()
{
	DictionaryCompressor *compressor = dictionary_compressor_alloc(INT4OID);
	DictionaryCompressed *compressed;
	DecompressionIterator *iter;
	int i;
	for (i = 0; i < 1015; i++)
		dictionary_compressor_append(compressor, Int32GetDatum(i % 15));

	compressed = dictionary_compressor_finish(compressor);
	Assert(compressed != NULL);

	i = 0;
	iter = tsl_dictionary_decompression_iterator_from_datum_forward(PointerGetDatum(compressed),
																	INT4OID);
	for (DecompressResult r = dictionary_decompression_iterator_try_next_forward(iter); !r.is_done;
		 r = dictionary_decompression_iterator_try_next_forward(iter))
	{
		Assert(!r.is_null);
		AssertInt64Eq(DatumGetInt32(r.val), i % 15);
		i += 1;
	}
	AssertInt64Eq(i, 1015);
}