#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * vals; } ;
typedef  TYPE_1__ paramValues_t ;
struct TYPE_7__ {int /*<<< orphan*/  strategy; int /*<<< orphan*/  targetLength; int /*<<< orphan*/  minMatch; int /*<<< orphan*/  searchLog; int /*<<< orphan*/  hashLog; int /*<<< orphan*/  chainLog; int /*<<< orphan*/  windowLog; } ;
typedef  TYPE_2__ ZSTD_compressionParameters ;

/* Variables and functions */
 size_t clog_ind ; 
 size_t hlog_ind ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 size_t mml_ind ; 
 size_t slog_ind ; 
 size_t strt_ind ; 
 size_t tlen_ind ; 
 size_t wlog_ind ; 

__attribute__((used)) static ZSTD_compressionParameters pvalsToCParams(paramValues_t p)
{
    ZSTD_compressionParameters c;
    memset(&c, 0, sizeof(ZSTD_compressionParameters));
    c.windowLog = p.vals[wlog_ind];
    c.chainLog = p.vals[clog_ind];
    c.hashLog = p.vals[hlog_ind];
    c.searchLog = p.vals[slog_ind];
    c.minMatch = p.vals[mml_ind];
    c.targetLength = p.vals[tlen_ind];
    c.strategy = p.vals[strt_ind];
    /* no forceAttachDict */
    return c;
}