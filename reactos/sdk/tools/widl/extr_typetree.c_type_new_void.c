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
typedef  int /*<<< orphan*/  type_t ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_VOID ; 
 int /*<<< orphan*/ * make_type (int /*<<< orphan*/ ) ; 

type_t *type_new_void(void)
{
    static type_t *void_type = NULL;
    if (!void_type)
        void_type = make_type(TYPE_VOID);
    return void_type;
}