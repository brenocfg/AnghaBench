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

/* Variables and functions */
 int /*<<< orphan*/  fatalError (char*,int) ; 
 void* realloc (void*,int) ; 

__attribute__((used)) static void *safe_realloc(void *pOld, int szNew){
  void *pNew = realloc(pOld, szNew<=0 ? 1 : szNew);
  if( pNew==0 ) fatalError("unable to realloc for %d bytes", szNew);
  return pNew;
}