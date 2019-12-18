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
typedef  int /*<<< orphan*/  GorillaCompressed ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  CompressedGorillaData ;

/* Variables and functions */
 scalar_t__ PG_DETOAST_DATUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compressed_gorilla_data_init_from_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
compressed_gorilla_data_init_from_datum(CompressedGorillaData *data, Datum gorilla_compressed)
{
	compressed_gorilla_data_init_from_pointer(data,
											  (GorillaCompressed *) PG_DETOAST_DATUM(
												  gorilla_compressed));
}