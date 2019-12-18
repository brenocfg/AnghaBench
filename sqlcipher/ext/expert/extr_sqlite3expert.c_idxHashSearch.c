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
struct TYPE_3__ {char const* zVal; } ;
typedef  TYPE_1__ IdxHashEntry ;
typedef  int /*<<< orphan*/  IdxHash ;

/* Variables and functions */
 TYPE_1__* idxHashFind (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static const char *idxHashSearch(IdxHash *pHash, const char *zKey, int nKey){
  IdxHashEntry *pEntry = idxHashFind(pHash, zKey, nKey);
  if( pEntry ) return pEntry->zVal;
  return 0;
}