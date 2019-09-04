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
struct stat {scalar_t__ st_size; } ;
struct TYPE_2__ {int loading; scalar_t__ loading_total_bytes; scalar_t__ loading_loaded_bytes; int /*<<< orphan*/  loading_start_time; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void startLoading(FILE *fp) {
    struct stat sb;

    /* Load the DB */
    server.loading = 1;
    server.loading_start_time = time(NULL);
    server.loading_loaded_bytes = 0;
    if (fstat(fileno(fp), &sb) == -1) {
        server.loading_total_bytes = 0;
    } else {
        server.loading_total_bytes = sb.st_size;
    }
}