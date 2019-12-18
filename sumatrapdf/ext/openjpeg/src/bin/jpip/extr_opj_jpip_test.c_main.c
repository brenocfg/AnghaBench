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
typedef  int /*<<< orphan*/  index_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  destroy_index (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * get_index_from_JP2file (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char *argv[])
{
    int fd;
    index_t *jp2idx;
    if (argc < 2) {
        return 1;
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        fprintf(stderr, "Error: Target %s not found\n", argv[1]);
        return -1;
    }

    if (!(jp2idx = get_index_from_JP2file(fd))) {
        fprintf(stderr, "JP2 file broken\n");
        return -1;
    }

    output_index(jp2idx);
    destroy_index(&jp2idx);
    close(fd);

    return 0;
}