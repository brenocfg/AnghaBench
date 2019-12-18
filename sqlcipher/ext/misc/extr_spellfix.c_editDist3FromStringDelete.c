#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int n; TYPE_1__* a; } ;
struct TYPE_5__ {TYPE_2__* apSubst; TYPE_2__* apDel; } ;
typedef  TYPE_2__ EditDist3FromString ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static void editDist3FromStringDelete(EditDist3FromString *p){
  int i;
  if( p ){
    for(i=0; i<p->n; i++){
      sqlite3_free(p->a[i].apDel);
      sqlite3_free(p->a[i].apSubst);
    }
    sqlite3_free(p);
  }
}