#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct HashTable {scalar_t__ MaxKey; } ;
typedef  scalar_t__ GLuint ;

/* Variables and functions */
 scalar_t__ HashLookup (struct HashTable const*,scalar_t__) ; 

GLuint HashFindFreeKeyBlock(const struct HashTable *table, GLuint numKeys)
{
   GLuint maxKey = ~((GLuint) 0);
   if (maxKey - numKeys > table->MaxKey) {
      /* the quick solution */
      return table->MaxKey + 1;
   }
   else {
      /* the slow solution */
      GLuint freeCount = 0;
      GLuint freeStart = 0;
      GLuint key;
      for (key=0; key!=maxKey; key++) {
	 if (HashLookup(table, key)) {
	    /* darn, this key is already in use */
	    freeCount = 0;
	    freeStart = key+1;
	 }
	 else {
	    /* this key not in use, check if we've found enough */
	    freeCount++;
	    if (freeCount == numKeys) {
	       return freeStart;
	    }
	 }
      }
      /* cannot allocate a block of numKeys consecutive keys */
      return 0;
   }
}