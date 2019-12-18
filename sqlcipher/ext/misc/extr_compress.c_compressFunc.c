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
 int Z_OK ; 
 int compress (unsigned char*,unsigned long*,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  sqlite3_free (unsigned char*) ; 
 unsigned char* sqlite3_malloc (unsigned long) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,unsigned char*,unsigned long,int /*<<< orphan*/  (*) (unsigned char*)) ; 
 unsigned char* sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 unsigned int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void compressFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const unsigned char *pIn;
  unsigned char *pOut;
  unsigned int nIn;
  unsigned long int nOut;
  unsigned char x[8];
  int rc;
  int i, j;

  pIn = sqlite3_value_blob(argv[0]);
  nIn = sqlite3_value_bytes(argv[0]);
  nOut = 13 + nIn + (nIn+999)/1000;
  pOut = sqlite3_malloc( nOut+5 );
  for(i=4; i>=0; i--){
    x[i] = (nIn >> (7*(4-i)))&0x7f;
  }
  for(i=0; i<4 && x[i]==0; i++){}
  for(j=0; i<=4; i++, j++) pOut[j] = x[i];
  pOut[j-1] |= 0x80;
  rc = compress(&pOut[j], &nOut, pIn, nIn);
  if( rc==Z_OK ){
    sqlite3_result_blob(context, pOut, nOut+j, sqlite3_free);
  }else{
    sqlite3_free(pOut);
  }
}