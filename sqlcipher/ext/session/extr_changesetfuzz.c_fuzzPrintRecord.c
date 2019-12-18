#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_3__ {int nCol; scalar_t__* aPK; } ;
typedef  TYPE_1__ FuzzChangesetGroup ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  fuzzGetI64 (int*) ; 
 int /*<<< orphan*/  fuzzGetVarint (int*,int*) ; 
 int /*<<< orphan*/  memcpy (double*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int fuzzPrintRecord(FuzzChangesetGroup *pGrp, u8 **ppRec, int bPKOnly){
  int rc = SQLITE_OK;
  u8 *p = *ppRec;
  int i;
  const char *zPre = " (";

  for(i=0; i<pGrp->nCol; i++){
    if( bPKOnly==0 || pGrp->aPK[i] ){
      u8 eType = p++[0];
      switch( eType ){
        case 0x00:                    /* undefined */
          printf("%sn/a", zPre);
          break;

        case 0x01: {                  /* integer */
          sqlite3_int64 iVal = 0;
          iVal = fuzzGetI64(p);
          printf("%s%lld", zPre, iVal);
          p += 8;
          break;
        }

        case 0x02: {                  /* real */
          sqlite3_int64 iVal = 0;
          double fVal = 0.0;
          iVal = fuzzGetI64(p);
          memcpy(&fVal, &iVal, 8);
          printf("%s%f", zPre, fVal);
          p += 8;
          break;
        }

        case 0x03:                    /* text */
        case 0x04: {                  /* blob */
          int nTxt;
          p += fuzzGetVarint(p, &nTxt);
          printf("%s%s", zPre, eType==0x03 ? "'" : "X'");
          for(i=0; i<nTxt; i++){
            if( eType==0x03 ){
              printf("%c", p[i]);
            }else{
              char aHex[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                               '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
              };
              printf("%c", aHex[ p[i]>>4 ]);
              printf("%c", aHex[ p[i] & 0x0F ]);
            }
          }
          printf("'");
          p += nTxt;
          break;
        }

        case 0x05:                    /* null */
          printf("%sNULL", zPre);
          break;
      }
      zPre = ", ";
    }
  }
  printf(")");

  *ppRec = p;
  return rc;
}