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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  write_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_little_endian_dword(DWORD x)
{
    write_byte((BYTE)x);
    write_byte((BYTE)(x >> 8));
    write_byte((BYTE)(x >> 16));
    write_byte((BYTE)(x >> 24));
}