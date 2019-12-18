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
struct TYPE_2__ {int /*<<< orphan*/ * internal; } ;
typedef  TYPE_1__ ExtendedCompressor ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Compressor ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetTimestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * delta_delta_compressor_alloc () ; 
 int /*<<< orphan*/  delta_delta_compressor_append_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
deltadelta_compressor_append_timestamp(Compressor *compressor, Datum val)
{
	ExtendedCompressor *extended = (ExtendedCompressor *) compressor;
	if (extended->internal == NULL)
		extended->internal = delta_delta_compressor_alloc();

	delta_delta_compressor_append_value(extended->internal, DatumGetTimestamp(val));
}