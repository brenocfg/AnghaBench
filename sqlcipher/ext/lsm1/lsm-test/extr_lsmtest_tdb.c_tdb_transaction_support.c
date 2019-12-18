#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ TestDb ;
struct TYPE_4__ {scalar_t__ xBegin; } ;

/* Variables and functions */
 scalar_t__ error_transaction_function ; 

int tdb_transaction_support(TestDb *pDb){
  return (pDb->pMethods->xBegin != error_transaction_function);
}