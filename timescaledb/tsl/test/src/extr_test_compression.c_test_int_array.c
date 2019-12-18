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
struct TYPE_4__ {int /*<<< orphan*/  val; int /*<<< orphan*/  is_null; int /*<<< orphan*/  is_done; } ;
typedef  int /*<<< orphan*/  DecompressionIterator ;
typedef  TYPE_1__ DecompressResult ;
typedef  int /*<<< orphan*/  ArrayCompressor ;
typedef  int /*<<< orphan*/  ArrayCompressed ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AssertInt64Eq (int,int) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * array_compressor_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_compressor_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * array_compressor_finish (int /*<<< orphan*/ *) ; 
 TYPE_1__ array_decompression_iterator_try_next_forward (int /*<<< orphan*/ *) ; 
 TYPE_1__ array_decompression_iterator_try_next_reverse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsl_array_decompression_iterator_from_datum_forward (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tsl_array_decompression_iterator_from_datum_reverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_int_array()
{
	ArrayCompressor *compressor = array_compressor_alloc(INT4OID);
	ArrayCompressed *compressed;
	DecompressionIterator *iter;
	int i;
	for (i = 0; i < 1015; i++)
		array_compressor_append(compressor, Int32GetDatum(i));

	compressed = array_compressor_finish(compressor);
	Assert(compressed != NULL);

	i = 0;
	iter =
		tsl_array_decompression_iterator_from_datum_forward(PointerGetDatum(compressed), INT4OID);
	for (DecompressResult r = array_decompression_iterator_try_next_forward(iter); !r.is_done;
		 r = array_decompression_iterator_try_next_forward(iter))
	{
		Assert(!r.is_null);
		AssertInt64Eq(DatumGetInt32(r.val), i);
		i += 1;
	}
	AssertInt64Eq(i, 1015);

	iter =
		tsl_array_decompression_iterator_from_datum_reverse(PointerGetDatum(compressed), INT4OID);
	for (DecompressResult r = array_decompression_iterator_try_next_reverse(iter); !r.is_done;
		 r = array_decompression_iterator_try_next_reverse(iter))
	{
		Assert(!r.is_null);
		AssertInt64Eq(DatumGetInt32(r.val), i - 1);
		i -= 1;
	}
	AssertInt64Eq(i, 0);
}