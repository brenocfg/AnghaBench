#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct zip_entry {scalar_t__ extralen; scalar_t__ uncompressed; scalar_t__ datasize; scalar_t__ header_offset; int /*<<< orphan*/  disk; int /*<<< orphan*/  namelen; } ;
typedef  scalar_t__ off64_t ;
struct TYPE_4__ {int /*<<< orphan*/  stream; } ;
struct TYPE_5__ {TYPE_1__ super; } ;
typedef  TYPE_2__ ar_archive_zip ;

/* Variables and functions */
 int /*<<< orphan*/  UINT16_MAX ; 
 scalar_t__ UINT32_MAX ; 
 scalar_t__ ar_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ar_skip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int uint16le (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uint32le (int /*<<< orphan*/ *) ; 
 void* uint64le (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool zip_parse_extra_fields(ar_archive_zip *zip, struct zip_entry *entry)
{
    uint8_t *extra;
    uint32_t idx;

    if (!entry->extralen)
        return true;

    /* read ZIP64 values where needed */
    if (!ar_skip(zip->super.stream, entry->namelen))
        return false;
    extra = malloc(entry->extralen);
    if (!extra || ar_read(zip->super.stream, extra, entry->extralen) != entry->extralen) {
        free(extra);
        return false;
    }
    for (idx = 0; idx + 4 < entry->extralen; idx += 4 + uint16le(&extra[idx + 2])) {
        if (uint16le(&extra[idx]) == 0x0001) {
            uint16_t size = uint16le(&extra[idx + 2]);
            uint16_t offset = 0;
            if (entry->uncompressed == UINT32_MAX && offset + 8 <= size) {
                entry->uncompressed = uint64le(&extra[idx + 4 + offset]);
                offset += 8;
            }
            if (entry->datasize == UINT32_MAX && offset + 8 <= size) {
                entry->datasize = uint64le(&extra[idx + 4 + offset]);
                offset += 8;
            }
            if (entry->header_offset == UINT32_MAX && offset + 8 <= size) {
                entry->header_offset = (off64_t)uint64le(&extra[idx + 4 + offset]);
                offset += 8;
            }
            if (entry->disk == UINT16_MAX && offset + 4 <= size) {
                entry->disk = uint32le(&extra[idx + 4 + offset]);
                offset += 4;
            }
            break;
        }
    }
    free(extra);

    return true;
}