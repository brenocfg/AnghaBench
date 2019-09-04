#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ Level; } ;
typedef  TYPE_1__ MSIFEATURE ;
typedef  scalar_t__ INT ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static inline BOOL is_feature_selected( MSIFEATURE *feature, INT level )
{
    return (feature->Level > 0 && feature->Level <= level);
}