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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 

__attribute__((used)) static int Seek( stream_t *p_access, uint64_t i_pos )
{
    (void) p_access; (void) i_pos;
    return VLC_EGENERIC;
}