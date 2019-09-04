#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* string_storage; int string_storage_len; char* string; int string_len; } ;
typedef  TYPE_1__ stb_lexer ;

/* Variables and functions */
 int CLEX_parse_error ; 
 int stb__clex_parse_char (char*,char**) ; 
 int stb__clex_token (TYPE_1__*,int,char*,char*) ; 

__attribute__((used)) static int stb__clex_parse_string(stb_lexer *lexer, char *p, int type)
{
   char *start = p;
   char delim = *p++; // grab the " or ' for later matching
   char *out = lexer->string_storage;
   char *outend = lexer->string_storage + lexer->string_storage_len;
   while (*p != delim) {
      int n;
      if (*p == '\\') {
         char *q;
         n = stb__clex_parse_char(p, &q);
         if (n < 0)
            return stb__clex_token(lexer, CLEX_parse_error, start, q);
         p = q;
      } else {
         // @OPTIMIZE: could speed this up by looping-while-not-backslash
         n = (unsigned char) *p++;
      }
      if (out+1 > outend)
         return stb__clex_token(lexer, CLEX_parse_error, start, p);
      // @TODO expand unicode escapes to UTF8
      *out++ = (char) n;
   }
   *out = 0;
   lexer->string = lexer->string_storage;
   lexer->string_len = (int) (out - lexer->string_storage);
   return stb__clex_token(lexer, type, start, p);
}