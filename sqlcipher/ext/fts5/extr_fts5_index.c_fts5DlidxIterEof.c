#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* aLvl; } ;
struct TYPE_7__ {scalar_t__ rc; } ;
struct TYPE_6__ {scalar_t__ bEof; } ;
typedef  TYPE_2__ Fts5Index ;
typedef  TYPE_3__ Fts5DlidxIter ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 

__attribute__((used)) static int fts5DlidxIterEof(Fts5Index *p, Fts5DlidxIter *pIter){
  return p->rc!=SQLITE_OK || pIter->aLvl[0].bEof;
}