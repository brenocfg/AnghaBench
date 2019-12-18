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
typedef  int /*<<< orphan*/  lsm_db ;
typedef  int /*<<< orphan*/  LsmPgno ;

/* Variables and functions */
 int INFO_PAGE_DUMP_DATA ; 
 int INFO_PAGE_DUMP_HEX ; 
 int INFO_PAGE_DUMP_VALUES ; 
 int infoPageDump (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char**) ; 

int lsmInfoPageDump(
  lsm_db *pDb,                    /* Database handle */
  LsmPgno iPg,                    /* Page number of page to dump */
  int bHex,                       /* True to output key/value in hex form */
  char **pzOut                    /* OUT: lsmMalloc'd string */
){
  int flags = INFO_PAGE_DUMP_DATA | INFO_PAGE_DUMP_VALUES;
  if( bHex ) flags |= INFO_PAGE_DUMP_HEX;
  return infoPageDump(pDb, iPg, flags, pzOut);
}