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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_num_images(char *imgdirpath)
{
    DIR *dir;
    struct dirent* content;
    int num_images = 0;

    /*Reading the input images from given input directory*/

    dir = opendir(imgdirpath);
    if (!dir) {
        fprintf(stderr, "Could not open Folder %s\n", imgdirpath);
        return 0;
    }

    while ((content = readdir(dir)) != NULL) {
        if (strcmp(".", content->d_name) == 0 || strcmp("..", content->d_name) == 0) {
            continue;
        }
        num_images++;
    }
    closedir(dir);
    return num_images;
}