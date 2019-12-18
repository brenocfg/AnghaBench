#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_4__ {int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ DocListReader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getVarint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readerAtEnd (TYPE_1__*) ; 

__attribute__((used)) static sqlite_int64 peekDocid(DocListReader *pReader){
  sqlite_int64 ret;
  assert( !readerAtEnd(pReader) );
  getVarint(pReader->p, &ret);
  return ret;
}