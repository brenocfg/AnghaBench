#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  value; int /*<<< orphan*/  param; } ;
typedef  TYPE_3__ param_value_t ;
struct TYPE_9__ {size_t size; TYPE_3__* data; } ;
struct TYPE_11__ {scalar_t__ use_dictionary; TYPE_2__ param_values; } ;
typedef  TYPE_4__ config_t ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_12__ {TYPE_1__ dictionary; } ;
typedef  TYPE_5__ buffer_state_t ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_CCtx_loadDictionary (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_setParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_isError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_reset_session_and_parameters ; 

__attribute__((used)) static int advanced_config(
    ZSTD_CCtx* cctx,
    buffer_state_t* state,
    config_t const* config) {
    ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters);
    for (size_t p = 0; p < config->param_values.size; ++p) {
        param_value_t const pv = config->param_values.data[p];
        if (ZSTD_isError(ZSTD_CCtx_setParameter(cctx, pv.param, pv.value))) {
            return 1;
        }
    }
    if (config->use_dictionary) {
        if (ZSTD_isError(ZSTD_CCtx_loadDictionary(
                cctx, state->dictionary.data, state->dictionary.size))) {
            return 1;
        }
    }
    return 0;
}