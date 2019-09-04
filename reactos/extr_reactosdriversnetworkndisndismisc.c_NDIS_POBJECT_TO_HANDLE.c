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
typedef  int /*<<< orphan*/  PNDIS_HANDLE_OBJECT ;
typedef  int /*<<< orphan*/  NDIS_HANDLE ;

/* Variables and functions */

__inline
NDIS_HANDLE
NDIS_POBJECT_TO_HANDLE ( PNDIS_HANDLE_OBJECT obj )
{
  return (NDIS_HANDLE)obj;
}