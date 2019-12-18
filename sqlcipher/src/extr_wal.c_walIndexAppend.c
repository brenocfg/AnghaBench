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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
typedef  int ht_slot ;
struct TYPE_3__ {void* iZero; int* aHash; void** aPgno; } ;
typedef  TYPE_1__ WalHashLoc ;
typedef  int /*<<< orphan*/  Wal ;

/* Variables and functions */
 int HASHTABLE_NSLOT ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  walCleanupHash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walFramePage (void*) ; 
 int walHash (void*) ; 
 int walHashGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int walNextHash (int) ; 

__attribute__((used)) static int walIndexAppend(Wal *pWal, u32 iFrame, u32 iPage){
  int rc;                         /* Return code */
  WalHashLoc sLoc;                /* Wal-index hash table location */

  rc = walHashGet(pWal, walFramePage(iFrame), &sLoc);

  /* Assuming the wal-index file was successfully mapped, populate the
  ** page number array and hash table entry.
  */
  if( rc==SQLITE_OK ){
    int iKey;                     /* Hash table key */
    int idx;                      /* Value to write to hash-table slot */
    int nCollide;                 /* Number of hash collisions */

    idx = iFrame - sLoc.iZero;
    assert( idx <= HASHTABLE_NSLOT/2 + 1 );
    
    /* If this is the first entry to be added to this hash-table, zero the
    ** entire hash table and aPgno[] array before proceeding. 
    */
    if( idx==1 ){
      int nByte = (int)((u8 *)&sLoc.aHash[HASHTABLE_NSLOT]
                               - (u8 *)&sLoc.aPgno[1]);
      memset((void*)&sLoc.aPgno[1], 0, nByte);
    }

    /* If the entry in aPgno[] is already set, then the previous writer
    ** must have exited unexpectedly in the middle of a transaction (after
    ** writing one or more dirty pages to the WAL to free up memory). 
    ** Remove the remnants of that writers uncommitted transaction from 
    ** the hash-table before writing any new entries.
    */
    if( sLoc.aPgno[idx] ){
      walCleanupHash(pWal);
      assert( !sLoc.aPgno[idx] );
    }

    /* Write the aPgno[] array entry and the hash-table slot. */
    nCollide = idx;
    for(iKey=walHash(iPage); sLoc.aHash[iKey]; iKey=walNextHash(iKey)){
      if( (nCollide--)==0 ) return SQLITE_CORRUPT_BKPT;
    }
    sLoc.aPgno[idx] = iPage;
    sLoc.aHash[iKey] = (ht_slot)idx;

#ifdef SQLITE_ENABLE_EXPENSIVE_ASSERT
    /* Verify that the number of entries in the hash table exactly equals
    ** the number of entries in the mapping region.
    */
    {
      int i;           /* Loop counter */
      int nEntry = 0;  /* Number of entries in the hash table */
      for(i=0; i<HASHTABLE_NSLOT; i++){ if( sLoc.aHash[i] ) nEntry++; }
      assert( nEntry==idx );
    }

    /* Verify that the every entry in the mapping region is reachable
    ** via the hash table.  This turns out to be a really, really expensive
    ** thing to check, so only do this occasionally - not on every
    ** iteration.
    */
    if( (idx&0x3ff)==0 ){
      int i;           /* Loop counter */
      for(i=1; i<=idx; i++){
        for(iKey=walHash(sLoc.aPgno[i]);
            sLoc.aHash[iKey];
            iKey=walNextHash(iKey)){
          if( sLoc.aHash[iKey]==i ) break;
        }
        assert( sLoc.aHash[iKey]==i );
      }
    }
#endif /* SQLITE_ENABLE_EXPENSIVE_ASSERT */
  }


  return rc;
}