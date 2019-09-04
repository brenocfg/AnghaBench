#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct apartment {int /*<<< orphan*/  oxid; } ;
typedef  int /*<<< orphan*/  OXID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static inline HRESULT apartment_getoxid(const struct apartment *apt, OXID *oxid)
{
    *oxid = apt->oxid;
    return S_OK;
}