#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u16 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {int nRef; int /*<<< orphan*/ * db; int /*<<< orphan*/  enc; void* nAllField; void* nKeyField; int /*<<< orphan*/ * aColl; int /*<<< orphan*/ * aSortOrder; } ;
typedef  TYPE_1__ KeyInfo ;
typedef  int /*<<< orphan*/  CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  ENC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* sqlite3DbMallocRawNN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3OomFault (int /*<<< orphan*/ *) ; 

KeyInfo *sqlite3KeyInfoAlloc(sqlite3 *db, int N, int X){
  int nExtra = (N+X)*(sizeof(CollSeq*)+1) - sizeof(CollSeq*);
  KeyInfo *p = sqlite3DbMallocRawNN(db, sizeof(KeyInfo) + nExtra);
  if( p ){
    p->aSortOrder = (u8*)&p->aColl[N+X];
    p->nKeyField = (u16)N;
    p->nAllField = (u16)(N+X);
    p->enc = ENC(db);
    p->db = db;
    p->nRef = 1;
    memset(&p[1], 0, nExtra);
  }else{
    sqlite3OomFault(db);
  }
  return p;
}