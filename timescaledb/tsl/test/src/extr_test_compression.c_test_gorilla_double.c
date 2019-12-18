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
typedef  int /*<<< orphan*/  GorillaCompressor ;
typedef  int /*<<< orphan*/  GorillaCompressed ;
typedef  int /*<<< orphan*/  DecompressionIterator ;
typedef  TYPE_1__ DecompressResult ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AssertDoubleEq (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  AssertInt64Eq (double,int) ; 
 int /*<<< orphan*/  DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLOAT8OID ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 double VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  double_get_bits (double) ; 
 int /*<<< orphan*/ * gorilla_compressor_alloc () ; 
 int /*<<< orphan*/  gorilla_compressor_append_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gorilla_compressor_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gorilla_decompression_iterator_from_datum_forward (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gorilla_decompression_iterator_from_datum_reverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ gorilla_decompression_iterator_try_next_forward (int /*<<< orphan*/ *) ; 
 TYPE_1__ gorilla_decompression_iterator_try_next_reverse (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_gorilla_double()
{
	GorillaCompressor *compressor = gorilla_compressor_alloc();
	GorillaCompressed *compressed;
	DecompressionIterator *iter;
	double i;
	for (i = 0.0; i < 1015.0; i++)
		gorilla_compressor_append_value(compressor, double_get_bits(i));

	compressed = gorilla_compressor_finish(compressor);
	Assert(compressed != NULL);
	AssertInt64Eq(VARSIZE(compressed), 1200);

	i = 0;
	iter =
		gorilla_decompression_iterator_from_datum_forward(PointerGetDatum(compressed), FLOAT8OID);
	for (DecompressResult r = gorilla_decompression_iterator_try_next_forward(iter); !r.is_done;
		 r = gorilla_decompression_iterator_try_next_forward(iter))
	{
		Assert(!r.is_null);
		AssertDoubleEq(DatumGetFloat8(r.val), i);
		i += 1.0;
	}
	AssertInt64Eq(i, 1015);

	iter =
		gorilla_decompression_iterator_from_datum_reverse(PointerGetDatum(compressed), FLOAT8OID);
	for (DecompressResult r = gorilla_decompression_iterator_try_next_reverse(iter); !r.is_done;
		 r = gorilla_decompression_iterator_try_next_reverse(iter))
	{
		Assert(!r.is_null);
		AssertDoubleEq(DatumGetFloat8(r.val), i - 1);
		i -= 1;
	}
	AssertInt64Eq(i, 0);
}