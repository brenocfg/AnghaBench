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
typedef  int /*<<< orphan*/  TestDb ;

/* Variables and functions */
 int test_bt_open (char*,char const*,int,int /*<<< orphan*/ **) ; 

int test_fbts_open(
  const char *zSpec, 
  const char *zFilename, 
  int bClear, 
  TestDb **ppDb
){
  return test_bt_open("fast=1 blksz=32K pagesz=512", zFilename, bClear, ppDb);
}