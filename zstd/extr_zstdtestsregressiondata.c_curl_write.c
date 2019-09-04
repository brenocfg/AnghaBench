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
struct TYPE_2__ {int /*<<< orphan*/  xxhash64; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ curl_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  XXH64_update (int /*<<< orphan*/ *,void*,size_t const) ; 
 size_t fwrite (void*,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t curl_write(void* data, size_t size, size_t count, void* ptr) {
    curl_data_t* cdata = (curl_data_t*)ptr;
    size_t const written = fwrite(data, size, count, cdata->file);
    XXH64_update(&cdata->xxhash64, data, written * size);
    return written;
}