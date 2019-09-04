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
struct TYPE_3__ {char* input_stream; char* eof; char* parse_point; char* string_storage; int string_storage_len; } ;
typedef  TYPE_1__ stb_lexer ;

/* Variables and functions */

void stb_c_lexer_init(stb_lexer *lexer, const char *input_stream, const char *input_stream_end, char *string_store, int store_length)
{
   lexer->input_stream = (char *) input_stream;
   lexer->eof = (char *) input_stream_end;
   lexer->parse_point = (char *) input_stream;
   lexer->string_storage = string_store;
   lexer->string_storage_len = store_length;
}