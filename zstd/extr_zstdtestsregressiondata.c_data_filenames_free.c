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
struct TYPE_3__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  filenames; } ;
typedef  TYPE_1__ data_filenames_t ;

/* Variables and functions */
 int /*<<< orphan*/  UTIL_freeFileList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void data_filenames_free(data_filenames_t filenames) {
    UTIL_freeFileList(filenames.filenames, filenames.buffer);
}