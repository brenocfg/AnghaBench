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
struct TYPE_3__ {int /*<<< orphan*/  (* DetachCurrentThread ) (TYPE_1__**) ;} ;

/* Variables and functions */
 TYPE_1__** s_jvm ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**) ; 

__attribute__((used)) static void release_env(bool b_detach)
{
    if (b_detach)
        (*s_jvm)->DetachCurrentThread(s_jvm);
}