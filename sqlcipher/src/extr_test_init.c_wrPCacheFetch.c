#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_pcache_page ;
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_3__ {int /*<<< orphan*/ * (* xFetch ) (int /*<<< orphan*/ *,unsigned int,int) ;} ;
struct TYPE_4__ {TYPE_1__ pcache; } ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,unsigned int,int) ; 
 TYPE_2__ wrapped ; 

__attribute__((used)) static sqlite3_pcache_page *wrPCacheFetch(sqlite3_pcache *p, unsigned a, int b){
  return wrapped.pcache.xFetch(p, a, b);
}