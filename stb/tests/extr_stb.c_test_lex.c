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
typedef  int /*<<< orphan*/  stb_matcher ;

/* Variables and functions */
 char* expects (int /*<<< orphan*/ *,char*,int,int,char*) ; 
 int /*<<< orphan*/  stb_lex_item (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * stb_lex_matcher () ; 
 int /*<<< orphan*/  stb_matcher_free (int /*<<< orphan*/ *) ; 

void test_lex(void)
{
   stb_matcher *m = stb_lex_matcher();
   //         tok_en5 .3 20.1 20. .20 .1
   char *s = "tok_en5.3 20.1 20. .20.1";

   stb_lex_item(m, "[a-zA-Z_][a-zA-Z0-9_]*", 1   );
   stb_lex_item(m, "[0-9]*\\.?[0-9]*"      , 2   );
   stb_lex_item(m, "[\r\n\t ]+"            , 3   );
   stb_lex_item(m, "."                     , -99 );
   s=expects(m,s,1,7, "stb_lex 1");
   s=expects(m,s,2,2, "stb_lex 2");
   s=expects(m,s,3,1, "stb_lex 3");
   s=expects(m,s,2,4, "stb_lex 4");
   s=expects(m,s,3,1, "stb_lex 5");
   s=expects(m,s,2,3, "stb_lex 6");
   s=expects(m,s,3,1, "stb_lex 7");
   s=expects(m,s,2,3, "stb_lex 8");
   s=expects(m,s,2,2, "stb_lex 9");
   s=expects(m,s,0,0, "stb_lex 10");
   stb_matcher_free(m);
}