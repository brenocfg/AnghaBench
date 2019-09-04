#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ strbuf ;
typedef  int /*<<< orphan*/  Registrar ;
typedef  int /*<<< orphan*/  LPCOLESTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_preprocess (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  do_process_root_key (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*) ; 

__attribute__((used)) static HRESULT string_register(Registrar *This, LPCOLESTR data, BOOL do_register)
{
    strbuf buf;
    HRESULT hres;

    TRACE("(%p %s %x)\n", This, debugstr_w(data), do_register);

    strbuf_init(&buf);
    hres = do_preprocess(This, data, &buf);
    if(FAILED(hres)) {
        WARN("preprocessing failed!\n");
        HeapFree(GetProcessHeap(), 0, buf.str);
        return hres;
    }

    hres = do_process_root_key(buf.str, do_register);
    if(FAILED(hres) && do_register)
        do_process_root_key(buf.str, FALSE);

    HeapFree(GetProcessHeap(), 0, buf.str);
    return hres;
}