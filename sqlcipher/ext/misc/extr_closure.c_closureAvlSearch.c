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
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_4__ {scalar_t__ id; struct TYPE_4__* pAfter; struct TYPE_4__* pBefore; } ;
typedef  TYPE_1__ closure_avl ;

/* Variables and functions */

__attribute__((used)) static closure_avl *closureAvlSearch(closure_avl *p, sqlite3_int64 id){
  while( p && id!=p->id ){
    p = (id<p->id) ? p->pBefore : p->pAfter;
  }
  return p;
}