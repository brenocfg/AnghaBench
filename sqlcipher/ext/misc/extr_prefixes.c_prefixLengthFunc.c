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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 unsigned char* sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prefixLengthFunc(
  sqlite3_context *ctx,
  int nVal,
  sqlite3_value **apVal
){
  int nByte;                      /* Number of bytes to compare */
  int nRet = 0;                   /* Return value */
  const unsigned char *zL = sqlite3_value_text(apVal[0]);
  const unsigned char *zR = sqlite3_value_text(apVal[1]);
  int nL = sqlite3_value_bytes(apVal[0]);
  int nR = sqlite3_value_bytes(apVal[1]);
  int i;

  nByte = (nL > nR ? nL : nR);
  for(i=0; i<nByte; i++){
    if( zL[i]!=zR[i] ) break;
    if( (zL[i] & 0xC0)!=0x80 ) nRet++;
  }

  if( (zL[i] & 0xC0)==0x80 ) nRet--;
  sqlite3_result_int(ctx, nRet);
}