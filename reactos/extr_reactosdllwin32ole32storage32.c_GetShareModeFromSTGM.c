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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
#define  STGM_SHARE_DENY_NONE 131 
#define  STGM_SHARE_DENY_READ 130 
#define  STGM_SHARE_DENY_WRITE 129 
#define  STGM_SHARE_EXCLUSIVE 128 
 int STGM_SHARE_MODE (int) ; 
 int STGM_TRANSACTED ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static DWORD GetShareModeFromSTGM(DWORD stgm)
{
  switch (STGM_SHARE_MODE(stgm))
  {
  case 0:
    assert(stgm & STGM_TRANSACTED);
    /* fall-through */
  case STGM_SHARE_DENY_NONE:
    return FILE_SHARE_READ | FILE_SHARE_WRITE;
  case STGM_SHARE_DENY_READ:
    return FILE_SHARE_WRITE;
  case STGM_SHARE_DENY_WRITE:
  case STGM_SHARE_EXCLUSIVE:
    return FILE_SHARE_READ;
  }
  ERR("Invalid share mode!\n");
  assert(0);
  return 0;
}