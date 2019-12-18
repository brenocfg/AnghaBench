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
struct TYPE_4__ {int /*<<< orphan*/  srcBuffer; int /*<<< orphan*/ * srcPtrs; } ;
typedef  TYPE_1__ buffers_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeNonSrcBuffers (TYPE_1__ const) ; 

__attribute__((used)) static void freeBuffers(const buffers_t b) {
    if(b.srcPtrs != NULL) {
        free(b.srcBuffer);
    }
    freeNonSrcBuffers(b);
}