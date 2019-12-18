#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ bDisable; } ;
struct TYPE_5__ {scalar_t__ isInterrupted; } ;
struct TYPE_7__ {scalar_t__ nVdbeExec; TYPE_2__ lookaside; TYPE_1__ u1; scalar_t__ mallocFailed; } ;
typedef  TYPE_3__ sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void sqlite3OomClear(sqlite3 *db){
  if( db->mallocFailed && db->nVdbeExec==0 ){
    db->mallocFailed = 0;
    db->u1.isInterrupted = 0;
    assert( db->lookaside.bDisable>0 );
    db->lookaside.bDisable--;
  }
}