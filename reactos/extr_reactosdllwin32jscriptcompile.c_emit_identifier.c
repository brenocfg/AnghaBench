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
typedef  int /*<<< orphan*/  compiler_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ident ; 
 int /*<<< orphan*/  OP_local ; 
 scalar_t__ bind_local (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  push_instr_bstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  push_instr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT emit_identifier(compiler_ctx_t *ctx, const WCHAR *identifier)
{
    int local_ref;
    if(bind_local(ctx, identifier, &local_ref))
        return push_instr_int(ctx, OP_local, local_ref);
    return push_instr_bstr(ctx, OP_ident, identifier);
}