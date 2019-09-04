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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int BUCKET_SIZE ; 
 int FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr_t ; 
 TYPE_1__ u ; 

__attribute__((used)) static inline size_t bstr_alloc_size(size_t size)
{
    return (FIELD_OFFSET(bstr_t, u.ptr[size]) + sizeof(WCHAR) + BUCKET_SIZE-1) & ~(BUCKET_SIZE-1);
}