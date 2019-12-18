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
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_5__ {scalar_t__ nData; scalar_t__ pData; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
typedef  TYPE_2__ LeafWriter ;

/* Variables and functions */
 int VARINT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int leafWriterInternalFlush (int /*<<< orphan*/ *,TYPE_2__*,int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int putVarint (char*,int) ; 

__attribute__((used)) static int leafWriterInlineFlush(fulltext_vtab *v, LeafWriter *pWriter,
                                 const char *pTerm, int nTerm,
                                 int iDoclistData){
  char c[VARINT_MAX+VARINT_MAX];
  int iData, n = putVarint(c, 0);
  n += putVarint(c+n, nTerm);

  /* There should always be room for the header.  Even if pTerm shared
  ** a substantial prefix with the previous term, the entire prefix
  ** could be constructed from earlier data in the doclist, so there
  ** should be room.
  */
  assert( iDoclistData>=n+nTerm );

  iData = iDoclistData-(n+nTerm);
  memcpy(pWriter->data.pData+iData, c, n);
  memcpy(pWriter->data.pData+iData+n, pTerm, nTerm);

  return leafWriterInternalFlush(v, pWriter, iData, pWriter->data.nData-iData);
}