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
struct TYPE_3__ {char type_align; int type_len; int /*<<< orphan*/  type_storage; scalar_t__ type_by_val; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  Pointer ;
typedef  TYPE_1__ DatumSerializer ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SET_VARSIZE_SHORT (char*,int) ; 
 scalar_t__ TYPE_IS_PACKABLE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_CAN_MAKE_SHORT (int /*<<< orphan*/ ) ; 
 int VARATT_CONVERTED_SHORT_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_IS_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_IS_SHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ ) ; 
 int VARSIZE (int /*<<< orphan*/ ) ; 
 int VARSIZE_SHORT (int /*<<< orphan*/ ) ; 
 char* align_and_zero (char*,char,int*) ; 
 int /*<<< orphan*/  check_allowed_data_len (int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_att_byval (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

char *
datum_to_bytes_and_advance(DatumSerializer *serializer, char *ptr, Size *max_size, Datum datum)
{
	Size data_length;

	if (serializer->type_by_val)
	{
		/* pass-by-value */
		ptr = align_and_zero(ptr, serializer->type_align, max_size);
		data_length = serializer->type_len;
		check_allowed_data_len(data_length, *max_size);
		store_att_byval(ptr, datum, data_length);
	}
	else if (serializer->type_len == -1)
	{
		/* varlena */
		Pointer val = DatumGetPointer(datum);

		if (VARATT_IS_EXTERNAL(val))
		{
			/*
			 * Throw error, because we should never get a toast datum.
			 *  Caller should have detoasted it.
			 */
			elog(ERROR, "datum should be detoasted before passed to datum_to_bytes_and_advance");
			data_length = 0; /* keep compiler quiet */
		}
		else if (VARATT_IS_SHORT(val))
		{
			/* no alignment for short varlenas */
			data_length = VARSIZE_SHORT(val);
			check_allowed_data_len(data_length, *max_size);
			memcpy(ptr, val, data_length);
		}
		else if (TYPE_IS_PACKABLE(serializer->type_len, serializer->type_storage) &&
				 VARATT_CAN_MAKE_SHORT(val))
		{
			/* convert to short varlena -- no alignment */
			data_length = VARATT_CONVERTED_SHORT_SIZE(val);
			check_allowed_data_len(data_length, *max_size);
			SET_VARSIZE_SHORT(ptr, data_length);
			memcpy(ptr + 1, VARDATA(val), data_length - 1);
		}
		else
		{
			/* full 4-byte header varlena */
			ptr = align_and_zero(ptr, serializer->type_align, max_size);
			data_length = VARSIZE(val);
			check_allowed_data_len(data_length, *max_size);
			memcpy(ptr, val, data_length);
		}
	}
	else if (serializer->type_len == -2)
	{
		/* cstring ... never needs alignment */
		Assert(serializer->type_align == 'c');
		data_length = strlen(DatumGetCString(datum)) + 1;
		check_allowed_data_len(data_length, *max_size);
		memcpy(ptr, DatumGetPointer(datum), data_length);
	}
	else
	{
		/* fixed-length pass-by-reference */
		ptr = align_and_zero(ptr, serializer->type_align, max_size);
		Assert(serializer->type_len > 0);
		data_length = serializer->type_len;
		check_allowed_data_len(data_length, *max_size);
		memcpy(ptr, DatumGetPointer(datum), data_length);
	}

	ptr += data_length;
	*max_size = *max_size - data_length;

	return ptr;
}