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
typedef  int /*<<< orphan*/  uint64_t ;
struct access_sys {scalar_t__ error_status; int eof; int /*<<< orphan*/  smb2fh; int /*<<< orphan*/  smb2; } ;
struct TYPE_4__ {struct access_sys* p_sys; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_SMB2_SET_ERROR (TYPE_1__*,char*,int) ; 
 int VLC_SUCCESS ; 
 scalar_t__ smb2_lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
FileSeek(stream_t *access, uint64_t i_pos)
{
    struct access_sys *sys = access->p_sys;

    if (sys->error_status != 0)
        return VLC_EGENERIC;

    if (smb2_lseek(sys->smb2, sys->smb2fh, i_pos, SEEK_SET, NULL) < 0)
    {
        VLC_SMB2_SET_ERROR(access, "smb2_seek_async", 1);
        return VLC_EGENERIC;
    }
    sys->eof = false;

    return VLC_SUCCESS;
}