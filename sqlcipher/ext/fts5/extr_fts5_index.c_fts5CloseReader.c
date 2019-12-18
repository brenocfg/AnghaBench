#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_blob ;
struct TYPE_3__ {int /*<<< orphan*/ * pReader; } ;
typedef  TYPE_1__ Fts5Index ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_blob_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts5CloseReader(Fts5Index *p){
  if( p->pReader ){
    sqlite3_blob *pReader = p->pReader;
    p->pReader = 0;
    sqlite3_blob_close(pReader);
  }
}