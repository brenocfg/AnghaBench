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
struct lemon {int /*<<< orphan*/  outname; int /*<<< orphan*/  nolinenosflag; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tplt_linedir (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void tplt_print(FILE *out, struct lemon *lemp, char *str, int *lineno)
{
  if( str==0 ) return;
  while( *str ){
    putc(*str,out);
    if( *str=='\n' ) (*lineno)++;
    str++;
  }
  if( str[-1]!='\n' ){
    putc('\n',out);
    (*lineno)++;
  }
  if (!lemp->nolinenosflag) {
    (*lineno)++; tplt_linedir(out,*lineno,lemp->outname);
  }
  return;
}