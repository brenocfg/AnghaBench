#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_5__ {int cParams; int /*<<< orphan*/  elemdescFunc; int /*<<< orphan*/ * lprgelemdescParam; } ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ FUNCDESC ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ITypeInfo_GetFuncDesc (int /*<<< orphan*/ *,int,TYPE_1__**) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseFuncDesc (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  write_param_fs (int /*<<< orphan*/ *,unsigned char*,size_t*,unsigned char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned short*) ; 
 int /*<<< orphan*/  write_proc_func_header (int /*<<< orphan*/ *,TYPE_1__*,int,unsigned char*,size_t*) ; 

__attribute__((used)) static HRESULT write_iface_fs(ITypeInfo *typeinfo, WORD funcs, WORD parentfuncs,
        unsigned char *type, size_t *typelen, unsigned char *proc,
        size_t *proclen, unsigned short *offset)
{
    unsigned short stack_offset;
    WORD proc_idx, param_idx;
    FUNCDESC *desc;
    HRESULT hr;

    for (proc_idx = 3; proc_idx < parentfuncs; proc_idx++)
    {
        if (offset)
            offset[proc_idx - 3] = -1;
    }

    for (proc_idx = 0; proc_idx < funcs; proc_idx++)
    {
        TRACE("Writing procedure %d.\n", proc_idx);

        hr = ITypeInfo_GetFuncDesc(typeinfo, proc_idx, &desc);
        if (FAILED(hr)) return hr;

        if (offset)
            offset[proc_idx + parentfuncs - 3] = *proclen;

        write_proc_func_header(typeinfo, desc, proc_idx + parentfuncs, proc, proclen);

        stack_offset = sizeof(void *);  /* This */
        for (param_idx = 0; param_idx < desc->cParams; param_idx++)
        {
            TRACE("Writing parameter %d.\n", param_idx);
            hr = write_param_fs(typeinfo, type, typelen, proc, proclen,
                    &desc->lprgelemdescParam[param_idx], FALSE, &stack_offset);
            if (FAILED(hr))
            {
                ITypeInfo_ReleaseFuncDesc(typeinfo, desc);
                return hr;
            }
        }

        hr = write_param_fs(typeinfo, type, typelen, proc, proclen,
                &desc->elemdescFunc, TRUE, &stack_offset);
        ITypeInfo_ReleaseFuncDesc(typeinfo, desc);
        if (FAILED(hr)) return hr;
    }

    return S_OK;
}