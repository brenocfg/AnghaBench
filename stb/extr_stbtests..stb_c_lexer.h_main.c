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
struct TYPE_5__ {scalar_t__ token; } ;
typedef  TYPE_1__ stb_lexer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CLEX_parse_error ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  print_token (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ stb_c_lexer_get_token (TYPE_1__*) ; 
 int /*<<< orphan*/  stb_c_lexer_init (TYPE_1__*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
   FILE *f = fopen("stb_c_lexer.h","rb");
   char *text = (char *) malloc(1 << 20);
   int len = f ? (int) fread(text, 1, 1<<20, f) : -1;
   stb_lexer lex;
   if (len < 0) {
      fprintf(stderr, "Error opening file\n");
      free(text);
      fclose(f);
      return 1;
   }
   fclose(f);

   stb_c_lexer_init(&lex, text, text+len, (char *) malloc(0x10000), 0x10000);
   while (stb_c_lexer_get_token(&lex)) {
      if (lex.token == CLEX_parse_error) {
         printf("\n<<<PARSE ERROR>>>\n");
         break;
      }
      print_token(&lex);
      printf("  ");
   }
   return 0;
}