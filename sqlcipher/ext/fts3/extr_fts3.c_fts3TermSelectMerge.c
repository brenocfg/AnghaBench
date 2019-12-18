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
struct TYPE_5__ {char** aaOutput; int* anOutput; } ;
typedef  TYPE_1__ TermSelect ;
struct TYPE_6__ {int /*<<< orphan*/  bDescIdx; } ;
typedef  TYPE_2__ Fts3Table ;

/* Variables and functions */
 scalar_t__ FTS3_VARINT_MAX ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SizeofArray (char**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3DoclistOrMerge (int /*<<< orphan*/ ,char*,int,char*,int,char**,int*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc (scalar_t__) ; 

__attribute__((used)) static int fts3TermSelectMerge(
  Fts3Table *p,                   /* FTS table handle */
  TermSelect *pTS,                /* TermSelect object to merge into */
  char *aDoclist,                 /* Pointer to doclist */
  int nDoclist                    /* Size of aDoclist in bytes */
){
  if( pTS->aaOutput[0]==0 ){
    /* If this is the first term selected, copy the doclist to the output
    ** buffer using memcpy(). 
    **
    ** Add FTS3_VARINT_MAX bytes of unused space to the end of the 
    ** allocation. This is so as to ensure that the buffer is big enough
    ** to hold the current doclist AND'd with any other doclist. If the
    ** doclists are stored in order=ASC order, this padding would not be
    ** required (since the size of [doclistA AND doclistB] is always less
    ** than or equal to the size of [doclistA] in that case). But this is
    ** not true for order=DESC. For example, a doclist containing (1, -1) 
    ** may be smaller than (-1), as in the first example the -1 may be stored
    ** as a single-byte delta, whereas in the second it must be stored as a
    ** FTS3_VARINT_MAX byte varint.
    **
    ** Similar padding is added in the fts3DoclistOrMerge() function.
    */
    pTS->aaOutput[0] = sqlite3_malloc(nDoclist + FTS3_VARINT_MAX + 1);
    pTS->anOutput[0] = nDoclist;
    if( pTS->aaOutput[0] ){
      memcpy(pTS->aaOutput[0], aDoclist, nDoclist);
      memset(&pTS->aaOutput[0][nDoclist], 0, FTS3_VARINT_MAX);
    }else{
      return SQLITE_NOMEM;
    }
  }else{
    char *aMerge = aDoclist;
    int nMerge = nDoclist;
    int iOut;

    for(iOut=0; iOut<SizeofArray(pTS->aaOutput); iOut++){
      if( pTS->aaOutput[iOut]==0 ){
        assert( iOut>0 );
        pTS->aaOutput[iOut] = aMerge;
        pTS->anOutput[iOut] = nMerge;
        break;
      }else{
        char *aNew;
        int nNew;

        int rc = fts3DoclistOrMerge(p->bDescIdx, aMerge, nMerge, 
            pTS->aaOutput[iOut], pTS->anOutput[iOut], &aNew, &nNew
        );
        if( rc!=SQLITE_OK ){
          if( aMerge!=aDoclist ) sqlite3_free(aMerge);
          return rc;
        }

        if( aMerge!=aDoclist ) sqlite3_free(aMerge);
        sqlite3_free(pTS->aaOutput[iOut]);
        pTS->aaOutput[iOut] = 0;
  
        aMerge = aNew;
        nMerge = nNew;
        if( (iOut+1)==SizeofArray(pTS->aaOutput) ){
          pTS->aaOutput[iOut] = aMerge;
          pTS->anOutput[iOut] = nMerge;
        }
      }
    }
  }
  return SQLITE_OK;
}