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
struct TYPE_4__ {struct TYPE_4__* pAfter; struct TYPE_4__* pBefore; int /*<<< orphan*/  zKey; } ;
typedef  TYPE_1__ amatch_avl ;

/* Variables and functions */
 int strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static amatch_avl *amatchAvlSearch(amatch_avl *p, const char *zKey){
  int c;
  while( p && (c = strcmp(zKey, p->zKey))!=0 ){
    p = (c<0) ? p->pBefore : p->pAfter;
  }
  return p;
}