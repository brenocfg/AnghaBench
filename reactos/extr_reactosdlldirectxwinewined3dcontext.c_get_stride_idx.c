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
typedef  unsigned int WORD ;
typedef  unsigned int DWORD ;

/* Variables and functions */

__attribute__((used)) static unsigned int get_stride_idx(const void *idx_data, unsigned int idx_size,
        unsigned int base_vertex_idx, unsigned int start_idx, unsigned int vertex_idx)
{
    if (!idx_data)
        return start_idx + vertex_idx;
    if (idx_size == 2)
        return ((const WORD *)idx_data)[start_idx + vertex_idx] + base_vertex_idx;
    return ((const DWORD *)idx_data)[start_idx + vertex_idx] + base_vertex_idx;
}