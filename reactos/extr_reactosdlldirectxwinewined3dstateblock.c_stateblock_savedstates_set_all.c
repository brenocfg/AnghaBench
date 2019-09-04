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
struct wined3d_saved_states {int indices; int material; int viewport; int vertexDecl; int pixelShader; int vertexShader; int scissorRect; int streamSource; int streamFreq; int textures; int* textureState; int* samplerState; unsigned int clipplane; int pixelShaderConstantsB; int pixelShaderConstantsI; int vertexShaderConstantsB; int vertexShaderConstantsI; int /*<<< orphan*/  vs_consts_f; int /*<<< orphan*/  ps_consts_f; int /*<<< orphan*/  renderState; int /*<<< orphan*/  transform; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ HIGHEST_TRANSFORMSTATE ; 
 unsigned int MAX_CLIP_DISTANCES ; 
 unsigned int MAX_COMBINED_SAMPLERS ; 
 unsigned int MAX_TEXTURES ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WINEHIGHEST_RENDER_STATE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stateblock_set_bits (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stateblock_savedstates_set_all(struct wined3d_saved_states *states, DWORD vs_consts, DWORD ps_consts)
{
    unsigned int i;

    /* Single values */
    states->indices = 1;
    states->material = 1;
    states->viewport = 1;
    states->vertexDecl = 1;
    states->pixelShader = 1;
    states->vertexShader = 1;
    states->scissorRect = 1;

    /* Fixed size arrays */
    states->streamSource = 0xffff;
    states->streamFreq = 0xffff;
    states->textures = 0xfffff;
    stateblock_set_bits(states->transform, HIGHEST_TRANSFORMSTATE + 1);
    stateblock_set_bits(states->renderState, WINEHIGHEST_RENDER_STATE + 1);
    for (i = 0; i < MAX_TEXTURES; ++i) states->textureState[i] = 0x3ffff;
    for (i = 0; i < MAX_COMBINED_SAMPLERS; ++i) states->samplerState[i] = 0x3ffe;
    states->clipplane = (1u << MAX_CLIP_DISTANCES) - 1;
    states->pixelShaderConstantsB = 0xffff;
    states->pixelShaderConstantsI = 0xffff;
    states->vertexShaderConstantsB = 0xffff;
    states->vertexShaderConstantsI = 0xffff;

    /* Dynamically sized arrays */
    memset(states->ps_consts_f, TRUE, sizeof(BOOL) * ps_consts);
    memset(states->vs_consts_f, TRUE, sizeof(BOOL) * vs_consts);
}