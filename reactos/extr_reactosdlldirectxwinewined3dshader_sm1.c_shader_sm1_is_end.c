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
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ const WINED3D_SM1_END ; 
 int /*<<< orphan*/  shader_sm1_read_comment (scalar_t__ const**) ; 

__attribute__((used)) static BOOL shader_sm1_is_end(void *data, const DWORD **ptr)
{
    shader_sm1_read_comment(ptr);

    if (**ptr == WINED3D_SM1_END)
    {
        ++(*ptr);
        return TRUE;
    }

    return FALSE;
}