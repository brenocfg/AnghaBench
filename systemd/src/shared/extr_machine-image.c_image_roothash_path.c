#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  path; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Image ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 char* file_in_same_dir (int /*<<< orphan*/ ,char const*) ; 
 char* strjoina (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *image_roothash_path(Image *image) {
        const char *fn;

        assert(image);

        fn = strjoina(image->name, ".roothash");

        return file_in_same_dir(image->path, fn);
}