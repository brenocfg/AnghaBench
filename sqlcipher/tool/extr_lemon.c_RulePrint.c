#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct symbol {scalar_t__ type; int nsubsym; char* name; TYPE_2__** subsym; } ;
struct rule {int nrhs; struct symbol** rhs; TYPE_1__* lhs; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ MULTITERMINAL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void RulePrint(FILE *fp, struct rule *rp, int iCursor){
  struct symbol *sp;
  int i, j;
  fprintf(fp,"%s ::=",rp->lhs->name);
  for(i=0; i<=rp->nrhs; i++){
    if( i==iCursor ) fprintf(fp," *");
    if( i==rp->nrhs ) break;
    sp = rp->rhs[i];
    if( sp->type==MULTITERMINAL ){
      fprintf(fp," %s", sp->subsym[0]->name);
      for(j=1; j<sp->nsubsym; j++){
        fprintf(fp,"|%s",sp->subsym[j]->name);
      }
    }else{
      fprintf(fp," %s", sp->name);
    }
  }
}