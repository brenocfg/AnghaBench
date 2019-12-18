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
struct TYPE_4__ {void* ptr; size_t capacity; scalar_t__ size; } ;
typedef  TYPE_1__ buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ kBuffNull ; 
 void* malloc (size_t) ; 

__attribute__((used)) static buffer_t createBuffer(size_t capacity)
{
    assert(capacity > 0);
    void* const ptr = malloc(capacity);
    if (ptr==NULL) return kBuffNull;

    buffer_t buffer;
    buffer.ptr = ptr;
    buffer.capacity = capacity;
    buffer.size = 0;
    return buffer;
}