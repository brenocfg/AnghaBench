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
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_NG ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
void_txn(strm_stream* strm)
{
  strm_raise(strm, "invalid transaction");
  return STRM_NG;
}