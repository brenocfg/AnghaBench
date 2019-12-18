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
typedef  int i64 ;

/* Variables and functions */
 int FTS5_DATA_DLI_B ; 
 int FTS5_DATA_HEIGHT_B ; 
 int FTS5_DATA_ID_B ; 
 int FTS5_DATA_PAGE_B ; 

__attribute__((used)) static void fts5DecodeRowid(
  i64 iRowid,                     /* Rowid from %_data table */
  int *piSegid,                   /* OUT: Segment id */
  int *pbDlidx,                   /* OUT: Dlidx flag */
  int *piHeight,                  /* OUT: Height */
  int *piPgno                     /* OUT: Page number */
){
  *piPgno = (int)(iRowid & (((i64)1 << FTS5_DATA_PAGE_B) - 1));
  iRowid >>= FTS5_DATA_PAGE_B;

  *piHeight = (int)(iRowid & (((i64)1 << FTS5_DATA_HEIGHT_B) - 1));
  iRowid >>= FTS5_DATA_HEIGHT_B;

  *pbDlidx = (int)(iRowid & 0x0001);
  iRowid >>= FTS5_DATA_DLI_B;

  *piSegid = (int)(iRowid & (((i64)1 << FTS5_DATA_ID_B) - 1));
}