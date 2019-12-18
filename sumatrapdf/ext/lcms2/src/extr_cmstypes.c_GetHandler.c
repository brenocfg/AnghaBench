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
typedef  scalar_t__ cmsTagTypeSignature ;
struct TYPE_6__ {scalar_t__ Signature; } ;
typedef  TYPE_1__ cmsTagTypeHandler ;
struct TYPE_7__ {TYPE_1__ Handler; struct TYPE_7__* Next; } ;
typedef  TYPE_2__ _cmsTagTypeLinkedList ;

/* Variables and functions */

__attribute__((used)) static
cmsTagTypeHandler* GetHandler(cmsTagTypeSignature sig, _cmsTagTypeLinkedList* PluginLinkedList, _cmsTagTypeLinkedList* DefaultLinkedList)
{
    _cmsTagTypeLinkedList* pt;

    for (pt = PluginLinkedList;
         pt != NULL;
         pt = pt ->Next) {

            if (sig == pt -> Handler.Signature) return &pt ->Handler;
    }

    for (pt = DefaultLinkedList;
         pt != NULL;
         pt = pt ->Next) {

            if (sig == pt -> Handler.Signature) return &pt ->Handler;
    }

    return NULL;
}