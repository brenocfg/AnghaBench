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
struct TYPE_3__ {int /*<<< orphan*/  const* data; } ;
typedef  TYPE_1__ method_state_t ;
typedef  int /*<<< orphan*/  data_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

__attribute__((used)) static method_state_t* method_state_create(data_t const* data) {
    method_state_t* state = (method_state_t*)malloc(sizeof(method_state_t));
    if (state == NULL)
        return NULL;
    state->data = data;
    return state;
}