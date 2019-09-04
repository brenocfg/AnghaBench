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
 int /*<<< orphan*/  c (int,char*) ; 
 int stb_lex (int /*<<< orphan*/ *,char*,int*) ; 

char *expects(stb_matcher *m, char *s, int result, int len, char *str)
{
   int res2,len2=0;
   res2 = stb_lex(m, s, &len2);
   c(result == res2 && len == len2, str);
   return s + len;
}