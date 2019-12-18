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
typedef  int /*<<< orphan*/  LeavesReader ;
typedef  int /*<<< orphan*/  LeafWriter ;
typedef  int /*<<< orphan*/  DLReader ;

/* Variables and functions */
 int /*<<< orphan*/  DL_DEFAULT ; 
 int MERGE_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dlrInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int leafWriterStepMerge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  leavesReaderData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leavesReaderDataBytes (int /*<<< orphan*/ *) ; 
 char* leavesReaderTerm (int /*<<< orphan*/ *) ; 
 int leavesReaderTermBytes (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int leavesReadersMerge(fulltext_vtab *v,
                              LeavesReader *pReaders, int nReaders,
                              LeafWriter *pWriter){
  DLReader dlReaders[MERGE_COUNT];
  const char *pTerm = leavesReaderTerm(pReaders);
  int i, nTerm = leavesReaderTermBytes(pReaders);

  assert( nReaders<=MERGE_COUNT );

  for(i=0; i<nReaders; i++){
    dlrInit(&dlReaders[i], DL_DEFAULT,
            leavesReaderData(pReaders+i),
            leavesReaderDataBytes(pReaders+i));
  }

  return leafWriterStepMerge(v, pWriter, pTerm, nTerm, dlReaders, nReaders);
}