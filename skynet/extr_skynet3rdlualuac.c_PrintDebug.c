#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* sp; } ;
struct TYPE_10__ {int sizek; int sizelocvars; int sizeupvalues; TYPE_2__* upvalues; TYPE_1__* locvars; } ;
struct TYPE_9__ {int instack; int idx; } ;
struct TYPE_8__ {int startpc; int endpc; int /*<<< orphan*/  varname; } ;
typedef  TYPE_3__ SharedProto ;
typedef  TYPE_4__ Proto ;

/* Variables and functions */
 int /*<<< orphan*/  PrintConstant (TYPE_4__ const*,int) ; 
 char* UPVALNAME (int) ; 
 int /*<<< orphan*/  VOID (TYPE_4__ const*) ; 
 char* getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void PrintDebug(const Proto* f)
{
 const SharedProto *sp = f->sp;
 int i,n;
 n=sp->sizek;
 printf("constants (%d) for %p:\n",n,VOID(f));
 for (i=0; i<n; i++)
 {
  printf("\t%d\t",i+1);
  PrintConstant(f,i);
  printf("\n");
 }
 n=sp->sizelocvars;
 printf("locals (%d) for %p:\n",n,VOID(f));
 for (i=0; i<n; i++)
 {
  printf("\t%d\t%s\t%d\t%d\n",
  i,getstr(sp->locvars[i].varname),sp->locvars[i].startpc+1,sp->locvars[i].endpc+1);
 }
 n=f->sp->sizeupvalues;
 printf("upvalues (%d) for %p:\n",n,VOID(f));
 for (i=0; i<n; i++)
 {
  printf("\t%d\t%s\t%d\t%d\n",
  i,UPVALNAME(i),sp->upvalues[i].instack,sp->upvalues[i].idx);
 }
}