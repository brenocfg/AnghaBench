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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_4__ {int nFanout; } ;
typedef  TYPE_1__ DbParameters ;

/* Variables and functions */
 int DB_KEY_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dbCksum ; 
 int /*<<< orphan*/  dbFormatKey (TYPE_1__*,int,int,char*) ; 
 int strlen (char*) ; 
 int tdb_scan (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 dbComputeCksum(
  DbParameters *pParam,           /* Database parameters */
  TestDb *pDb,                    /* Database connection handle */
  int iLevel,                     /* Level of checksum to compute */
  int iKey,                       /* Compute checksum for this key */
  int *pRc                        /* IN/OUT: Error code */
){
  u32 cksum = 0;
  if( *pRc==0 ){
    int nFirst;
    int nLast;
    int iFirst = 0;
    int iLast = 0;
    int i;
    int f = 1;
    char zFirst[DB_KEY_BYTES];
    char zLast[DB_KEY_BYTES];

    assert( iLevel>=1 );
    for(i=0; i<iLevel; i++) f = f * pParam->nFanout;

    iFirst = f*(iKey/f);
    iLast = iFirst + f - 1;
    dbFormatKey(pParam, iLevel-1, iFirst, zFirst);
    dbFormatKey(pParam, iLevel-1, iLast, zLast);
    nFirst = strlen(zFirst);
    nLast = strlen(zLast);

    *pRc = tdb_scan(pDb, (u32*)&cksum, 0, zFirst, nFirst, zLast, nLast,dbCksum);
  }

  return cksum;
}