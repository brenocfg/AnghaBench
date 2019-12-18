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
struct TYPE_2__ {scalar_t__ label; scalar_t__ arg; scalar_t__ type; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ OPT_FFLAG ; 
 scalar_t__ OPT_FLAG ; 
 scalar_t__ OPT_FSTR ; 
 char** argv ; 
 char* emsg ; 
 int /*<<< orphan*/  errline (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  lemonStrlen (scalar_t__) ; 
 TYPE_1__* op ; 
 scalar_t__ strncmp (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 void stub1 (int) ; 
 void stub2 (char*) ; 

__attribute__((used)) static int handleflags(int i, FILE *err)
{
  int v;
  int errcnt = 0;
  int j;
  for(j=0; op[j].label; j++){
    if( strncmp(&argv[i][1],op[j].label,lemonStrlen(op[j].label))==0 ) break;
  }
  v = argv[i][0]=='-' ? 1 : 0;
  if( op[j].label==0 ){
    if( err ){
      fprintf(err,"%sundefined option.\n",emsg);
      errline(i,1,err);
    }
    errcnt++;
  }else if( op[j].arg==0 ){
    /* Ignore this option */
  }else if( op[j].type==OPT_FLAG ){
    *((int*)op[j].arg) = v;
  }else if( op[j].type==OPT_FFLAG ){
    (*(void(*)(int))(op[j].arg))(v);
  }else if( op[j].type==OPT_FSTR ){
    (*(void(*)(char *))(op[j].arg))(&argv[i][2]);
  }else{
    if( err ){
      fprintf(err,"%smissing argument on switch.\n",emsg);
      errline(i,1,err);
    }
    errcnt++;
  }
  return errcnt;
}