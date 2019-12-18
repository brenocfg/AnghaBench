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
typedef  int /*<<< orphan*/  OPJ_UINT8 ;
typedef  int OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_ARG_NOT_USED (int) ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static OPJ_BOOL bmp_read_raw_data(FILE* IN, OPJ_UINT8* pData, OPJ_UINT32 stride,
                                  OPJ_UINT32 width, OPJ_UINT32 height)
{
    OPJ_ARG_NOT_USED(width);

    if (fread(pData, sizeof(OPJ_UINT8), stride * height, IN) != (stride * height)) {
        fprintf(stderr,
                "\nError: fread return a number of element different from the expected.\n");
        return OPJ_FALSE;
    }
    return OPJ_TRUE;
}