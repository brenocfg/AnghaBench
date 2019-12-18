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
struct lemon {char* filename; int /*<<< orphan*/  errorcnt; int /*<<< orphan*/  argv0; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ access (char*,int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  lemon_sprintf (char*,char*,...) ; 
 char* pathsearch (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strrchr (char*,char) ; 
 scalar_t__ user_templatename ; 

FILE *tplt_open(struct lemon *lemp)
{
  static char templatename[] = "lempar.c";
  char buf[1000];
  FILE *in;
  char *tpltname;
  char *cp;

  /* first, see if user specified a template filename on the command line. */
  if (user_templatename != 0) {
    if( access(user_templatename,004)==-1 ){
      fprintf(stderr,"Can't find the parser driver template file \"%s\".\n",
        user_templatename);
      lemp->errorcnt++;
      return 0;
    }
    in = fopen(user_templatename,"rb");
    if( in==0 ){
      fprintf(stderr,"Can't open the template file \"%s\".\n",
              user_templatename);
      lemp->errorcnt++;
      return 0;
    }
    return in;
  }

  cp = strrchr(lemp->filename,'.');
  if( cp ){
    lemon_sprintf(buf,"%.*s.lt",(int)(cp-lemp->filename),lemp->filename);
  }else{
    lemon_sprintf(buf,"%s.lt",lemp->filename);
  }
  if( access(buf,004)==0 ){
    tpltname = buf;
  }else if( access(templatename,004)==0 ){
    tpltname = templatename;
  }else{
    tpltname = pathsearch(lemp->argv0,templatename,0);
  }
  if( tpltname==0 ){
    fprintf(stderr,"Can't find the parser driver template file \"%s\".\n",
    templatename);
    lemp->errorcnt++;
    return 0;
  }
  in = fopen(tpltname,"rb");
  if( in==0 ){
    fprintf(stderr,"Can't open the template file \"%s\".\n",templatename);
    lemp->errorcnt++;
    return 0;
  }
  return in;
}