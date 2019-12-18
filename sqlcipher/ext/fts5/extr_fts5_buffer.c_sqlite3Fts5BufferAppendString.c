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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ Fts5Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3Fts5BufferAppendBlob (int*,TYPE_1__*,int,int /*<<< orphan*/  const*) ; 
 scalar_t__ strlen (char const*) ; 

void sqlite3Fts5BufferAppendString(
  int *pRc,
  Fts5Buffer *pBuf, 
  const char *zStr
){
  int nStr = (int)strlen(zStr);
  sqlite3Fts5BufferAppendBlob(pRc, pBuf, nStr+1, (const u8*)zStr);
  pBuf->n--;
}