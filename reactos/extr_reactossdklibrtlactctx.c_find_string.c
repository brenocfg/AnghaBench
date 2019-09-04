#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_6__ {int /*<<< orphan*/ * hActCtx; } ;
typedef  TYPE_1__* PACTCTX_SECTION_KEYED_DATA ;
typedef  scalar_t__ NTSTATUS ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  ACTIVATION_CONTEXT ;

/* Variables and functions */
#define  ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION 132 
#define  ACTIVATION_CONTEXT_SECTION_COM_PROGID_REDIRECTION 131 
#define  ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION 130 
#define  ACTIVATION_CONTEXT_SECTION_GLOBAL_OBJECT_RENAME_TABLE 129 
#define  ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION 128 
 int /*<<< orphan*/  DPRINT1 (char*,int) ; 
 int FIND_ACTCTX_SECTION_KEY_RETURN_HACTCTX ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ STATUS_SXS_KEY_NOT_FOUND ; 
 scalar_t__ STATUS_SXS_SECTION_NOT_FOUND ; 
 int /*<<< orphan*/  actctx_addref (int /*<<< orphan*/ *) ; 
 scalar_t__ find_dll_redirection (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 scalar_t__ find_progid_redirection (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 scalar_t__ find_window_class (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*) ; 

__attribute__((used)) static NTSTATUS find_string(ACTIVATION_CONTEXT* actctx, ULONG section_kind,
                            const UNICODE_STRING *section_name,
                            DWORD flags, PACTCTX_SECTION_KEYED_DATA data)
{
    NTSTATUS status;

    switch (section_kind)
    {
    case ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION:
        DPRINT1("Unsupported yet section_kind %x\n", section_kind);
        return STATUS_SXS_KEY_NOT_FOUND;
    case ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION:
        status = find_dll_redirection(actctx, section_name, data);
        break;
    case ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION:
        status = find_window_class(actctx, section_name, data);
        break;
    case ACTIVATION_CONTEXT_SECTION_COM_PROGID_REDIRECTION:
        status = find_progid_redirection(actctx, section_name, data);
        break;
    case ACTIVATION_CONTEXT_SECTION_GLOBAL_OBJECT_RENAME_TABLE:
        DPRINT1("Unsupported yet section_kind %x\n", section_kind);
        return STATUS_SXS_SECTION_NOT_FOUND;
    default:
        DPRINT1("Unknown section_kind %x\n", section_kind);
        return STATUS_SXS_SECTION_NOT_FOUND;
    }

    if (status != STATUS_SUCCESS) return status;

    if (data && (flags & FIND_ACTCTX_SECTION_KEY_RETURN_HACTCTX))
    {
        actctx_addref(actctx);
        data->hActCtx = actctx;
    }
    return STATUS_SUCCESS;
}