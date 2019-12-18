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
struct rule {char* codePrefix; char* code; int line; char* codeSuffix; } ;
struct lemon {int /*<<< orphan*/  outname; int /*<<< orphan*/  nolinenosflag; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  tplt_linedir (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void emit_code(
  FILE *out,
  struct rule *rp,
  struct lemon *lemp,
  int *lineno
){
 const char *cp;

 /* Setup code prior to the #line directive */
 if( rp->codePrefix && rp->codePrefix[0] ){
   fprintf(out, "{%s", rp->codePrefix);
   for(cp=rp->codePrefix; *cp; cp++){ if( *cp=='\n' ) (*lineno)++; }
 }

 /* Generate code to do the reduce action */
 if( rp->code ){
   if( !lemp->nolinenosflag ){
     (*lineno)++;
     tplt_linedir(out,rp->line,lemp->filename);
   }
   fprintf(out,"{%s",rp->code);
   for(cp=rp->code; *cp; cp++){ if( *cp=='\n' ) (*lineno)++; }
   fprintf(out,"}\n"); (*lineno)++;
   if( !lemp->nolinenosflag ){
     (*lineno)++;
     tplt_linedir(out,*lineno,lemp->outname);
   }
 }

 /* Generate breakdown code that occurs after the #line directive */
 if( rp->codeSuffix && rp->codeSuffix[0] ){
   fprintf(out, "%s", rp->codeSuffix);
   for(cp=rp->codeSuffix; *cp; cp++){ if( *cp=='\n' ) (*lineno)++; }
 }

 if( rp->codePrefix ){
   fprintf(out, "}\n"); (*lineno)++;
 }

 return;
}