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
struct TYPE_5__ {int /*<<< orphan*/  tymed; int /*<<< orphan*/  lindex; int /*<<< orphan*/  dwAspect; int /*<<< orphan*/  ptd; int /*<<< orphan*/  cfFormat; } ;
struct TYPE_6__ {scalar_t__ pAdvSink; int /*<<< orphan*/  dwConnection; int /*<<< orphan*/  advf; TYPE_1__ formatetc; } ;
typedef  TYPE_2__ STATDATA ;
typedef  int /*<<< orphan*/  IOleCache2 ;
typedef  int /*<<< orphan*/  IEnumSTATDATA ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IEnumSTATDATA_Next (int /*<<< orphan*/ *,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumSTATDATA_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IOleCache2_EnumCache (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void check_enum_cache(IOleCache2 *cache, const STATDATA *expect, int num)
{
    IEnumSTATDATA *enum_stat;
    STATDATA stat;
    HRESULT hr;

    hr = IOleCache2_EnumCache( cache, &enum_stat );
    ok( hr == S_OK, "got %08x\n", hr );

    while (IEnumSTATDATA_Next(enum_stat, 1, &stat, NULL) == S_OK)
    {
        ok( stat.formatetc.cfFormat == expect->formatetc.cfFormat, "got %d expect %d\n",
            stat.formatetc.cfFormat, expect->formatetc.cfFormat );
        ok( !stat.formatetc.ptd == !expect->formatetc.ptd, "got %p expect %p\n",
            stat.formatetc.ptd, expect->formatetc.ptd );
        ok( stat.formatetc.dwAspect == expect->formatetc.dwAspect, "got %d expect %d\n",
            stat.formatetc.dwAspect, expect->formatetc.dwAspect );
        ok( stat.formatetc.lindex == expect->formatetc.lindex, "got %d expect %d\n",
            stat.formatetc.lindex, expect->formatetc.lindex );
        ok( stat.formatetc.tymed == expect->formatetc.tymed, "got %d expect %d\n",
            stat.formatetc.tymed, expect->formatetc.tymed );
        ok( stat.advf == expect->advf, "got %d expect %d\n", stat.advf, expect->advf );
        ok( stat.pAdvSink == 0, "got %p\n", stat.pAdvSink );
        ok( stat.dwConnection == expect->dwConnection, "got %d expect %d\n", stat.dwConnection, expect->dwConnection );
        num--;
        expect++;
    }

    ok( num == 0, "incorrect number. num %d\n", num );

    IEnumSTATDATA_Release( enum_stat );
}