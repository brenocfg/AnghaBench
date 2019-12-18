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
struct TYPE_3__ {int /*<<< orphan*/  n; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ Fts5Token ;

/* Variables and functions */
 int SQLITE_OK ; 
 char* sqlite3Fts5Strndup (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5ParseStringFromToken(Fts5Token *pToken, char **pz){
  int rc = SQLITE_OK;
  *pz = sqlite3Fts5Strndup(&rc, pToken->p, pToken->n);
  return rc;
}