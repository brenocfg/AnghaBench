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
struct TYPE_3__ {scalar_t__ serial; } ;
typedef  TYPE_1__ strm_txn ;

/* Variables and functions */
 int STRM_NG ; 

__attribute__((used)) static int
txn_retry(strm_txn* txn)
{
  txn->serial = 0;              /* retry mark */
  return STRM_NG;
}