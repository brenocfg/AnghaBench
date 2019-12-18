#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mayAbort; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 TYPE_1__* sqlite3ParseToplevel (TYPE_1__*) ; 

void sqlite3MayAbort(Parse *pParse){
  Parse *pToplevel = sqlite3ParseToplevel(pParse);
  pToplevel->mayAbort = 1;
}