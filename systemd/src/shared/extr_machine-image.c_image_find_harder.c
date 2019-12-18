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
typedef  int /*<<< orphan*/  ImageClass ;
typedef  int /*<<< orphan*/  Image ;

/* Variables and functions */
 int image_find (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 int image_from_path (char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ image_name_is_valid (char const*) ; 

int image_find_harder(ImageClass class, const char *name_or_path, Image **ret) {
        if (image_name_is_valid(name_or_path))
                return image_find(class, name_or_path, ret);

        return image_from_path(name_or_path, ret);
}