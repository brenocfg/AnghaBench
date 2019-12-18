#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int h; } ;
typedef  TYPE_1__ unixFile ;
typedef  scalar_t__ sqlite3_int64 ;
typedef  int i64 ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  OSTRACE (char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SimulateIOError (int) ; 
 int /*<<< orphan*/  TIMER_ELAPSED ; 
 int /*<<< orphan*/  TIMER_END ; 
 int /*<<< orphan*/  TIMER_START ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int osPread (int,void*,int,scalar_t__) ; 
 int osPread64 (int,void*,int,scalar_t__) ; 
 int osRead (int,void*,int) ; 
 int /*<<< orphan*/  storeLastErrno (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int seekAndRead(unixFile *id, sqlite3_int64 offset, void *pBuf, int cnt){
  int got;
  int prior = 0;
#if (!defined(USE_PREAD) && !defined(USE_PREAD64))
  i64 newOffset;
#endif
  TIMER_START;
  assert( cnt==(cnt&0x1ffff) );
  assert( id->h>2 );
  do{
#if defined(USE_PREAD)
    got = osPread(id->h, pBuf, cnt, offset);
    SimulateIOError( got = -1 );
#elif defined(USE_PREAD64)
    got = osPread64(id->h, pBuf, cnt, offset);
    SimulateIOError( got = -1 );
#else
    newOffset = lseek(id->h, offset, SEEK_SET);
    SimulateIOError( newOffset = -1 );
    if( newOffset<0 ){
      storeLastErrno((unixFile*)id, errno);
      return -1;
    }
    got = osRead(id->h, pBuf, cnt);
#endif
    if( got==cnt ) break;
    if( got<0 ){
      if( errno==EINTR ){ got = 1; continue; }
      prior = 0;
      storeLastErrno((unixFile*)id,  errno);
      break;
    }else if( got>0 ){
      cnt -= got;
      offset += got;
      prior += got;
      pBuf = (void*)(got + (char*)pBuf);
    }
  }while( got>0 );
  TIMER_END;
  OSTRACE(("READ    %-3d %5d %7lld %llu\n",
            id->h, got+prior, offset-prior, TIMER_ELAPSED));
  return got+prior;
}