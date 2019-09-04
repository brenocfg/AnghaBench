#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ left; scalar_t__ right; scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_8__ {TYPE_1__ rect; } ;
struct TYPE_7__ {scalar_t__ right; scalar_t__ bottom; scalar_t__ left; scalar_t__ top; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ PluginHost ;

/* Variables and functions */

__attribute__((used)) static void get_pos_rect(PluginHost *host, RECT *ret)
{
    ret->top = 0;
    ret->left = 0;
    ret->bottom = host->rect.bottom - host->rect.top;
    ret->right = host->rect.right - host->rect.left;
}