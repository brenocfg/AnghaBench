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
typedef  size_t UINT ;
typedef  size_t BYTE ;

/* Variables and functions */

__attribute__((used)) static UINT read_table_int( BYTE *const *data, UINT row, UINT col, UINT bytes )
{
    UINT ret = 0, i;

    for (i = 0; i < bytes; i++)
        ret += data[row][col + i] << i * 8;

    return ret;
}