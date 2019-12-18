#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_2__ {scalar_t__ sz; scalar_t__ szMax; scalar_t__ aData; } ;
typedef  TYPE_1__ MemFile ;

/* Variables and functions */
 int SQLITE_FULL ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int memTruncate(sqlite3_file *pFile, sqlite_int64 size){
  MemFile *p = (MemFile *)pFile;
  if( size>p->sz ){
    if( size>p->szMax ) return SQLITE_FULL;
    memset(p->aData+p->sz, 0, size-p->sz);
  }
  p->sz = size; 
  return SQLITE_OK;
}