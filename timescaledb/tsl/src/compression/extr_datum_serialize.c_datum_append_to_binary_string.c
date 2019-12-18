#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bytea ;
struct TYPE_5__ {int /*<<< orphan*/  send_flinfo; scalar_t__ use_binary_send; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ DatumSerializer ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ BinaryStringEncoding ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MESSAGE_SPECIFIES_ENCODING ; 
 char* OutputFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SendFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 scalar_t__ datum_serializer_binary_string_encoding (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  load_send_fn (TYPE_1__*) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pq_sendbytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendstring (int /*<<< orphan*/ ,char*) ; 

void
datum_append_to_binary_string(DatumSerializer *serializer, BinaryStringEncoding encoding,
							  StringInfo buffer, Datum datum)
{
	load_send_fn(serializer);

	if (encoding == MESSAGE_SPECIFIES_ENCODING)
		pq_sendbyte(buffer, serializer->use_binary_send);
	else if (encoding != datum_serializer_binary_string_encoding(serializer))
		elog(ERROR, "incorrect encoding chosen in datum_append_to_binary_string");

	if (serializer->use_binary_send)
	{
		bytea *output = SendFunctionCall(&serializer->send_flinfo, datum);
		pq_sendint32(buffer, VARSIZE_ANY_EXHDR(output));
		pq_sendbytes(buffer, VARDATA(output), VARSIZE_ANY_EXHDR(output));
	}
	else
	{
		char *output = OutputFunctionCall(&serializer->send_flinfo, datum);
		pq_sendstring(buffer, output);
	}
}