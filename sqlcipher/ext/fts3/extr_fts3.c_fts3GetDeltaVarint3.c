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
typedef  scalar_t__ sqlite3_int64 ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3Fts3GetVarint (char*,scalar_t__*) ; 

__attribute__((used)) static void fts3GetDeltaVarint3(
  char **pp,                      /* IN/OUT: Point to read varint from */
  char *pEnd,                     /* End of buffer */
  int bDescIdx,                   /* True if docids are descending */
  sqlite3_int64 *pVal             /* IN/OUT: Integer value */
){
  if( *pp>=pEnd ){
    *pp = 0;
  }else{
    sqlite3_int64 iVal;
    *pp += sqlite3Fts3GetVarint(*pp, &iVal);
    if( bDescIdx ){
      *pVal -= iVal;
    }else{
      *pVal += iVal;
    }
  }
}