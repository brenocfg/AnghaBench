#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ dwMagic; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/ * cvinfo; } ;
struct TYPE_11__ {int /*<<< orphan*/  lpOutput; TYPE_2__* lpbiInput; int /*<<< orphan*/  lpInput; TYPE_1__* lpbiOutput; } ;
struct TYPE_10__ {int /*<<< orphan*/  biSizeImage; int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biWidth; } ;
struct TYPE_9__ {int /*<<< orphan*/  biHeight; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LONG ;
typedef  TYPE_3__ ICDECOMPRESS ;
typedef  TYPE_4__ ICCVID_Info ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ ICCVID_MAGIC ; 
 int /*<<< orphan*/  ICERR_BADPARAM ; 
 int /*<<< orphan*/  ICERR_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_cinepak (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LRESULT ICCVID_Decompress( ICCVID_Info *info, ICDECOMPRESS *icd, DWORD size )
{
    LONG width, height;
    BOOL inverted;

    TRACE("ICM_DECOMPRESS %p %p %d\n", info, icd, size);

    if( (info==NULL) || (info->dwMagic!=ICCVID_MAGIC) )
        return ICERR_BADPARAM;
    if (info->cvinfo==NULL)
    {
        ERR("ICM_DECOMPRESS sent after ICM_DECOMPRESS_END\n");
        return ICERR_BADPARAM;
    }

    width  = icd->lpbiInput->biWidth;
    height = icd->lpbiInput->biHeight;
    inverted = -icd->lpbiOutput->biHeight == height;

    decode_cinepak(info->cvinfo, icd->lpInput, icd->lpbiInput->biSizeImage,
                   icd->lpOutput, width, height, info->bits_per_pixel, inverted);

    return ICERR_OK;
}