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
typedef  int /*<<< orphan*/  ITypeInfoImpl ;
typedef  int /*<<< orphan*/  ITypeInfo2 ;
typedef  int /*<<< orphan*/  ITypeInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * impl_from_ITypeInfo2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline ITypeInfoImpl *impl_from_ITypeInfo( ITypeInfo *iface )
{
    return impl_from_ITypeInfo2((ITypeInfo2*)iface);
}