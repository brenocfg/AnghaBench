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
struct TYPE_3__ {int keyClass; int copyKey; scalar_t__ ht; scalar_t__ htsize; scalar_t__ count; scalar_t__ first; } ;
typedef  TYPE_1__ fts2Hash ;

/* Variables and functions */
 int FTS2_HASH_BINARY ; 
 int FTS2_HASH_STRING ; 
 int /*<<< orphan*/  assert (int) ; 

void sqlite3Fts2HashInit(fts2Hash *pNew, int keyClass, int copyKey){
  assert( pNew!=0 );
  assert( keyClass>=FTS2_HASH_STRING && keyClass<=FTS2_HASH_BINARY );
  pNew->keyClass = keyClass;
  pNew->copyKey = copyKey;
  pNew->first = 0;
  pNew->count = 0;
  pNew->htsize = 0;
  pNew->ht = 0;
}