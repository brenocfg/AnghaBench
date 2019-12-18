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
struct TYPE_3__ {void* data; } ;
typedef  TYPE_1__ Fts3HashElem ;
typedef  int /*<<< orphan*/  Fts3Hash ;

/* Variables and functions */
 TYPE_1__* sqlite3Fts3HashFindElem (int /*<<< orphan*/  const*,void const*,int) ; 

void *sqlite3Fts3HashFind(const Fts3Hash *pH, const void *pKey, int nKey){
  Fts3HashElem *pElem;            /* The element that matches key (if any) */

  pElem = sqlite3Fts3HashFindElem(pH, pKey, nKey);
  return pElem ? pElem->data : 0;
}