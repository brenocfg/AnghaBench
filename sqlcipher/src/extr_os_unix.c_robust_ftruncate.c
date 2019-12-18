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
 scalar_t__ EINTR ; 
 int SQLITE_OK ; 
 scalar_t__ errno ; 
 int osFtruncate (int,scalar_t__) ; 

__attribute__((used)) static int robust_ftruncate(int h, sqlite3_int64 sz){
  int rc;
#ifdef __ANDROID__
  /* On Android, ftruncate() always uses 32-bit offsets, even if 
  ** _FILE_OFFSET_BITS=64 is defined. This means it is unsafe to attempt to
  ** truncate a file to any size larger than 2GiB. Silently ignore any
  ** such attempts.  */
  if( sz>(sqlite3_int64)0x7FFFFFFF ){
    rc = SQLITE_OK;
  }else
#endif
  do{ rc = osFtruncate(h,sz); }while( rc<0 && errno==EINTR );
  return rc;
}