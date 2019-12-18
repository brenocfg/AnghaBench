#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pLock; } ;
struct TYPE_4__ {int nFile; struct TYPE_4__* pNext; int /*<<< orphan*/  zFile; } ;
typedef  TYPE_1__ AsyncLock ;

/* Variables and functions */
 TYPE_3__ async ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static AsyncLock *findLock(const char *zName, int nName){
  AsyncLock *p = async.pLock;
  while( p && (p->nFile!=nName || memcmp(p->zFile, zName, nName)) ){
    p = p->pNext;
  }
  return p;
}