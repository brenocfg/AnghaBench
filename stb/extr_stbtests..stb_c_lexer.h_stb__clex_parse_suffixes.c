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
typedef  int /*<<< orphan*/  stb_lexer ;

/* Variables and functions */
 int stb__clex_token (int /*<<< orphan*/ *,long,char*,char*) ; 

__attribute__((used)) static int stb__clex_parse_suffixes(stb_lexer *lexer, long tokenid, char *start, char *cur, const char *suffixes)
{
   #ifdef STB__clex_parse_suffixes
   lexer->string = lexer->string_storage;
   lexer->string_len = 0;

   while ((*cur >= 'a' && *cur <= 'z') || (*cur >= 'A' && *cur <= 'Z')) {
      if (stb__strchr(suffixes, *cur) == 0)
         return stb__clex_token(lexer, CLEX_parse_error, start, cur);
      if (lexer->string_len+1 >= lexer->string_storage_len)
         return stb__clex_token(lexer, CLEX_parse_error, start, cur);
      lexer->string[lexer->string_len++] = *cur++;
   }
   #else
   suffixes = suffixes; // attempt to suppress warnings
   #endif
   return stb__clex_token(lexer, tokenid, start, cur-1);
}