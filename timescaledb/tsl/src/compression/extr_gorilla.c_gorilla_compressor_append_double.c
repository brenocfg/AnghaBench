#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_2__ {int /*<<< orphan*/ * internal; } ;
typedef  TYPE_1__ ExtendedCompressor ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Compressor ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_get_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gorilla_compressor_alloc () ; 
 int /*<<< orphan*/  gorilla_compressor_append_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gorilla_compressor_append_double(Compressor *compressor, Datum val)
{
	ExtendedCompressor *extended = (ExtendedCompressor *) compressor;
	uint64 value = double_get_bits(DatumGetFloat8(val));
	if (extended->internal == NULL)
		extended->internal = gorilla_compressor_alloc();

	gorilla_compressor_append_value(extended->internal, value);
}