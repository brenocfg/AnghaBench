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
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  DocListReader ;

/* Variables and functions */
 int /*<<< orphan*/  atEnd (int /*<<< orphan*/ *) ; 
 scalar_t__ peekDocid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skipDocument (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int skipToDocid(DocListReader *pReader, sqlite_int64 iDocid){
  sqlite_int64 d = 0;
  while( !atEnd(pReader) && (d=peekDocid(pReader))<iDocid ){
    skipDocument(pReader);
  }
  return !atEnd(pReader) && d==iDocid;
}