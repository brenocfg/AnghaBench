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
struct TYPE_3__ {scalar_t__ context_mutex; } ;
typedef  TYPE_1__ d3d11_device_t ;

/* Variables and functions */
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  ReleaseMutex (scalar_t__) ; 

__attribute__((used)) static inline void d3d11_device_unlock(d3d11_device_t *d3d_dev)
{
    if( d3d_dev->context_mutex  != INVALID_HANDLE_VALUE )
        ReleaseMutex( d3d_dev->context_mutex );
}