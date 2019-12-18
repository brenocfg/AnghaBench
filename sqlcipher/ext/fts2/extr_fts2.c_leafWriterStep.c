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
typedef  int /*<<< orphan*/  fulltext_vtab ;
typedef  int /*<<< orphan*/  LeafWriter ;
typedef  int /*<<< orphan*/  DLReader ;

/* Variables and functions */
 int /*<<< orphan*/  DL_DEFAULT ; 
 int /*<<< orphan*/  dlrDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlrInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int leafWriterStepMerge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int leafWriterStep(fulltext_vtab *v, LeafWriter *pWriter,
                          const char *pTerm, int nTerm,
                          const char *pData, int nData){
  int rc;
  DLReader reader;

  dlrInit(&reader, DL_DEFAULT, pData, nData);
  rc = leafWriterStepMerge(v, pWriter, pTerm, nTerm, &reader, 1);
  dlrDestroy(&reader);

  return rc;
}