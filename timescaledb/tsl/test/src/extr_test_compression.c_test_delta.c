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
typedef  int /*<<< orphan*/  DeltaDeltaCompressor ;
typedef  int /*<<< orphan*/  DecompressionIterator ;
typedef  TYPE_1__ DecompressResult ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AssertInt64Eq (int,int) ; 
 int DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT8OID ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * delta_delta_compressor_alloc () ; 
 int /*<<< orphan*/  delta_delta_compressor_append_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * delta_delta_decompression_iterator_from_datum_forward (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ delta_delta_decompression_iterator_try_next_forward (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsl_deltadelta_compressor_finish ; 

__attribute__((used)) static void
test_delta()
{
	DeltaDeltaCompressor *compressor = delta_delta_compressor_alloc();
	Datum compressed;
	DecompressionIterator *iter;
	int i;
	for (i = 0; i < 1015; i++)
		delta_delta_compressor_append_value(compressor, i);

	compressed = DirectFunctionCall1(tsl_deltadelta_compressor_finish, PointerGetDatum(compressor));
	Assert(DatumGetPointer(compressed) != NULL);
	AssertInt64Eq(VARSIZE(DatumGetPointer(compressed)), 56);

	i = 0;
	iter = delta_delta_decompression_iterator_from_datum_forward(compressed, INT8OID);
	for (DecompressResult r = delta_delta_decompression_iterator_try_next_forward(iter); !r.is_done;
		 r = delta_delta_decompression_iterator_try_next_forward(iter))
	{
		Assert(!r.is_null);
		AssertInt64Eq(DatumGetInt64(r.val), i);
		i += 1;
	}
	AssertInt64Eq(i, 1015);
}