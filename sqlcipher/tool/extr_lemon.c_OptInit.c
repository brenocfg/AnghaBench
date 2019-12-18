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
struct s_options {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OptPrint () ; 
 char** argv ; 
 int /*<<< orphan*/ * errstream ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ handleflags (int,int /*<<< orphan*/ *) ; 
 scalar_t__ handleswitch (int,int /*<<< orphan*/ *) ; 
 struct s_options* op ; 
 scalar_t__ strchr (char*,char) ; 

int OptInit(char **a, struct s_options *o, FILE *err)
{
  int errcnt = 0;
  argv = a;
  op = o;
  errstream = err;
  if( argv && *argv && op ){
    int i;
    for(i=1; argv[i]; i++){
      if( argv[i][0]=='+' || argv[i][0]=='-' ){
        errcnt += handleflags(i,err);
      }else if( strchr(argv[i],'=') ){
        errcnt += handleswitch(i,err);
      }
    }
  }
  if( errcnt>0 ){
    fprintf(err,"Valid command line options for \"%s\" are:\n",*a);
    OptPrint();
    exit(1);
  }
  return 0;
}