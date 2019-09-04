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
typedef  int /*<<< orphan*/  HFILE ;
typedef  int DWORD ;

/* Variables and functions */
#define  IMAGE_NT_SIGNATURE 129 
#define  IMAGE_OS2_SIGNATURE 128 
 int /*<<< orphan*/  find_ne_resource (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  find_pe_resource (int /*<<< orphan*/ ,int*,int*,int) ; 
 int read_xx_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD find_version_resource( HFILE lzfd, DWORD *reslen, DWORD *offset, DWORD flags )
{
    DWORD magic = read_xx_header( lzfd );

    switch (magic)
    {
    case IMAGE_OS2_SIGNATURE:
        if (!find_ne_resource( lzfd, reslen, offset )) magic = 0;
        break;
    case IMAGE_NT_SIGNATURE:
        if (!find_pe_resource( lzfd, reslen, offset, flags )) magic = 0;
        break;
    }
    return magic;
}