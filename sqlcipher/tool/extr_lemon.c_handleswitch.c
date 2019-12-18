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
struct TYPE_2__ {scalar_t__ label; int type; scalar_t__ arg; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  OPT_DBL 135 
#define  OPT_FDBL 134 
#define  OPT_FFLAG 133 
#define  OPT_FINT 132 
#define  OPT_FLAG 131 
#define  OPT_FSTR 130 
#define  OPT_INT 129 
#define  OPT_STR 128 
 scalar_t__* argv ; 
 int /*<<< orphan*/  assert (int) ; 
 char* emsg ; 
 int /*<<< orphan*/  errline (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_1__* op ; 
 char* strchr (scalar_t__,char) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 
 double strtod (char*,char**) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 void stub1 (double) ; 
 void stub2 (int) ; 
 void stub3 (char*) ; 

__attribute__((used)) static int handleswitch(int i, FILE *err)
{
  int lv = 0;
  double dv = 0.0;
  char *sv = 0, *end;
  char *cp;
  int j;
  int errcnt = 0;
  cp = strchr(argv[i],'=');
  assert( cp!=0 );
  *cp = 0;
  for(j=0; op[j].label; j++){
    if( strcmp(argv[i],op[j].label)==0 ) break;
  }
  *cp = '=';
  if( op[j].label==0 ){
    if( err ){
      fprintf(err,"%sundefined option.\n",emsg);
      errline(i,0,err);
    }
    errcnt++;
  }else{
    cp++;
    switch( op[j].type ){
      case OPT_FLAG:
      case OPT_FFLAG:
        if( err ){
          fprintf(err,"%soption requires an argument.\n",emsg);
          errline(i,0,err);
        }
        errcnt++;
        break;
      case OPT_DBL:
      case OPT_FDBL:
        dv = strtod(cp,&end);
        if( *end ){
          if( err ){
            fprintf(err,
               "%sillegal character in floating-point argument.\n",emsg);
            errline(i,(int)((char*)end-(char*)argv[i]),err);
          }
          errcnt++;
        }
        break;
      case OPT_INT:
      case OPT_FINT:
        lv = strtol(cp,&end,0);
        if( *end ){
          if( err ){
            fprintf(err,"%sillegal character in integer argument.\n",emsg);
            errline(i,(int)((char*)end-(char*)argv[i]),err);
          }
          errcnt++;
        }
        break;
      case OPT_STR:
      case OPT_FSTR:
        sv = cp;
        break;
    }
    switch( op[j].type ){
      case OPT_FLAG:
      case OPT_FFLAG:
        break;
      case OPT_DBL:
        *(double*)(op[j].arg) = dv;
        break;
      case OPT_FDBL:
        (*(void(*)(double))(op[j].arg))(dv);
        break;
      case OPT_INT:
        *(int*)(op[j].arg) = lv;
        break;
      case OPT_FINT:
        (*(void(*)(int))(op[j].arg))((int)lv);
        break;
      case OPT_STR:
        *(char**)(op[j].arg) = sv;
        break;
      case OPT_FSTR:
        (*(void(*)(char *))(op[j].arg))(sv);
        break;
    }
  }
  return errcnt;
}