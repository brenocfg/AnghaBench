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
typedef  int /*<<< orphan*/  var_t ;
typedef  int /*<<< orphan*/  type_t ;

/* Variables and functions */
 int /*<<< orphan*/  write_procformatstring_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int*,int /*<<< orphan*/ ) ; 

unsigned int get_size_procformatstring_func(const type_t *iface, const var_t *func)
{
    unsigned int offset = 0;
    write_procformatstring_func( NULL, 0, iface, func, &offset, 0 );
    return offset;
}