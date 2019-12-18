#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nColumn; scalar_t__** azColumn; } ;
typedef  TYPE_1__ fulltext_vtab ;

/* Variables and functions */
 scalar_t__ memcmp (scalar_t__*,char const*,int) ; 

__attribute__((used)) static int checkColumnSpecifier(
  fulltext_vtab *pVtab,    /* The virtual table */
  const char *zToken,      /* Text of the token */
  int nToken               /* Number of characters in the token */
){
  int i;
  for(i=0; i<pVtab->nColumn; i++){
    if( memcmp(pVtab->azColumn[i], zToken, nToken)==0
        && pVtab->azColumn[i][nToken]==0 ){
      return i;
    }
  }
  return -1;
}