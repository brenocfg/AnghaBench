#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ i64 ;

/* Variables and functions */
 int lsmSqlite4PutVarint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int lsmVarintPut64(u8 *aData, i64 iVal){
  return lsmSqlite4PutVarint64(aData, (u64)iVal);
}