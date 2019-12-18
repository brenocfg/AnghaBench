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
typedef  int /*<<< orphan*/  errcode_t ;
typedef  scalar_t__ blk64_t ;
typedef  long long __u64 ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _CloseDisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _Ext2OpenDevice (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,long long*,long long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _GetDeviceSize (int /*<<< orphan*/ ,long long*) ; 

errcode_t ext2fs_get_device_size2(const char *file, int blocksize, blk64_t *retblocks)
{
	errcode_t errcode = 0;
	__u64 Offset, Size = 0;
	HANDLE h;
	BOOLEAN Readonly;

	if (!_Ext2OpenDevice(file, TRUE, &h, &Offset, &Size, &Readonly, &errcode))
		return errcode;

	if (Size == 0LL)
		_GetDeviceSize(h, &Size);
	_CloseDisk(h);

	*retblocks = (blk64_t)(Size / blocksize);
	return 0;
}