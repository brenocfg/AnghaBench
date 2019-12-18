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
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  InteriorReader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  interiorReaderAtEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interiorReaderCurrentBlockid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interiorReaderDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interiorReaderInit (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interiorReaderStep (int /*<<< orphan*/ *) ; 
 scalar_t__ interiorReaderTermCmp (int /*<<< orphan*/ *,char const*,int,int) ; 

__attribute__((used)) static void getChildrenContaining(const char *pData, int nData,
                                  const char *pTerm, int nTerm, int isPrefix,
                                  sqlite_int64 *piStartChild,
                                  sqlite_int64 *piEndChild){
  InteriorReader reader;

  assert( nData>1 );
  assert( *pData!='\0' );
  interiorReaderInit(pData, nData, &reader);

  /* Scan for the first child which could contain pTerm/nTerm. */
  while( !interiorReaderAtEnd(&reader) ){
    if( interiorReaderTermCmp(&reader, pTerm, nTerm, 0)>0 ) break;
    interiorReaderStep(&reader);
  }
  *piStartChild = interiorReaderCurrentBlockid(&reader);

  /* Keep scanning to find a term greater than our term, using prefix
  ** comparison if indicated.  If isPrefix is false, this will be the
  ** same blockid as the starting block.
  */
  while( !interiorReaderAtEnd(&reader) ){
    if( interiorReaderTermCmp(&reader, pTerm, nTerm, isPrefix)>0 ) break;
    interiorReaderStep(&reader);
  }
  *piEndChild = interiorReaderCurrentBlockid(&reader);

  interiorReaderDestroy(&reader);

  /* Children must ascend, and if !prefix, both must be the same. */
  assert( *piEndChild>=*piStartChild );
  assert( isPrefix || *piStartChild==*piEndChild );
}