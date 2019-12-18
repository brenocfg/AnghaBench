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
typedef  int /*<<< orphan*/  ID3DBlob ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  D3DCOMPILE_SKIP_VALIDATION ; 
 int D3DXERR_INVALIDDATA ; 
 int /*<<< orphan*/ * ID3D10Blob_GetBufferPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D10Blob_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_shader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int,int,int) ; 
 int pD3DAssemble (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void failure_test(void) {
    const char * tests[] = {
        /* shader 0: instruction modifier not allowed */
        "ps_3_0\n"
        "dcl_2d s2\n"
        "texldd_x2 r0, v1, s2, v3, v4\n",
        /* shader 1: coissue not supported in vertex shaders */
        "vs.1.1\r\n"
        "add r0.rgb, r0, r1\n"
        "+add r0.a, r0, r2\n",
        /* shader 2: coissue not supported in pixel shader version >= 2.0 */
        "ps_2_0\n"
        "texld r0, t0, s0\n"
        "add r0.rgb, r0, r1\n"
        "+add r0.a, r0, v1\n",
        /* shader 3: predicates not supported in vertex shader < 2.0 */
        "vs_1_1\n"
        "(p0) add r0, r0, v0\n",
        /* shader 4: register a0 doesn't exist in pixel shaders */
        "ps_3_0\n"
        "mov r0, v[ a0 + 12 ]\n",
        /* shader 5: s0 doesn't exist in vs_1_1 */
        "vs_1_1\n"
        "mov r0, s0\n",
        /* shader 6: aL is a scalar register, no swizzles allowed */
        "ps_3_0\n"
        "mov r0, v[ aL.x + 12 ]\n",
        /* shader 7: tn doesn't exist in ps_3_0 */
        "ps_3_0\n"
        "dcl_2d s2\n"
        "texldd r0, t1, s2, v3, v4\n",
        /* shader 8: two shift modifiers */
        "ps_1_3\n"
        "mov_x2_x2 r0, r1\n",
        /* shader 9: too many source registers for mov instruction */
        "vs_1_1\n"
        "mov r0, r1, r2\n",
        /* shader 10: invalid combination of negate and divide modifiers */
        "ps_1_4\n"
        "texld r5, -r2_dz\n",
        /* shader 11: complement modifier not allowed in >= PS 2 */
        "ps_2_0\n"
        "mov r2, 1 - r0\n",
        /* shader 12: invalid modifier */
        "vs_3_0\n"
        "mov r2, 2 - r0\n",
        /* shader 13: float value in relative addressing */
        "vs_3_0\n"
        "mov r2, c[ aL + 3.4 ]\n",
        /* shader 14: complement modifier not available in VS */
        "vs_3_0\n"
        "mov r2, 1 - r1\n",
        /* shader 15: _x2 modifier not available in VS */
        "vs_1_1\n"
        "mov r2, r1_x2\n",
        /* shader 16: _abs modifier not available in < VS 3.0 */
        "vs_1_1\n"
        "mov r2, r1_abs\n",
        /* shader 17: _x2 modifier not available in >= PS 2.0 */
        "ps_2_0\n"
        "mov r0, r1_x2\n",
        /* shader 18: wrong swizzle */
        "vs_2_0\n"
        "mov r0, r1.abcd\n",
        /* shader 19: wrong swizzle */
        "vs_2_0\n"
        "mov r0, r1.xyzwx\n",
        /* shader 20: wrong swizzle */
        "vs_2_0\n"
        "mov r0, r1.\n",
        /* shader 21: invalid writemask */
        "vs_2_0\n"
        "mov r0.xxyz, r1\n",
        /* shader 22: register r5 doesn't exist in PS < 1.4 */
        "ps_1_3\n"
        "mov r5, r0\n",
        /* shader 23: can't declare output registers in a pixel shader */
        "ps_3_0\n"
        "dcl_positiont o0\n",
        /* shader 24: _pp instruction modifier not allowed in vertex shaders */
        "vs_3_0\n"
        "add_pp r0, r0, r1\n",
        /* shader 25: _x4 instruction modified not allowed in > ps_1_x */
        "ps_3_0\n"
        "add_x4 r0, r0, r1\n",
        /* shader 26: there aren't oCx registers in ps_1_x */
        "ps_1_3\n"
        "add oC0, r0, r1\n",
        /* shader 27: oC3 is the max in >= ps_2_0 */
        "ps_3_0\n"
        "add oC4, r0, r1\n",
        /* shader 28: register v17 doesn't exist */
        "vs_3_0\n"
        "add r0, r0, v17\n",
        /* shader 29: register o13 doesn't exist */
        "vs_3_0\n"
        "add o13, r0, r1\n",
        /* shader 30: label > 2047 not allowed */
        "vs_3_0\n"
        "call l2048\n",
        /* shader 31: s20 register does not exist */
        "ps_3_0\n"
        "texld r0, r1, s20\n",
        /* shader 32: t5 not allowed in ps_1_3 */
        "ps_1_3\n"
        "tex t5\n",
        /* shader 33: no temporary registers relative addressing */
        "vs_3_0\n"
        "add r0, r0[ a0.x ], r1\n",
        /* shader 34: no input registers relative addressing in vs_2_0 */
        "vs_2_0\n"
        "add r0, v[ a0.x ], r1\n",
        /* shader 35: no aL register in ps_2_0 */
        "ps_2_0\n"
        "add r0, v[ aL ], r1\n",
        /* shader 36: no relative addressing in ps_2_0 */
        "ps_2_0\n"
        "add r0, v[ r0 ], r1\n",
        /* shader 37: no a0 register in ps_3_0 */
        "ps_3_0\n"
        "add r0, v[ a0.x ], r1\n",
        /* shader 38: only a0.x accepted in vs_1_1 */
        "vs_1_1\n"
        "mov r0, c0[ a0 ]\n",
        /* shader 39: invalid modifier for dcl instruction */
        "ps_3_0\n"
        "dcl_texcoord0_sat v0\n",
        /* shader 40: shift not allowed */
        "ps_3_0\n"
        "dcl_texcoord0_x2 v0\n",
        /* shader 41: no modifier allowed with dcl instruction in vs */
        "vs_3_0\n"
        "dcl_texcoord0_centroid v0\n",
        /* shader 42: no modifiers with vs dcl sampler instruction */
        "vs_3_0\n"
        "dcl_2d_pp s0\n",
        /* shader 43: */
        "ps_2_0\n"
        "texm3x3vspec t3, t0\n",
    };
    HRESULT hr;
    unsigned int i;
    ID3DBlob *shader, *messages;

    for(i = 0; i < ARRAY_SIZE(tests); i++)
    {
        shader = NULL;
        messages = NULL;
        hr = pD3DAssemble(tests[i], strlen(tests[i]), NULL,
                          NULL, NULL, D3DCOMPILE_SKIP_VALIDATION,
                          &shader, &messages);
        ok(hr == D3DXERR_INVALIDDATA, "Failure test, shader %d: "
           "expected D3DAssemble failure with D3DXERR_INVALIDDATA, "
           "got 0x%x - %d\n", i, hr, hr & 0x0000FFFF);
        if(messages) {
            trace("D3DAssemble messages:\n%s", (char *)ID3D10Blob_GetBufferPointer(messages));
            ID3D10Blob_Release(messages);
        }
        if(shader) {
            DWORD *res = ID3D10Blob_GetBufferPointer(shader);
            dump_shader(res);
            ID3D10Blob_Release(shader);
        }
    }
}