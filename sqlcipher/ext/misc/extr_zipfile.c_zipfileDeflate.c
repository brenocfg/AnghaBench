#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int avail_in; scalar_t__ total_out; int /*<<< orphan*/  avail_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_DEFLATED ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  compressBound (int) ; 
 int deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deflateEnd (TYPE_1__*) ; 
 int /*<<< orphan*/  deflateInit2 (TYPE_1__*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_malloc64 (int /*<<< orphan*/ ) ; 
 char* sqlite3_mprintf (char*) ; 

__attribute__((used)) static int zipfileDeflate(
  const u8 *aIn, int nIn,         /* Input */
  u8 **ppOut, int *pnOut,         /* Output */
  char **pzErr                    /* OUT: Error message */
){
  sqlite3_int64 nAlloc = compressBound(nIn);
  u8 *aOut;
  int rc = SQLITE_OK;

  aOut = (u8*)sqlite3_malloc64(nAlloc);
  if( aOut==0 ){
    rc = SQLITE_NOMEM;
  }else{
    int res;
    z_stream str;
    memset(&str, 0, sizeof(str));
    str.next_in = (Bytef*)aIn;
    str.avail_in = nIn;
    str.next_out = aOut;
    str.avail_out = nAlloc;

    deflateInit2(&str, 9, Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY);
    res = deflate(&str, Z_FINISH);

    if( res==Z_STREAM_END ){
      *ppOut = aOut;
      *pnOut = (int)str.total_out;
    }else{
      sqlite3_free(aOut);
      *pzErr = sqlite3_mprintf("zipfile: deflate() error");
      rc = SQLITE_ERROR;
    }
    deflateEnd(&str);
  }

  return rc;
}