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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ contents; int /*<<< orphan*/  encoding; } ;
typedef  TYPE_1__ intset ;
typedef  void* int64_t ;
typedef  void* int32_t ;
typedef  void* int16_t ;

/* Variables and functions */
 scalar_t__ INTSET_ENC_INT32 ; 
 scalar_t__ INTSET_ENC_INT64 ; 
 scalar_t__ intrev32ifbe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memrev16ifbe (void**) ; 
 int /*<<< orphan*/  memrev32ifbe (void**) ; 
 int /*<<< orphan*/  memrev64ifbe (void**) ; 

__attribute__((used)) static void _intsetSet(intset *is, int pos, int64_t value) {
    uint32_t encoding = intrev32ifbe(is->encoding);

    if (encoding == INTSET_ENC_INT64) {
        ((int64_t*)is->contents)[pos] = value;
        memrev64ifbe(((int64_t*)is->contents)+pos);
    } else if (encoding == INTSET_ENC_INT32) {
        ((int32_t*)is->contents)[pos] = value;
        memrev32ifbe(((int32_t*)is->contents)+pos);
    } else {
        ((int16_t*)is->contents)[pos] = value;
        memrev16ifbe(((int16_t*)is->contents)+pos);
    }
}