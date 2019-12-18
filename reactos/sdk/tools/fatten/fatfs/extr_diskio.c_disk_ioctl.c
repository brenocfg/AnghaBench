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
typedef  int /*<<< orphan*/  DRESULT ;
typedef  size_t BYTE ;

/* Variables and functions */
#define  CTRL_SYNC 132 
#define  GET_BLOCK_SIZE 131 
#define  GET_SECTOR_COUNT 130 
#define  GET_SECTOR_SIZE 129 
 int /*<<< orphan*/  RES_ERROR ; 
 int /*<<< orphan*/  RES_OK ; 
 int /*<<< orphan*/  RES_PARERR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
#define  SET_SECTOR_COUNT 128 
 int /*<<< orphan*/ ** driveHandle ; 
 size_t driveHandleCount ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (void*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int* sectorCount ; 

DRESULT disk_ioctl(
    BYTE pdrv,		/* Physical drive nmuber (0..) */
    BYTE cmd,		/* Control code */
    void *buff		/* Buffer to send/receive control data */
    )
{
    if (pdrv < driveHandleCount)
    {
        if (driveHandle[pdrv] != NULL)
        {
            switch (cmd)
            {
            case CTRL_SYNC:
                fflush(driveHandle[pdrv]);
                return RES_OK;
            case GET_SECTOR_SIZE:
                *(DWORD*)buff = 512;
                return RES_OK;
            case GET_BLOCK_SIZE:
                *(DWORD*)buff = 512;
                return RES_OK;
            case GET_SECTOR_COUNT:
            {
                if (sectorCount[pdrv] <= 0)
                {
                    if (fseek(driveHandle[pdrv], 0, SEEK_END))
                        printf("fseek failed!\n");
                    else
                        sectorCount[pdrv] = ftell(driveHandle[pdrv]) / 512;
                }

                *(DWORD*)buff = sectorCount[pdrv];
                return RES_OK;
            }
            case SET_SECTOR_COUNT:
            {
                int count = *(DWORD*)buff;
                long size;

                sectorCount[pdrv] = count;

                fseek(driveHandle[pdrv], 0, SEEK_END);
                size = ftell(driveHandle[pdrv]) / 512;

                if (size < count)
                {
                    if (fseek(driveHandle[pdrv], count * 512 - 1, SEEK_SET))
                        return RES_ERROR;

                    fwrite(buff, 1, 1, driveHandle[pdrv]);

                    return RES_OK;
                }
                else
                {
                    // SHRINKING NOT IMPLEMENTED
                    return RES_OK;
                }
            }
            }
        }
    }

    return RES_PARERR;
}