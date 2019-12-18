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

/* Variables and functions */
 int /*<<< orphan*/  _T (char*) ; 
 int _tunlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_unlink_files(void)
{
    int result = 0;

    //printf("sizeof dos_data: %d\n", sizeof(dos_data));
    //printf("sizeof nix_data: %d\n", sizeof(nix_data));

    result |= _tunlink(_T("binary.dos"));
    result |= _tunlink(_T("binary.nix"));
    result |= _tunlink(_T("text.dos"));
    result |= _tunlink(_T("text.nix"));
    return result;
}