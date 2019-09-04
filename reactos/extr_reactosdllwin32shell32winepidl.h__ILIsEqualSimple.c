#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ cb; } ;
struct TYPE_8__ {TYPE_1__ mkid; } ;
typedef  TYPE_2__* LPCITEMIDLIST ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (TYPE_2__*,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static inline 
BOOL    _ILIsEqualSimple        (LPCITEMIDLIST pidlA, LPCITEMIDLIST pidlB)
{
    return (pidlA->mkid.cb > 0 && !memcmp(pidlA, pidlB, pidlA->mkid.cb)) ||
            (!pidlA->mkid.cb && !pidlB->mkid.cb);
}