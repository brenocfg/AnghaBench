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
struct TYPE_3__ {scalar_t__ xCmp; scalar_t__ pUser; int /*<<< orphan*/  zName; } ;
typedef  TYPE_1__ CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ binCollFunc ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int sqlite3IsBinary(const CollSeq *p){
  assert( p==0 || p->xCmp!=binCollFunc || p->pUser!=0
            || strcmp(p->zName,"BINARY")==0 );
  return p==0 || (p->xCmp==binCollFunc && p->pUser==0);
}