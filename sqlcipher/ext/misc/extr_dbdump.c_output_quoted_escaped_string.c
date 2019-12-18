#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pArg; int /*<<< orphan*/  (* xCallback ) (char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ DState ;

/* Variables and functions */
 int /*<<< orphan*/  output_formatted (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (char*,int /*<<< orphan*/ ) ; 
 char* unused_string (char const*,char*,char*,char*) ; 

__attribute__((used)) static void output_quoted_escaped_string(DState *p, const char *z){
  int i;
  char c;
  for(i=0; (c = z[i])!=0 && c!='\'' && c!='\n' && c!='\r'; i++){}
  if( c==0 ){
    output_formatted(p,"'%s'",z);
  }else{
    const char *zNL = 0;
    const char *zCR = 0;
    int nNL = 0;
    int nCR = 0;
    char zBuf1[20], zBuf2[20];
    for(i=0; z[i]; i++){
      if( z[i]=='\n' ) nNL++;
      if( z[i]=='\r' ) nCR++;
    }
    if( nNL ){
      p->xCallback("replace(", p->pArg);
      zNL = unused_string(z, "\\n", "\\012", zBuf1);
    }
    if( nCR ){
      p->xCallback("replace(", p->pArg);
      zCR = unused_string(z, "\\r", "\\015", zBuf2);
    }
    p->xCallback("'", p->pArg);
    while( *z ){
      for(i=0; (c = z[i])!=0 && c!='\n' && c!='\r' && c!='\''; i++){}
      if( c=='\'' ) i++;
      if( i ){
        output_formatted(p, "%.*s", i, z);
        z += i;
      }
      if( c=='\'' ){
        p->xCallback("'", p->pArg);
        continue;
      }
      if( c==0 ){
        break;
      }
      z++;
      if( c=='\n' ){
        p->xCallback(zNL, p->pArg);
        continue;
      }
      p->xCallback(zCR, p->pArg);
    }
    p->xCallback("'", p->pArg);
    if( nCR ){
      output_formatted(p, ",'%s',char(13))", zCR);
    }
    if( nNL ){
      output_formatted(p, ",'%s',char(10))", zNL);
    }
  }
}