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
struct TYPE_4__ {scalar_t__ n; } ;
typedef  TYPE_1__ String ;

/* Variables and functions */
 int /*<<< orphan*/  ISSPACE (char const) ; 
 int /*<<< orphan*/  stringAppend (TYPE_1__*,char const*,int) ; 

__attribute__((used)) static void stringAppendTerm(String *p, const char *z){
  int i;
  if( p->n ) stringAppend(p, " ", 1);
  if( z==0 ){
    stringAppend(p, "nil", 3);
    return;
  }
  for(i=0; z[i] && !ISSPACE(z[i]); i++){}
  if( i>0 && z[i]==0 ){
    stringAppend(p, z, i);
    return;
  }
  stringAppend(p, "'", 1);
  while( z[0] ){
    for(i=0; z[i] && z[i]!='\''; i++){}
    if( z[i] ){
      stringAppend(p, z, i+1);
      stringAppend(p, "'", 1);
      z += i+1;
    }else{
      stringAppend(p, z, i);
      break;
    }
  }
  stringAppend(p, "'", 1);
}