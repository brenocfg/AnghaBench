#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  hEnhMetaFile; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  TYPE_3__ SIZEL ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FORMATETC ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ME_CommitUndo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_UpdateRepaint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseStgMedium (TYPE_2__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_static_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static HRESULT paste_emf(ME_TextEditor *editor, FORMATETC *fmt, STGMEDIUM *med)
{
    HRESULT hr;
    SIZEL sz = {0, 0};

    hr = insert_static_object( editor, med->u.hEnhMetaFile, NULL, &sz );
    if (SUCCEEDED(hr))
    {
        ME_CommitUndo( editor );
        ME_UpdateRepaint( editor, FALSE );
    }
    else
        ReleaseStgMedium( med );

    return hr;
}