#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lemon {char* tokenprefix; int nterminal; TYPE_1__** symbols; } ;
struct TYPE_2__ {int name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int LINESIZE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * file_open (struct lemon*,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,int,int) ; 
 int /*<<< orphan*/  lemon_sprintf (char*,char*,char const*,int,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

void ReportHeader(struct lemon *lemp)
{
  FILE *out, *in;
  const char *prefix;
  char line[LINESIZE];
  char pattern[LINESIZE];
  int i;

  if( lemp->tokenprefix ) prefix = lemp->tokenprefix;
  else                    prefix = "";
  in = file_open(lemp,".h","rb");
  if( in ){
    int nextChar;
    for(i=1; i<lemp->nterminal && fgets(line,LINESIZE,in); i++){
      lemon_sprintf(pattern,"#define %s%-30s %3d\n",
                    prefix,lemp->symbols[i]->name,i);
      if( strcmp(line,pattern) ) break;
    }
    nextChar = fgetc(in);
    fclose(in);
    if( i==lemp->nterminal && nextChar==EOF ){
      /* No change in the file.  Don't rewrite it. */
      return;
    }
  }
  out = file_open(lemp,".h","wb");
  if( out ){
    for(i=1; i<lemp->nterminal; i++){
      fprintf(out,"#define %s%-30s %3d\n",prefix,lemp->symbols[i]->name,i);
    }
    fclose(out);
  }
  return;
}