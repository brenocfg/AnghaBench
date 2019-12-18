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
struct TYPE_5__ {int /*<<< orphan*/  b; int /*<<< orphan*/  dlw; int /*<<< orphan*/  plw; } ;
typedef  TYPE_1__ DLCollector ;

/* Variables and functions */
 int /*<<< orphan*/  SCRAMBLE (TYPE_1__*) ; 
 int /*<<< orphan*/  dataBufferDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlwDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plwDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static void dlcDelete(DLCollector *pCollector){
  plwDestroy(&pCollector->plw);
  dlwDestroy(&pCollector->dlw);
  dataBufferDestroy(&pCollector->b);
  SCRAMBLE(pCollector);
  sqlite3_free(pCollector);
}