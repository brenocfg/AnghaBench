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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ capacity; scalar_t__ size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ data_buffer_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ const UTIL_FILESIZE_UNKNOWN ; 
 scalar_t__ UTIL_getFileSize (char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fread (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (scalar_t__ const) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

data_buffer_t data_buffer_read(char const* filename) {
    data_buffer_t buffer = {};

    uint64_t const size = UTIL_getFileSize(filename);
    if (size == UTIL_FILESIZE_UNKNOWN) {
        fprintf(stderr, "unknown size for %s\n", filename);
        return buffer;
    }

    buffer.data = (uint8_t*)malloc(size);
    if (buffer.data == NULL) {
        fprintf(stderr, "malloc failed\n");
        return buffer;
    }
    buffer.capacity = size;

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "file null\n");
        goto err;
    }
    buffer.size = fread(buffer.data, 1, buffer.capacity, file);
    fclose(file);
    if (buffer.size != buffer.capacity) {
        fprintf(stderr, "read %zu != %zu\n", buffer.size, buffer.capacity);
        goto err;
    }

    return buffer;
err:
    free(buffer.data);
    memset(&buffer, 0, sizeof(buffer));
    return buffer;
}