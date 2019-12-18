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
struct TYPE_6__ {int avail_in; int avail_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inflateEnd (TYPE_1__*) ; 
 int inflateInit2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_malloc (int) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zipfileCtxErrorMsg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  zipfileFree ; 

__attribute__((used)) static void zipfileInflate(
  sqlite3_context *pCtx,          /* Store result here */
  const u8 *aIn,                  /* Compressed data */
  int nIn,                        /* Size of buffer aIn[] in bytes */
  int nOut                        /* Expected output size */
){
  u8 *aRes = sqlite3_malloc(nOut);
  if( aRes==0 ){
    sqlite3_result_error_nomem(pCtx);
  }else{
    int err;
    z_stream str;
    memset(&str, 0, sizeof(str));

    str.next_in = (Byte*)aIn;
    str.avail_in = nIn;
    str.next_out = (Byte*)aRes;
    str.avail_out = nOut;

    err = inflateInit2(&str, -15);
    if( err!=Z_OK ){
      zipfileCtxErrorMsg(pCtx, "inflateInit2() failed (%d)", err);
    }else{
      err = inflate(&str, Z_NO_FLUSH);
      if( err!=Z_STREAM_END ){
        zipfileCtxErrorMsg(pCtx, "inflate() failed (%d)", err);
      }else{
        sqlite3_result_blob(pCtx, aRes, nOut, zipfileFree);
        aRes = 0;
      }
    }
    sqlite3_free(aRes);
    inflateEnd(&str);
  }
}