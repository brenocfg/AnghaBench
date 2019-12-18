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
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetAccess (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_stream_ReadBlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static block_t *Block(stream_t *access, bool *restrict eof)
{
    stream_t *a = GetAccess(access);
    if (a == NULL)
    {
        *eof = true;
        return NULL;
    }

    return vlc_stream_ReadBlock(a);
}