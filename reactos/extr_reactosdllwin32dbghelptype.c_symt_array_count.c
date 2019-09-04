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
struct symt_array {int end; int start; int /*<<< orphan*/  base_type; } ;
struct module {int dummy; } ;
typedef  scalar_t__ DWORD64 ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TI_GET_LENGTH ; 
 scalar_t__ symt_get_info (struct module*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static inline DWORD symt_array_count(struct module* module, const struct symt_array* array)
{
    if (array->end < 0)
    {
        DWORD64 elem_size;
        /* One could want to also set the array->end field in array, but we won't do it
         * as long as all the get_type() helpers use const objects
         */
        if (symt_get_info(module, array->base_type, TI_GET_LENGTH, &elem_size) && elem_size)
            return -array->end / (DWORD)elem_size;
        return 0;
    }
    return array->end - array->start + 1;
}