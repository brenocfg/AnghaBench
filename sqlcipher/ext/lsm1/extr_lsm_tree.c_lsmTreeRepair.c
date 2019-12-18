#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  treehdr; TYPE_2__* pShmhdr; } ;
typedef  TYPE_1__ lsm_db ;
typedef  int /*<<< orphan*/  TreeHeader ;
struct TYPE_7__ {int /*<<< orphan*/  hdr2; int /*<<< orphan*/  hdr1; } ;
typedef  TYPE_2__ ShmHeader ;

/* Variables and functions */
 int LSM_OK ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ treeHeaderChecksumOk (int /*<<< orphan*/ *) ; 
 int treeRepairList (TYPE_1__*) ; 
 int treeRepairPtrs (TYPE_1__*) ; 

int lsmTreeRepair(lsm_db *db){
  int rc = LSM_OK;
  TreeHeader hdr;
  ShmHeader *pHdr = db->pShmhdr;

  /* Ensure that the two tree-headers are consistent. Copy one over the other
  ** if necessary. Prefer the data from a tree-header for which the checksum
  ** computes. Or, if they both compute, prefer tree-header-1.  */
  if( memcmp(&pHdr->hdr1, &pHdr->hdr2, sizeof(TreeHeader)) ){
    if( treeHeaderChecksumOk(&pHdr->hdr1) ){
      memcpy(&pHdr->hdr2, &pHdr->hdr1, sizeof(TreeHeader));
    }else{
      memcpy(&pHdr->hdr1, &pHdr->hdr2, sizeof(TreeHeader));
    }
  }

  /* Save the connections current copy of the tree-header. It will be 
  ** restored before returning.  */
  memcpy(&hdr, &db->treehdr, sizeof(TreeHeader));

  /* Walk the tree. Zero any v2 pointers with a transaction-id greater than
  ** the transaction-id currently in the tree-headers.  */
  rc = treeRepairPtrs(db);

  /* Repair the linked list of shared-memory chunks. */
  if( rc==LSM_OK ){
    rc = treeRepairList(db);
  }

  memcpy(&db->treehdr, &hdr, sizeof(TreeHeader));
  return rc;
}