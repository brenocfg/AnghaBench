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
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  DocListReader ;

/* Variables and functions */
 scalar_t__ atEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readDocid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skipPositionList (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sqlite_int64 nextDocid(DocListReader *pIn){
  skipPositionList(pIn);
  return atEnd(pIn) ? 0 : readDocid(pIn);
}