#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  regset2table; } ;
struct TYPE_9__ {int /*<<< orphan*/  table_sizes; } ;
struct TYPE_10__ {TYPE_2__ regs; } ;
struct d3dx_param_eval {int param_type; TYPE_1__ shader_inputs; TYPE_3__ pres; int /*<<< orphan*/ * version_counter; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  int /*<<< orphan*/  ULONG64 ;
typedef  struct d3dx_param_eval* HRESULT ;
typedef  int D3DXPARAMETER_TYPE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 struct d3dx_param_eval* D3DXERR_INVALIDDATA ; 
#define  D3DXPT_PIXELSHADER 129 
#define  D3DXPT_VERTEXSHADER 128 
 struct d3dx_param_eval* D3D_OK ; 
 struct d3dx_param_eval* E_OUTOFMEMORY ; 
 scalar_t__ FAILED (struct d3dx_param_eval*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  FOURCC_PRES ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 struct d3dx_param_eval* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int PRES_REGTAB_COUNT ; 
 unsigned int PRES_REGTAB_FIRST_SHADER ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  d3dx ; 
 int /*<<< orphan*/  d3dx_free_param_eval (struct d3dx_param_eval*) ; 
 int /*<<< orphan*/  dump_bytecode (void*,unsigned int) ; 
 int /*<<< orphan*/  dump_preshader (TYPE_3__*) ; 
 int /*<<< orphan*/  dump_registers (TYPE_1__*) ; 
 unsigned int* find_bytecode_comment (unsigned int*,unsigned int,int /*<<< orphan*/ ,unsigned int*) ; 
 struct d3dx_param_eval* get_constants_desc (unsigned int*,TYPE_1__*,struct d3dx9_base_effect*,char const**,unsigned int,TYPE_3__*) ; 
 struct d3dx_param_eval* parse_preshader (TYPE_3__*,unsigned int*,unsigned int,struct d3dx9_base_effect*) ; 
 struct d3dx_param_eval* regstore_alloc_table (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  shad_regset2table ; 
 int /*<<< orphan*/  update_table_sizes_consts (int /*<<< orphan*/ ,TYPE_1__*) ; 

HRESULT d3dx_create_param_eval(struct d3dx9_base_effect *base_effect, void *byte_code, unsigned int byte_code_size,
        D3DXPARAMETER_TYPE type, struct d3dx_param_eval **peval_out, ULONG64 *version_counter,
        const char **skip_constants, unsigned int skip_constants_count)
{
    struct d3dx_param_eval *peval;
    unsigned int *ptr, *shader_ptr = NULL;
    unsigned int i;
    BOOL shader;
    unsigned int count, pres_size;
    HRESULT ret;

    TRACE("base_effect %p, byte_code %p, byte_code_size %u, type %u, peval_out %p.\n",
            base_effect, byte_code, byte_code_size, type, peval_out);

    count = byte_code_size / sizeof(unsigned int);
    if (!byte_code || !count)
    {
        *peval_out = NULL;
        return D3D_OK;
    }

    peval = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*peval));
    if (!peval)
    {
        ret = E_OUTOFMEMORY;
        goto err_out;
    }
    peval->version_counter = version_counter;

    peval->param_type = type;
    switch (type)
    {
        case D3DXPT_VERTEXSHADER:
        case D3DXPT_PIXELSHADER:
            shader = TRUE;
            break;
        default:
            shader = FALSE;
            break;
    }
    peval->shader_inputs.regset2table = shad_regset2table;

    ptr = (unsigned int *)byte_code;
    if (shader)
    {
        if ((*ptr & 0xfffe0000) != 0xfffe0000)
        {
            FIXME("Invalid shader signature %#x.\n", *ptr);
            ret = D3DXERR_INVALIDDATA;
            goto err_out;
        }
        TRACE("Shader version %#x.\n", *ptr & 0xffff);
        shader_ptr = ptr;
        ptr = find_bytecode_comment(ptr + 1, count - 1, FOURCC_PRES, &pres_size);
        if (!ptr)
            TRACE("No preshader found.\n");
    }
    else
    {
        pres_size = count;
    }

    if (ptr && FAILED(ret = parse_preshader(&peval->pres, ptr, pres_size, base_effect)))
    {
        FIXME("Failed parsing preshader, byte code for analysis follows.\n");
        dump_bytecode(byte_code, byte_code_size);
        goto err_out;
    }

    if (shader)
    {
        if (FAILED(ret = get_constants_desc(shader_ptr, &peval->shader_inputs, base_effect,
                skip_constants, skip_constants_count, &peval->pres)))
        {
            TRACE("Could not get shader constant table, hr %#x.\n", ret);
            goto err_out;
        }
        update_table_sizes_consts(peval->pres.regs.table_sizes, &peval->shader_inputs);
    }

    for (i = PRES_REGTAB_FIRST_SHADER; i < PRES_REGTAB_COUNT; ++i)
    {
        if (FAILED(ret = regstore_alloc_table(&peval->pres.regs, i)))
            goto err_out;
    }

    if (TRACE_ON(d3dx))
    {
        dump_bytecode(byte_code, byte_code_size);
        dump_preshader(&peval->pres);
        if (shader)
        {
            TRACE("// Shader registers:\n");
            dump_registers(&peval->shader_inputs);
        }
    }
    *peval_out = peval;
    TRACE("Created parameter evaluator %p.\n", *peval_out);
    return D3D_OK;

err_out:
    WARN("Error creating parameter evaluator.\n");
    if (TRACE_ON(d3dx))
        dump_bytecode(byte_code, byte_code_size);

    d3dx_free_param_eval(peval);
    *peval_out = NULL;
    return ret;
}