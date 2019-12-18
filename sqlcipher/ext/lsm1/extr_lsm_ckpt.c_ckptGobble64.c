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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  i64 ;

/* Variables and functions */
 int /*<<< orphan*/  ckptRead64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static i64 ckptGobble64(u32 *a, int *piIn){
  int iIn = *piIn;
  *piIn += 2;
  return ckptRead64(&a[iIn]);
}