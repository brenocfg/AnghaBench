#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT16 ;
typedef  size_t UINT ;
struct TYPE_2__ {size_t wMaxId; int nMapper; int /*<<< orphan*/ * lpMlds; } ;
typedef  int /*<<< orphan*/ * LPWINE_MLD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,size_t,size_t) ; 
 TYPE_1__* llTypes ; 

__attribute__((used)) static LPWINE_MLD MMDRV_GetByID(UINT uDevID, UINT type)
{
    TRACE("(%04x, %04x)\n", uDevID, type);
    if (uDevID < llTypes[type].wMaxId)
	return &llTypes[type].lpMlds[uDevID];
    if ((uDevID == (UINT16)-1 || uDevID == (UINT)-1) && llTypes[type].nMapper != -1)
	return &llTypes[type].lpMlds[-1];
    return NULL;
}