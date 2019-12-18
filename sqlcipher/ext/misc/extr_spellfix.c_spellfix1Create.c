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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int spellfix1Init (int,int /*<<< orphan*/ *,void*,int,char const* const*,int /*<<< orphan*/ **,char**) ; 

__attribute__((used)) static int spellfix1Create(
  sqlite3 *db,
  void *pAux,
  int argc, const char *const*argv,
  sqlite3_vtab **ppVTab,
  char **pzErr
){
  return spellfix1Init(1, db, pAux, argc, argv, ppVTab, pzErr);
}