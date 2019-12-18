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
struct TYPE_3__ {scalar_t__ pSegments; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_blob_close (scalar_t__) ; 

void sqlite3Fts3SegmentsClose(Fts3Table *p){
  sqlite3_blob_close(p->pSegments);
  p->pSegments = 0;
}