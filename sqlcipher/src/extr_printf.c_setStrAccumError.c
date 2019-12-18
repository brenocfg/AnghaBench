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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int /*<<< orphan*/  db; scalar_t__ mxAlloc; scalar_t__ accError; } ;
typedef  TYPE_1__ StrAccum ;

/* Variables and functions */
 scalar_t__ SQLITE_NOMEM ; 
 scalar_t__ SQLITE_TOOBIG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ErrorToParser (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_str_reset (TYPE_1__*) ; 

__attribute__((used)) static void setStrAccumError(StrAccum *p, u8 eError){
  assert( eError==SQLITE_NOMEM || eError==SQLITE_TOOBIG );
  p->accError = eError;
  if( p->mxAlloc ) sqlite3_str_reset(p);
  if( eError==SQLITE_TOOBIG ) sqlite3ErrorToParser(p->db, eError);
}