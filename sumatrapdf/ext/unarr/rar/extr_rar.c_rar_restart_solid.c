#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off64_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_8__ {int restart; } ;
struct TYPE_9__ {TYPE_1__ solid; } ;
typedef  TYPE_2__ ar_archive_rar ;
struct TYPE_10__ {scalar_t__ entry_offset; scalar_t__ entry_offset_first; size_t entry_size_uncompressed; } ;
typedef  TYPE_3__ ar_archive ;

/* Variables and functions */
 int /*<<< orphan*/  ar_entry_uncompress (TYPE_3__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ar_parse_entry (TYPE_3__*) ; 
 int /*<<< orphan*/  ar_parse_entry_at (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  log (char*) ; 
 size_t smin (size_t,int) ; 

__attribute__((used)) static bool rar_restart_solid(ar_archive *ar)
{
    ar_archive_rar *rar = (ar_archive_rar *)ar;
    off64_t current_offset = ar->entry_offset;
    log("Restarting decompression for solid entry");
    if (!ar_parse_entry_at(ar, ar->entry_offset_first)) {
        ar_parse_entry_at(ar, current_offset);
        return false;
    }
    while (ar->entry_offset < current_offset) {
        size_t size = ar->entry_size_uncompressed;
        rar->solid.restart = false;
        while (size > 0) {
            unsigned char buffer[1024];
            size_t count = smin(size, sizeof(buffer));
            if (!ar_entry_uncompress(ar, buffer, count)) {
                ar_parse_entry_at(ar, current_offset);
                return false;
            }
            size -= count;
        }
        if (!ar_parse_entry(ar)) {
            ar_parse_entry_at(ar, current_offset);
            return false;
        }
    }
    rar->solid.restart = false;
    return true;
}