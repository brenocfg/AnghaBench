#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ use_dictionary; } ;
typedef  TYPE_5__ config_t ;
struct TYPE_9__ {int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {scalar_t__ size; } ;
struct TYPE_14__ {TYPE_1__ dictionary; TYPE_4__ decompressed; TYPE_3__ compressed; TYPE_2__ inputs; } ;
typedef  TYPE_6__ buffer_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int buffer_state_bad(
    buffer_state_t const* state,
    config_t const* config) {
    if (state == NULL) {
        fprintf(stderr, "buffer_state_t is NULL\n");
        return 1;
    }
    if (state->inputs.size == 0 || state->compressed.data == NULL ||
        state->decompressed.data == NULL) {
        fprintf(stderr, "buffer state allocation failure\n");
        return 1;
    }
    if (config->use_dictionary && state->dictionary.data == NULL) {
        fprintf(stderr, "dictionary loading failed\n");
        return 1;
    }
    return 0;
}