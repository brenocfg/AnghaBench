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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct pl_plane_data {int dummy; } ;
struct pl_gpu {int dummy; } ;
struct fmt_desc {int num_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  FillDesc (int /*<<< orphan*/ ,struct fmt_desc const*,struct pl_plane_data*) ; 
 struct fmt_desc* FindDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl_plane_find_fmt (struct pl_gpu const*,int /*<<< orphan*/ *,struct pl_plane_data*) ; 

bool vlc_placebo_FormatSupported(const struct pl_gpu *gpu, vlc_fourcc_t fcc)
{
    const struct fmt_desc *desc = FindDesc(fcc);
    if (!desc)
        return false;

    struct pl_plane_data data[4];
    FillDesc(fcc, desc, data);
    for (int i = 0; i < desc->num_planes; i++) {
        if (!pl_plane_find_fmt(gpu, NULL, &data[i]))
            return false;
    }

    return true;
}