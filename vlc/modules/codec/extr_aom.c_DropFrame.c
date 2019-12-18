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
struct aom_image {int dummy; } ;
typedef  struct aom_image const decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (struct aom_image const*) ; 

__attribute__((used)) static void DropFrame(decoder_t *dec, const struct aom_image *img)
{
    VLC_UNUSED(dec);
    VLC_UNUSED(img);
    /* do nothing for now */
}