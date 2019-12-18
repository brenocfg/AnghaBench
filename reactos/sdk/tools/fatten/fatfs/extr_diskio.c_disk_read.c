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
typedef  int UINT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DRESULT ;
typedef  size_t BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  RES_ERROR ; 
 int /*<<< orphan*/  RES_OK ; 
 int /*<<< orphan*/  RES_PARERR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ ** driveHandle ; 
 size_t driveHandleCount ; 
 int fread (size_t*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

DRESULT disk_read(
    BYTE pdrv,		/* Physical drive nmuber (0..) */
    BYTE *buff,		/* Data buffer to store read data */
    DWORD sector,	/* Sector address (LBA) */
    UINT count		/* Number of sectors to read (1..128) */
    )
{
    DWORD result;

    if (pdrv < driveHandleCount)
    {
        if (driveHandle[pdrv] != NULL)
        {
            if (fseek(driveHandle[pdrv], sector * 512, SEEK_SET))
                return RES_ERROR;

            result = fread(buff, 512, count, driveHandle[pdrv]);

            if (result != count)
                return RES_ERROR;

            return RES_OK;
        }
    }

    return RES_PARERR;
}