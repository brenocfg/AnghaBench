#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_2__ {int /*<<< orphan*/ * data; scalar_t__ used; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int HEAP_ZERO_MEMORY ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int dwBlockSize ; 
 size_t dwMaxBlock ; 
 TYPE_1__* lpMemArea ; 

__attribute__((used)) static LPVOID DPLAYX_PrivHeapAlloc( DWORD flags, DWORD size )
{
  LPVOID lpvArea = NULL;
  UINT   uBlockUsed;

  if( size > (dwBlockSize - sizeof(BOOL)) )
  {
    FIXME( "Size exceeded. Request of 0x%08x\n", size );
    size = dwBlockSize - sizeof(BOOL);
  }

  /* Find blank area */
  uBlockUsed = 0;
  while( uBlockUsed < dwMaxBlock && lpMemArea[ uBlockUsed ].used ) { uBlockUsed++; }

  if( uBlockUsed < dwMaxBlock )
  {
    /* Set the area used */
    lpMemArea[ uBlockUsed ].used = TRUE;
    lpvArea = lpMemArea[ uBlockUsed ].data;
  }
  else
  {
    ERR( "No free block found\n" );
    return NULL;
  }

  if( flags & HEAP_ZERO_MEMORY )
  {
    ZeroMemory( lpvArea, size );
  }

  return lpvArea;
}