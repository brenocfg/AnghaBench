#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * inflate; } ;
struct ar_archive_zip_uncomp {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/ * inflate_create (int) ; 

__attribute__((used)) static bool zip_init_uncompress_deflate64(struct ar_archive_zip_uncomp *uncomp, bool deflate64)
{
    uncomp->state.inflate = inflate_create(deflate64);

    return uncomp->state.inflate != NULL;
}