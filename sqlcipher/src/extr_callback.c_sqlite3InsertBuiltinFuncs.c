#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__** a; } ;
struct TYPE_6__ {TYPE_2__* pHash; } ;
struct TYPE_7__ {char* zName; TYPE_1__ u; struct TYPE_7__* pNext; } ;
typedef  TYPE_2__ FuncDef ;

/* Variables and functions */
 int SQLITE_FUNC_HASH (char const,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__ sqlite3BuiltinFunctions ; 
 TYPE_2__* sqlite3FunctionSearch (int,char const*) ; 
 int sqlite3Strlen30 (char const*) ; 

void sqlite3InsertBuiltinFuncs(
  FuncDef *aDef,      /* List of global functions to be inserted */
  int nDef            /* Length of the apDef[] list */
){
  int i;
  for(i=0; i<nDef; i++){
    FuncDef *pOther;
    const char *zName = aDef[i].zName;
    int nName = sqlite3Strlen30(zName);
    int h = SQLITE_FUNC_HASH(zName[0], nName);
    assert( zName[0]>='a' && zName[0]<='z' );
    pOther = sqlite3FunctionSearch(h, zName);
    if( pOther ){
      assert( pOther!=&aDef[i] && pOther->pNext!=&aDef[i] );
      aDef[i].pNext = pOther->pNext;
      pOther->pNext = &aDef[i];
    }else{
      aDef[i].pNext = 0;
      aDef[i].u.pHash = sqlite3BuiltinFunctions.a[h];
      sqlite3BuiltinFunctions.a[h] = &aDef[i];
    }
  }
}