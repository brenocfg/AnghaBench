#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_10__ {scalar_t__ xCmp; } ;
struct TYPE_9__ {int /*<<< orphan*/  rc; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_ERROR_MISSING_COLLSEQ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  callCollNeeded (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_1__*,char*,char const*) ; 
 TYPE_2__* sqlite3FindCollSeq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ synthCollSeq (int /*<<< orphan*/ *,TYPE_2__*) ; 

CollSeq *sqlite3GetCollSeq(
  Parse *pParse,        /* Parsing context */
  u8 enc,               /* The desired encoding for the collating sequence */
  CollSeq *pColl,       /* Collating sequence with native encoding, or NULL */
  const char *zName     /* Collating sequence name */
){
  CollSeq *p;
  sqlite3 *db = pParse->db;

  p = pColl;
  if( !p ){
    p = sqlite3FindCollSeq(db, enc, zName, 0);
  }
  if( !p || !p->xCmp ){
    /* No collation sequence of this type for this encoding is registered.
    ** Call the collation factory to see if it can supply us with one.
    */
    callCollNeeded(db, enc, zName);
    p = sqlite3FindCollSeq(db, enc, zName, 0);
  }
  if( p && !p->xCmp && synthCollSeq(db, p) ){
    p = 0;
  }
  assert( !p || p->xCmp );
  if( p==0 ){
    sqlite3ErrorMsg(pParse, "no such collation sequence: %s", zName);
    pParse->rc = SQLITE_ERROR_MISSING_COLLSEQ;
  }
  return p;
}