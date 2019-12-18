#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_9__ {scalar_t__ nField; scalar_t__ default_rc; TYPE_2__* aMem; } ;
typedef  TYPE_1__ UnpackedRecord ;
struct TYPE_11__ {scalar_t__ nKeyField; int /*<<< orphan*/  db; int /*<<< orphan*/  enc; } ;
struct TYPE_10__ {scalar_t__ z; scalar_t__ szMalloc; int /*<<< orphan*/  db; int /*<<< orphan*/  enc; } ;
typedef  TYPE_2__ Mem ;
typedef  TYPE_3__ KeyInfo ;

/* Variables and functions */
 int CORRUPT_DB ; 
 int EIGHT_BYTE_ALIGNMENT (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t getVarint32 (unsigned char const*,size_t) ; 
 int /*<<< orphan*/  sqlite3VdbeMemSetNull (TYPE_2__*) ; 
 scalar_t__ sqlite3VdbeSerialGet (unsigned char const*,size_t,TYPE_2__*) ; 

void sqlite3VdbeRecordUnpack(
  KeyInfo *pKeyInfo,     /* Information about the record format */
  int nKey,              /* Size of the binary record */
  const void *pKey,      /* The binary record */
  UnpackedRecord *p      /* Populate this structure before returning. */
){
  const unsigned char *aKey = (const unsigned char *)pKey;
  u32 d; 
  u32 idx;                        /* Offset in aKey[] to read from */
  u16 u;                          /* Unsigned loop counter */
  u32 szHdr;
  Mem *pMem = p->aMem;

  p->default_rc = 0;
  assert( EIGHT_BYTE_ALIGNMENT(pMem) );
  idx = getVarint32(aKey, szHdr);
  d = szHdr;
  u = 0;
  while( idx<szHdr && d<=(u32)nKey ){
    u32 serial_type;

    idx += getVarint32(&aKey[idx], serial_type);
    pMem->enc = pKeyInfo->enc;
    pMem->db = pKeyInfo->db;
    /* pMem->flags = 0; // sqlite3VdbeSerialGet() will set this for us */
    pMem->szMalloc = 0;
    pMem->z = 0;
    d += sqlite3VdbeSerialGet(&aKey[d], serial_type, pMem);
    pMem++;
    if( (++u)>=p->nField ) break;
  }
  if( d>(u32)nKey && u ){
    assert( CORRUPT_DB );
    /* In a corrupt record entry, the last pMem might have been set up using 
    ** uninitialized memory. Overwrite its value with NULL, to prevent
    ** warnings from MSAN. */
    sqlite3VdbeMemSetNull(pMem-1);
  }
  assert( u<=pKeyInfo->nKeyField + 1 );
  p->nField = u;
}