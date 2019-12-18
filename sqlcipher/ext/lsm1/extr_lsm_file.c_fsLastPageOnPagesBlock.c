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
typedef  int /*<<< orphan*/  LsmPgno ;
typedef  int /*<<< orphan*/  FileSystem ;

/* Variables and functions */
 int /*<<< orphan*/  fsLastPageOnBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsPageToBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

LsmPgno fsLastPageOnPagesBlock(FileSystem *pFS, LsmPgno iPg){
  return fsLastPageOnBlock(pFS, fsPageToBlock(pFS, iPg));
}