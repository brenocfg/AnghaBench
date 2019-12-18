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
struct TYPE_3__ {int token; char* where_firstchar; char* where_lastchar; char* parse_point; } ;
typedef  TYPE_1__ stb_lexer ;

/* Variables and functions */

__attribute__((used)) static int stb__clex_token(stb_lexer *lexer, int token, char *start, char *end)
{
   lexer->token = token;
   lexer->where_firstchar = start;
   lexer->where_lastchar = end;
   lexer->parse_point = end+1;
   return 1;
}