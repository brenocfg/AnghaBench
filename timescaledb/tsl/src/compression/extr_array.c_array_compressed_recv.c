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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayCompressorSerializationInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PG_RETURN_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * array_compressed_data_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_compressed_from_serialization_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binary_string_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int pq_getmsgbyte (int /*<<< orphan*/ ) ; 

Datum
array_compressed_recv(StringInfo buffer)
{
	ArrayCompressorSerializationInfo *data;
	uint8 has_nulls;
	Oid element_type;

	has_nulls = pq_getmsgbyte(buffer);
	if (has_nulls != 0 && has_nulls != 1)
		elog(ERROR, "invalid recv in array: bad bool");

	element_type = binary_string_get_type(buffer);

	data = array_compressed_data_recv(buffer, element_type);

	PG_RETURN_POINTER(array_compressed_from_serialization_info(data, element_type));
}