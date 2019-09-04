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
typedef  scalar_t__ INT_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  TlsSetValue (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  indent_tls_index ; 

__attribute__((used)) static inline void set_indent_level( INT_PTR level )
{
    TlsSetValue( indent_tls_index, (void *)level );
}