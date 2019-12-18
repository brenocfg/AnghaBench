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
struct TYPE_3__ {int /*<<< orphan*/  type_len; int /*<<< orphan*/  type_by_val; int /*<<< orphan*/  type_align; } ;
typedef  char* Pointer ;
typedef  TYPE_1__ DatumDeserializer ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 char* att_addlength_pointer (char const*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ att_align_pointer (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fetch_att (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Datum
bytes_to_datum_and_advance(DatumDeserializer *deserializer, const char **ptr)
{
	Datum res;

	/* att_align_pointer can handle the case where an unaligned short-varlen follows any other
	 * varlen by detecting padding. padding bytes _must always_ be set to 0, while the first byte of
	 * a varlen header is _never_ 0. This means that if the next byte is non-zero, it must be the
	 * start of a short-varlen, otherwise we need to align the pointer.
	 */

	*ptr =
		(Pointer) att_align_pointer(*ptr, deserializer->type_align, deserializer->type_len, *ptr);
	res = fetch_att(*ptr, deserializer->type_by_val, deserializer->type_len);
	*ptr = att_addlength_pointer(*ptr, deserializer->type_len, *ptr);
	return res;
}