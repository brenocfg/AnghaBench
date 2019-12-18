#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  zSnippet; int /*<<< orphan*/  zOffset; int /*<<< orphan*/  aMatch; } ;
typedef  TYPE_1__ Snippet ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snippetClear(Snippet *p){
  sqlite3_free(p->aMatch);
  sqlite3_free(p->zOffset);
  sqlite3_free(p->zSnippet);
  CLEAR(p);
}