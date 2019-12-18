#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_7__ {int /*<<< orphan*/  type_mod; int /*<<< orphan*/  type_io_param; int /*<<< orphan*/  recv_flinfo; } ;
struct TYPE_6__ {char* data; int /*<<< orphan*/  maxlen; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_2__ DatumDeserializer ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int BinaryStringEncoding ;

/* Variables and functions */
#define  BINARY_ENCODING 130 
 int /*<<< orphan*/  InputFunctionCall (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  MESSAGE_SPECIFIES_ENCODING 129 
 int /*<<< orphan*/  ReceiveFunctionCall (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TEXT_ENCODING 128 
 int /*<<< orphan*/  load_recv_fn (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pq_getmsgbyte (int /*<<< orphan*/ ) ; 
 char* pq_getmsgbytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_getmsgint32 (int /*<<< orphan*/ ) ; 
 char* pq_getmsgstring (int /*<<< orphan*/ ) ; 

Datum
binary_string_to_datum(DatumDeserializer *deserializer, BinaryStringEncoding encoding,
					   StringInfo buffer)
{
	Datum res;
	bool use_binary_recv = false;

	switch (encoding)
	{
		case BINARY_ENCODING:
			use_binary_recv = true;
			break;
		case TEXT_ENCODING:
			use_binary_recv = false;
			break;
		case MESSAGE_SPECIFIES_ENCODING:
			use_binary_recv = pq_getmsgbyte(buffer) != 0;
			break;
	}

	load_recv_fn(deserializer, use_binary_recv);

	if (use_binary_recv)
	{
		uint32 data_size = pq_getmsgint32(buffer);
		const char *bytes = pq_getmsgbytes(buffer, data_size);
		StringInfoData d = {
			.data = (char *) bytes,
			.len = data_size,
			.maxlen = data_size,
		};
		res = ReceiveFunctionCall(&deserializer->recv_flinfo,
								  &d,
								  deserializer->type_io_param,
								  deserializer->type_mod);
	}
	else
	{
		const char *string = pq_getmsgstring(buffer);
		res = InputFunctionCall(&deserializer->recv_flinfo,
								(char *) string,
								deserializer->type_io_param,
								deserializer->type_mod);
	}
	return res;
}