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
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_3__ {int /*<<< orphan*/  tv; } ;
typedef  TYPE_1__ strm_txn ;

/* Variables and functions */
 int /*<<< orphan*/  STRM_PTR_AUX ; 
 scalar_t__ strm_value_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static strm_txn*
get_txn(int argc, strm_value* args)
{
  strm_txn* txn;

  if (argc == 0) return NULL;
  txn = (strm_txn*)strm_value_ptr(args[0], STRM_PTR_AUX);
  if (!txn->tv) {
    return NULL;
  }
  return txn;
}