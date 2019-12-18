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
typedef  int /*<<< orphan*/  PLWriter ;
typedef  int /*<<< orphan*/  PLReader ;
typedef  int /*<<< orphan*/  DocListType ;
typedef  int /*<<< orphan*/  DataBuffer ;
typedef  int /*<<< orphan*/  DLWriter ;
typedef  int /*<<< orphan*/  DLReader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dlrAtEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlrDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlrDocid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlrInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  dlrStep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlwDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlwInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrAtEnd (int /*<<< orphan*/ *) ; 
 int plrColumn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrEndOffset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrPosition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrStartOffset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrStep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plwAdd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plwDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plwInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plwTerminate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void docListTrim(DocListType iType, const char *pData, int nData,
                        int iColumn, DocListType iOutType, DataBuffer *out){
  DLReader dlReader;
  DLWriter dlWriter;

  assert( iOutType<=iType );

  dlrInit(&dlReader, iType, pData, nData);
  dlwInit(&dlWriter, iOutType, out);

  while( !dlrAtEnd(&dlReader) ){
    PLReader plReader;
    PLWriter plWriter;
    int match = 0;

    plrInit(&plReader, &dlReader);

    while( !plrAtEnd(&plReader) ){
      if( iColumn==-1 || plrColumn(&plReader)==iColumn ){
        if( !match ){
          plwInit(&plWriter, &dlWriter, dlrDocid(&dlReader));
          match = 1;
        }
        plwAdd(&plWriter, plrColumn(&plReader), plrPosition(&plReader),
               plrStartOffset(&plReader), plrEndOffset(&plReader));
      }
      plrStep(&plReader);
    }
    if( match ){
      plwTerminate(&plWriter);
      plwDestroy(&plWriter);
    }

    plrDestroy(&plReader);
    dlrStep(&dlReader);
  }
  dlwDestroy(&dlWriter);
  dlrDestroy(&dlReader);
}