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
struct TYPE_4__ {int /*<<< orphan*/  dwConnection; scalar_t__ pAdvSink; int /*<<< orphan*/  advf; int /*<<< orphan*/  formatetc; } ;
typedef  TYPE_1__ STATDATA ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAdviseSink_AddRef (scalar_t__) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  copy_formatetc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT copy_statdata(STATDATA *dst, const STATDATA *src)
{
    HRESULT hr;

    hr = copy_formatetc( &dst->formatetc, &src->formatetc );
    if (FAILED(hr)) return hr;
    dst->advf = src->advf;
    dst->pAdvSink = src->pAdvSink;
    if (dst->pAdvSink) IAdviseSink_AddRef( dst->pAdvSink );
    dst->dwConnection = src->dwConnection;
    return S_OK;
}