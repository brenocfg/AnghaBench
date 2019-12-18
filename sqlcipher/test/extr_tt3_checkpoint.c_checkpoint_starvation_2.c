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
struct TYPE_7__ {scalar_t__ nMaxFrame; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Error ;
typedef  TYPE_2__ CheckpointStarvationCtx ;

/* Variables and functions */
 scalar_t__ CHECKPOINT_STARVATION_FRAMELIMIT ; 
 int /*<<< orphan*/  SQLITE_CHECKPOINT_RESTART ; 
 int /*<<< orphan*/  checkpoint_starvation_main (int,TYPE_2__*) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_1__*) ; 
 int /*<<< orphan*/  test_error (TYPE_1__*,char*,scalar_t__) ; 

__attribute__((used)) static void checkpoint_starvation_2(int nMs){
  Error err = {0};
  CheckpointStarvationCtx ctx = { SQLITE_CHECKPOINT_RESTART, 0 };
  checkpoint_starvation_main(nMs, &ctx);
  if( ctx.nMaxFrame>CHECKPOINT_STARVATION_FRAMELIMIT+10 ){
    test_error(&err, "WAL grew too large - %d frames", ctx.nMaxFrame);
  }
  print_and_free_err(&err);
}