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
typedef  int /*<<< orphan*/  HashmapBase ;

/* Variables and functions */
 unsigned int DIB_FREE ; 
 int /*<<< orphan*/  DIB_RAW_FREE ; 
 int /*<<< orphan*/  DIB_RAW_OVERFLOW ; 
 int /*<<< orphan*/  MIN (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dib_raw_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bucket_set_dib(HashmapBase *h, unsigned idx, unsigned dib) {
        dib_raw_ptr(h)[idx] = dib != DIB_FREE ? MIN(dib, DIB_RAW_OVERFLOW) : DIB_RAW_FREE;
}