#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t data_left; size_t bytes_done; } ;
struct TYPE_5__ {int /*<<< orphan*/  stream; } ;
struct TYPE_7__ {TYPE_2__ progress; TYPE_1__ super; } ;
typedef  TYPE_3__ ar_archive_rar ;

/* Variables and functions */
 size_t ar_read (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static bool rar_copy_stored(ar_archive_rar *rar, void *buffer, size_t count)
{
    if (count > rar->progress.data_left) {
        warn("Unexpected EOS in stored data");
        return false;
    }
    if (ar_read(rar->super.stream, buffer, count) != count) {
        warn("Unexpected EOF in stored data");
        return false;
    }
    rar->progress.data_left -= count;
    rar->progress.bytes_done += count;
    return true;
}