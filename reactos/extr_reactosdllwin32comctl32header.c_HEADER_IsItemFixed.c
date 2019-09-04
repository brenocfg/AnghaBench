#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dwStyle; TYPE_1__* items; } ;
struct TYPE_4__ {int fmt; } ;
typedef  size_t INT ;
typedef  TYPE_2__ HEADER_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 int HDF_FIXEDWIDTH ; 
 int HDS_NOSIZING ; 

__attribute__((used)) static inline BOOL
HEADER_IsItemFixed(const HEADER_INFO *infoPtr, INT iItem)
{
    return (infoPtr->dwStyle & HDS_NOSIZING) || (infoPtr->items[iItem].fmt & HDF_FIXEDWIDTH);
}