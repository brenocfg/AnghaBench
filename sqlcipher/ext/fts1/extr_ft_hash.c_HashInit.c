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
struct TYPE_3__ {int keyClass; int copyKey; int /*<<< orphan*/  xFree; int /*<<< orphan*/  xMalloc; scalar_t__ ht; scalar_t__ htsize; scalar_t__ count; scalar_t__ first; } ;
typedef  TYPE_1__ Hash ;

/* Variables and functions */
 int HASH_BINARY ; 
 int HASH_INT ; 
 int HASH_POINTER ; 
 int HASH_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  malloc_and_zero ; 

void HashInit(Hash *pNew, int keyClass, int copyKey){
  assert( pNew!=0 );
  assert( keyClass>=HASH_STRING && keyClass<=HASH_BINARY );
  pNew->keyClass = keyClass;
#if 0
  if( keyClass==HASH_POINTER || keyClass==HASH_INT ) copyKey = 0;
#endif
  pNew->copyKey = copyKey;
  pNew->first = 0;
  pNew->count = 0;
  pNew->htsize = 0;
  pNew->ht = 0;
  pNew->xMalloc = malloc_and_zero;
  pNew->xFree = free;
}