#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_6__ {int /*<<< orphan*/  nData; } ;
struct TYPE_5__ {TYPE_4__ data; } ;
typedef  TYPE_1__ LeafWriter ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  dataBufferReset (TYPE_4__*) ; 
 int leafWriterInternalFlush (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int leafWriterFlush(fulltext_vtab *v, LeafWriter *pWriter){
  int rc = leafWriterInternalFlush(v, pWriter, 0, pWriter->data.nData);
  if( rc!=SQLITE_OK ) return rc;

  /* Re-initialize the output buffer. */
  dataBufferReset(&pWriter->data);

  return SQLITE_OK;
}