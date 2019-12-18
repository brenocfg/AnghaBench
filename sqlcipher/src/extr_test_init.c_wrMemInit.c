#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int (* xInit ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  pAppData; } ;
struct TYPE_4__ {int mem_init; TYPE_1__ mem; scalar_t__ mem_fail; } ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__ wrapped ; 

__attribute__((used)) static int wrMemInit(void *pAppData){
  int rc;
  if( wrapped.mem_fail ){
    rc = SQLITE_ERROR;
  }else{
    rc = wrapped.mem.xInit(wrapped.mem.pAppData);
  }
  if( rc==SQLITE_OK ){
    wrapped.mem_init = 1;
  }
  return rc;
}