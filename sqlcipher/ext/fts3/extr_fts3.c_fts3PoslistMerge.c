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
typedef  int sqlite3_int64 ;

/* Variables and functions */
 int FTS_CORRUPT_VTAB ; 
 int POSITION_LIST_END ; 
 char POS_COLUMN ; 
 char POS_END ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts3ColumnlistCopy (char**,char**) ; 
 int /*<<< orphan*/  fts3GetDeltaVarint (char**,int*) ; 
 int /*<<< orphan*/  fts3GetVarint32 (char*,int*) ; 
 int fts3PutColNumber (char**,int) ; 
 int /*<<< orphan*/  fts3PutDeltaVarint (char**,int*,int) ; 
 int /*<<< orphan*/  fts3ReadNextPos (char**,int*) ; 

__attribute__((used)) static int fts3PoslistMerge(
  char **pp,                      /* Output buffer */
  char **pp1,                     /* Left input list */
  char **pp2                      /* Right input list */
){
  char *p = *pp;
  char *p1 = *pp1;
  char *p2 = *pp2;

  while( *p1 || *p2 ){
    int iCol1;         /* The current column index in pp1 */
    int iCol2;         /* The current column index in pp2 */

    if( *p1==POS_COLUMN ){ 
      fts3GetVarint32(&p1[1], &iCol1);
      if( iCol1==0 ) return FTS_CORRUPT_VTAB;
    }
    else if( *p1==POS_END ) iCol1 = POSITION_LIST_END;
    else iCol1 = 0;

    if( *p2==POS_COLUMN ){
      fts3GetVarint32(&p2[1], &iCol2);
      if( iCol2==0 ) return FTS_CORRUPT_VTAB;
    }
    else if( *p2==POS_END ) iCol2 = POSITION_LIST_END;
    else iCol2 = 0;

    if( iCol1==iCol2 ){
      sqlite3_int64 i1 = 0;       /* Last position from pp1 */
      sqlite3_int64 i2 = 0;       /* Last position from pp2 */
      sqlite3_int64 iPrev = 0;
      int n = fts3PutColNumber(&p, iCol1);
      p1 += n;
      p2 += n;

      /* At this point, both p1 and p2 point to the start of column-lists
      ** for the same column (the column with index iCol1 and iCol2).
      ** A column-list is a list of non-negative delta-encoded varints, each 
      ** incremented by 2 before being stored. Each list is terminated by a
      ** POS_END (0) or POS_COLUMN (1). The following block merges the two lists
      ** and writes the results to buffer p. p is left pointing to the byte
      ** after the list written. No terminator (POS_END or POS_COLUMN) is
      ** written to the output.
      */
      fts3GetDeltaVarint(&p1, &i1);
      fts3GetDeltaVarint(&p2, &i2);
      do {
        fts3PutDeltaVarint(&p, &iPrev, (i1<i2) ? i1 : i2); 
        iPrev -= 2;
        if( i1==i2 ){
          fts3ReadNextPos(&p1, &i1);
          fts3ReadNextPos(&p2, &i2);
        }else if( i1<i2 ){
          fts3ReadNextPos(&p1, &i1);
        }else{
          fts3ReadNextPos(&p2, &i2);
        }
      }while( i1!=POSITION_LIST_END || i2!=POSITION_LIST_END );
    }else if( iCol1<iCol2 ){
      p1 += fts3PutColNumber(&p, iCol1);
      fts3ColumnlistCopy(&p, &p1);
    }else{
      p2 += fts3PutColNumber(&p, iCol2);
      fts3ColumnlistCopy(&p, &p2);
    }
  }

  *p++ = POS_END;
  *pp = p;
  *pp1 = p1 + 1;
  *pp2 = p2 + 1;
  return SQLITE_OK;
}