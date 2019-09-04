#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* lpReserved2; int cbReserved2; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BYTE ;

/* Variables and functions */

__attribute__((used)) static void create_io_inherit_block( STARTUPINFOA *startup, unsigned int count, const HANDLE *handles )
{
    static BYTE block[1024];
    BYTE *wxflag_ptr;
    HANDLE *handle_ptr;
    unsigned int i;

    startup->lpReserved2 = block;
    startup->cbReserved2 = sizeof(unsigned) + (sizeof(char) + sizeof(HANDLE)) * count;
    wxflag_ptr = block + sizeof(unsigned);
    handle_ptr = (HANDLE *)(wxflag_ptr + count);

    *(unsigned*)block = count;
    for (i = 0; i < count; i++)
    {
        wxflag_ptr[i] = 0x81;
        handle_ptr[i] = handles[i];
    }
}