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
struct TYPE_4__ {size_t count; void** descs; void** values; } ;
typedef  TYPE_1__ enum_context_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t BUILTIN_SHADERS_COUNT ; 
 int /*<<< orphan*/  SELECTED_SHADER_FILE ; 
 TYPE_2__* builtin_shaders ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 void* xrealloc (void**,size_t) ; 

__attribute__((used)) static void ListShaders(enum_context_t *ctx)
{
    size_t num_shaders = BUILTIN_SHADERS_COUNT;
    ctx->values = xrealloc(ctx->values, (ctx->count + num_shaders + 1) * sizeof(char *));
    ctx->descs = xrealloc(ctx->descs, (ctx->count + num_shaders + 1) * sizeof(char *));
    for (size_t i = 0; i < num_shaders; ++i) {
        ctx->values[ctx->count] = strdup(builtin_shaders[i].name);
        ctx->descs[ctx->count] = strdup(builtin_shaders[i].name);
        ctx->count++;
    }
    ctx->values[ctx->count] = strdup(SELECTED_SHADER_FILE);
    ctx->descs[ctx->count] = strdup(SELECTED_SHADER_FILE);
    ctx->count++;
}