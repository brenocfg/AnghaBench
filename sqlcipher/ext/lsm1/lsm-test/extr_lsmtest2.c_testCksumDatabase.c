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
typedef  int u32 ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_3__ {int nRow; scalar_t__ cksum2; scalar_t__ cksum1; } ;
typedef  TYPE_1__ Cksum ;

/* Variables and functions */
 scalar_t__ TEST_CKSUM_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scanCksumDb ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  tdb_scan (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int testCksumDatabase(
  TestDb *pDb,                    /* Database handle */
  char *zOut                      /* Buffer to write checksum to */
){
  Cksum cksum;
  memset(&cksum, 0, sizeof(Cksum));
  tdb_scan(pDb, (void *)&cksum, 0, 0, 0, 0, 0, scanCksumDb);
  sprintf(zOut, "%d %x %x", 
      cksum.nRow, (u32)cksum.cksum1, (u32)cksum.cksum2
  );
  assert( strlen(zOut)<TEST_CKSUM_BYTES );
  return cksum.nRow;
}