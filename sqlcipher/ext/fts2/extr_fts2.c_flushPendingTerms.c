#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nPendingData; int /*<<< orphan*/  pendingTerms; } ;
typedef  TYPE_1__ fulltext_vtab ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  clearPendingTerms (TYPE_1__*) ; 
 int writeZeroSegment (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flushPendingTerms(fulltext_vtab *v){
  if( v->nPendingData>=0 ){
    int rc = writeZeroSegment(v, &v->pendingTerms);
    if( rc==SQLITE_OK ) clearPendingTerms(v);
    return rc;
  }
  return SQLITE_OK;
}