#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_6__ {int /*<<< orphan*/  a; } ;
struct TYPE_5__ {int nVertex; int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ GeoPoly ;
typedef  TYPE_2__ GeoBBox ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 TYPE_1__* geopolyBBox (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void geopolyBBoxFinal(
  sqlite3_context *context
){
  GeoPoly *p;
  GeoBBox *pBBox;
  pBBox = (GeoBBox*)sqlite3_aggregate_context(context, 0);
  if( pBBox==0 ) return;
  p = geopolyBBox(context, 0, pBBox->a, 0);
  if( p ){
    sqlite3_result_blob(context, p->hdr, 
       4+8*p->nVertex, SQLITE_TRANSIENT);
    sqlite3_free(p);
  }
}