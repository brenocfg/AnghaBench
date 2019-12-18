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
struct TYPE_4__ {struct TYPE_4__* aArg; struct TYPE_4__* aOp; } ;
typedef  TYPE_1__ ReCompiled ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

void re_free(ReCompiled *pRe){
  if( pRe ){
    sqlite3_free(pRe->aOp);
    sqlite3_free(pRe->aArg);
    sqlite3_free(pRe);
  }
}