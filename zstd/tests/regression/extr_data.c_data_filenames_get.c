#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* path; } ;
struct TYPE_7__ {TYPE_1__ data; } ;
typedef  TYPE_2__ data_t ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  filenames; } ;
typedef  TYPE_3__ data_filenames_t ;

/* Variables and functions */
 int /*<<< orphan*/  UTIL_createFileList (char const**,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

data_filenames_t data_filenames_get(data_t const* data) {
    data_filenames_t filenames = {.buffer = NULL, .size = 0};
    char const* path = data->data.path;

    filenames.filenames = UTIL_createFileList(
        &path,
        1,
        &filenames.buffer,
        &filenames.size,
        /* followLinks */ 0);
    return filenames;
}