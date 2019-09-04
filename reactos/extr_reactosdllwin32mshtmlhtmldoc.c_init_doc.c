#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_27__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_26__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_25__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_24__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_23__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_22__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_21__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_20__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_19__ {TYPE_9__ IHTMLDocument2_iface; int /*<<< orphan*/  cp_container; int /*<<< orphan*/  task_magic; int /*<<< orphan*/ * dispex; int /*<<< orphan*/ * unk_impl; TYPE_8__ IProvideClassInfo_iface; TYPE_7__ ISupportErrorInfo_iface; TYPE_6__ IDispatchEx_iface; TYPE_5__ IHTMLDocument7_iface; TYPE_4__ IHTMLDocument6_iface; TYPE_3__ IHTMLDocument5_iface; TYPE_2__ IHTMLDocument4_iface; TYPE_1__ IHTMLDocument3_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  TYPE_10__ HTMLDocument ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionPointContainer_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DocDispatchExVtbl ; 
 int /*<<< orphan*/  HTMLDocument3Vtbl ; 
 int /*<<< orphan*/  HTMLDocument4Vtbl ; 
 int /*<<< orphan*/  HTMLDocument5Vtbl ; 
 int /*<<< orphan*/  HTMLDocument6Vtbl ; 
 int /*<<< orphan*/  HTMLDocument7Vtbl ; 
 int /*<<< orphan*/  HTMLDocumentVtbl ; 
 int /*<<< orphan*/  HTMLDocument_Hlink_Init (TYPE_10__*) ; 
 int /*<<< orphan*/  HTMLDocument_OleCmd_Init (TYPE_10__*) ; 
 int /*<<< orphan*/  HTMLDocument_OleObj_Init (TYPE_10__*) ; 
 int /*<<< orphan*/  HTMLDocument_Persist_Init (TYPE_10__*) ; 
 int /*<<< orphan*/  HTMLDocument_Service_Init (TYPE_10__*) ; 
 int /*<<< orphan*/  HTMLDocument_View_Init (TYPE_10__*) ; 
 int /*<<< orphan*/  HTMLDocument_Window_Init (TYPE_10__*) ; 
 int /*<<< orphan*/  HTMLDocument_cpc ; 
 int /*<<< orphan*/  ProvideClassInfoVtbl ; 
 int /*<<< orphan*/  SupportErrorInfoVtbl ; 
 int /*<<< orphan*/  get_task_target_magic () ; 

__attribute__((used)) static void init_doc(HTMLDocument *doc, IUnknown *unk_impl, IDispatchEx *dispex)
{
    doc->IHTMLDocument2_iface.lpVtbl = &HTMLDocumentVtbl;
    doc->IHTMLDocument3_iface.lpVtbl = &HTMLDocument3Vtbl;
    doc->IHTMLDocument4_iface.lpVtbl = &HTMLDocument4Vtbl;
    doc->IHTMLDocument5_iface.lpVtbl = &HTMLDocument5Vtbl;
    doc->IHTMLDocument6_iface.lpVtbl = &HTMLDocument6Vtbl;
    doc->IHTMLDocument7_iface.lpVtbl = &HTMLDocument7Vtbl;
    doc->IDispatchEx_iface.lpVtbl = &DocDispatchExVtbl;
    doc->ISupportErrorInfo_iface.lpVtbl = &SupportErrorInfoVtbl;
    doc->IProvideClassInfo_iface.lpVtbl = &ProvideClassInfoVtbl;

    doc->unk_impl = unk_impl;
    doc->dispex = dispex;
    doc->task_magic = get_task_target_magic();

    HTMLDocument_Persist_Init(doc);
    HTMLDocument_OleCmd_Init(doc);
    HTMLDocument_OleObj_Init(doc);
    HTMLDocument_View_Init(doc);
    HTMLDocument_Window_Init(doc);
    HTMLDocument_Service_Init(doc);
    HTMLDocument_Hlink_Init(doc);

    ConnectionPointContainer_Init(&doc->cp_container, (IUnknown*)&doc->IHTMLDocument2_iface, HTMLDocument_cpc);
}