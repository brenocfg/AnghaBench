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
typedef  int /*<<< orphan*/  DocList ;

/* Variables and functions */
 int /*<<< orphan*/  readDocid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readerInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sqlite_int64 firstDocid(DocList *d){
  DocListReader r;
  readerInit(&r, d);
  return readDocid(&r);
}