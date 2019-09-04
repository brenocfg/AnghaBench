#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fd; int /*<<< orphan*/ * target_copy; int /*<<< orphan*/ * alternate; int /*<<< orphan*/  shstrtab; } ;
struct TYPE_4__ {TYPE_1__ elf; } ;
struct image_file_map {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMAGE_NO_MAP ; 

__attribute__((used)) static inline void elf_reset_file_map(struct image_file_map* fmap)
{
    fmap->u.elf.fd = -1;
    fmap->u.elf.shstrtab = IMAGE_NO_MAP;
    fmap->u.elf.alternate = NULL;
    fmap->u.elf.target_copy = NULL;
}