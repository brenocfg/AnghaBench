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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int bGlobal; int nElem; int /*<<< orphan*/ * aMatchinfo; } ;
typedef  TYPE_1__ MatchinfoBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fts3MIBufferSetGlobal(MatchinfoBuffer *p){
  p->bGlobal = 1;
  memcpy(&p->aMatchinfo[2+p->nElem], &p->aMatchinfo[1], p->nElem*sizeof(u32));
}