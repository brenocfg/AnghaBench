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
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3ErrorMsg (int /*<<< orphan*/ *,char const*,int,int) ; 

void sqlite3SubselectError(Parse *pParse, int nActual, int nExpect){
  const char *zFmt = "sub-select returns %d columns - expected %d";
  sqlite3ErrorMsg(pParse, zFmt, nActual, nExpect);
}