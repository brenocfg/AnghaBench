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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int /*<<< orphan*/  funcFlags; } ;
typedef  TYPE_1__ FuncDef ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_1__*) ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 TYPE_1__* sqlite3FindFunction (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setLikeOptFlag(sqlite3 *db, const char *zName, u8 flagVal){
  FuncDef *pDef;
  pDef = sqlite3FindFunction(db, zName, 2, SQLITE_UTF8, 0);
  if( ALWAYS(pDef) ){
    pDef->funcFlags |= flagVal;
  }
  pDef = sqlite3FindFunction(db, zName, 3, SQLITE_UTF8, 0);
  if( pDef ){
    pDef->funcFlags |= flagVal;
  }
}