#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* xPagecount ) (scalar_t__) ;} ;
struct TYPE_7__ {TYPE_1__ pcache2; } ;
struct TYPE_6__ {scalar_t__ pCache; } ;
typedef  TYPE_2__ PCache ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__ sqlite3GlobalConfig ; 
 int stub1 (scalar_t__) ; 

int sqlite3PcachePagecount(PCache *pCache){
  assert( pCache->pCache!=0 );
  return sqlite3GlobalConfig.pcache2.xPagecount(pCache->pCache);
}