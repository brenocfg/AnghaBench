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
typedef  char WCHAR ;
typedef  int UINT ;
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  sprintfW (char*,char const*,int,int,int,int) ; 

__attribute__((used)) static DWORD ui2ipv4(WCHAR *dest, UINT address) {
    static const WCHAR formatW[] =
        {'%','u','.','%','u','.','%','u','.','%','u',0};
    DWORD ret = 0;
    UCHAR digits[4];

    digits[0] = (address >> 24) & 0xff;
    digits[1] = (address >> 16) & 0xff;
    digits[2] = (address >> 8) & 0xff;
    digits[3] = address & 0xff;

    if(!dest) {
        WCHAR tmp[16];
        ret = sprintfW(tmp, formatW, digits[0], digits[1], digits[2], digits[3]);
    } else
        ret = sprintfW(dest, formatW, digits[0], digits[1], digits[2], digits[3]);

    return ret;
}