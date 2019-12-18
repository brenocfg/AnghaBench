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
typedef  int /*<<< orphan*/  sqlite3_module ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * sqlite3_malloc (int) ; 

__attribute__((used)) static int vtshimCopyModule(
  const sqlite3_module *pMod,   /* Source module to be copied */
  sqlite3_module **ppMod        /* Destination for copied module */
){
  sqlite3_module *p;
  if( !pMod || !ppMod ) return SQLITE_ERROR;
  p = sqlite3_malloc( sizeof(*p) );
  if( p==0 ) return SQLITE_NOMEM;
  memcpy(p, pMod, sizeof(*p));
  *ppMod = p;
  return SQLITE_OK;
}