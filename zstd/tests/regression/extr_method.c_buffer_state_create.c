#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  const* data; } ;
typedef  TYPE_1__ method_state_t ;
typedef  int /*<<< orphan*/  data_t ;
struct TYPE_5__ {TYPE_1__ base; void* decompressed; void* compressed; int /*<<< orphan*/  inputs; int /*<<< orphan*/  dictionary; } ;
typedef  TYPE_2__ buffer_state_t ;

/* Variables and functions */
 size_t const ZSTD_compressBound (size_t const) ; 
 size_t buffers_max_size (int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 void* data_buffer_create (size_t const) ; 
 int /*<<< orphan*/  data_buffer_get_dict (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  data_buffers_get (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static method_state_t* buffer_state_create(data_t const* data) {
    buffer_state_t* state = (buffer_state_t*)calloc(1, sizeof(buffer_state_t));
    if (state == NULL)
        return NULL;
    state->base.data = data;
    state->inputs = data_buffers_get(data);
    state->dictionary = data_buffer_get_dict(data);
    size_t const max_size = buffers_max_size(state->inputs);
    state->compressed = data_buffer_create(ZSTD_compressBound(max_size));
    state->decompressed = data_buffer_create(max_size);
    return &state->base;
}