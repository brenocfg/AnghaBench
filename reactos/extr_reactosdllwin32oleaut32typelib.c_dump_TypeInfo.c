#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t typekind; int /*<<< orphan*/  cImplTypes; int /*<<< orphan*/  cVars; int /*<<< orphan*/  cFuncs; int /*<<< orphan*/  wTypeFlags; } ;
struct TYPE_6__ {TYPE_1__ typeattr; int /*<<< orphan*/  impltypes; int /*<<< orphan*/  vardescs; int /*<<< orphan*/  funcdescs; int /*<<< orphan*/  DllName; int /*<<< orphan*/  index; int /*<<< orphan*/  pTypeLib; int /*<<< orphan*/  guid; int /*<<< orphan*/  DocString; int /*<<< orphan*/  Name; int /*<<< orphan*/  ref; } ;
typedef  TYPE_2__ ITypeInfoImpl ;

/* Variables and functions */
 size_t TKIND_MODULE ; 
 int /*<<< orphan*/  TLB_get_bstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLB_get_guidref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__ const*,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_TLBFuncDesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_TLBImplType (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_TLBVarDesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ole ; 
 int /*<<< orphan*/ * typekind_desc ; 

__attribute__((used)) static void dump_TypeInfo(const ITypeInfoImpl * pty)
{
    TRACE("%p ref=%u\n", pty, pty->ref);
    TRACE("%s %s\n", debugstr_w(TLB_get_bstr(pty->Name)), debugstr_w(TLB_get_bstr(pty->DocString)));
    TRACE("attr:%s\n", debugstr_guid(TLB_get_guidref(pty->guid)));
    TRACE("kind:%s\n", typekind_desc[pty->typeattr.typekind]);
    TRACE("fct:%u var:%u impl:%u\n", pty->typeattr.cFuncs, pty->typeattr.cVars, pty->typeattr.cImplTypes);
    TRACE("wTypeFlags: 0x%04x\n", pty->typeattr.wTypeFlags);
    TRACE("parent tlb:%p index in TLB:%u\n",pty->pTypeLib, pty->index);
    if (pty->typeattr.typekind == TKIND_MODULE) TRACE("dllname:%s\n", debugstr_w(TLB_get_bstr(pty->DllName)));
    if (TRACE_ON(ole))
        dump_TLBFuncDesc(pty->funcdescs, pty->typeattr.cFuncs);
    dump_TLBVarDesc(pty->vardescs, pty->typeattr.cVars);
    dump_TLBImplType(pty->impltypes, pty->typeattr.cImplTypes);
}