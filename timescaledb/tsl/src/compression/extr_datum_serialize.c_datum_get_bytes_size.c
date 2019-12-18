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
struct TYPE_3__ {int type_len; int /*<<< orphan*/  type_align; int /*<<< orphan*/  type_storage; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Pointer ;
typedef  TYPE_1__ DatumSerializer ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ TYPE_IS_PACKABLE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_CAN_MAKE_SHORT (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_CONVERTED_SHORT_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_IS_EXTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  att_addlength_datum (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  att_align_datum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

Size
datum_get_bytes_size(DatumSerializer *serializer, Size start_offset, Datum val)
{
	Size data_length = start_offset;

	if (serializer->type_len == -1)
	{
		/* varlena */
		Pointer ptr = DatumGetPointer(val);

		if (VARATT_IS_EXTERNAL(ptr))
		{
			/*
			 * Throw error, because we should never get a toasted datum.
			 * Caller should have detoasted it.
			 */
			elog(ERROR, "datum should be detoasted before passed to datum_get_bytes_size");
		}
	}

	if (TYPE_IS_PACKABLE(serializer->type_len, serializer->type_storage) &&
		VARATT_CAN_MAKE_SHORT(DatumGetPointer(val)))
	{
		/*
		 * we're anticipating converting to a short varlena header, so adjust
		 * length and don't count any alignment (the case where the Datum is already
		 * in short format is handled by att_align_datum)
		 */
		data_length += VARATT_CONVERTED_SHORT_SIZE(DatumGetPointer(val));
	}
	else
	{
		data_length =
			att_align_datum(data_length, serializer->type_align, serializer->type_len, val);
		data_length = att_addlength_datum(data_length, serializer->type_len, val);
	}

	return data_length;
}