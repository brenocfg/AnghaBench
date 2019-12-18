#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dirent {int /*<<< orphan*/  d_name; } ;
struct TYPE_3__ {int /*<<< orphan*/ * filename; } ;
typedef  TYPE_1__ dircnt_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int load_images(dircnt_t *dirptr, char *imgdirpath)
{
    DIR *dir;
    struct dirent* content;
    int i = 0;

    /*Reading the input images from given input directory*/

    dir = opendir(imgdirpath);
    if (!dir) {
        fprintf(stderr, "Could not open Folder %s\n", imgdirpath);
        return 1;
    } else   {
        fprintf(stderr, "Folder opened successfully\n");
    }

    while ((content = readdir(dir)) != NULL) {
        if (strcmp(".", content->d_name) == 0 || strcmp("..", content->d_name) == 0) {
            continue;
        }

        strcpy(dirptr->filename[i], content->d_name);
        i++;
    }
    return 0;
}