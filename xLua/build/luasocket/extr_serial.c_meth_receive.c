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
typedef  TYPE_1__* p_unix ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  auxiliar_checkclass (int /*<<< orphan*/ *,char*,int) ; 
 int buffer_meth_receive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meth_receive(lua_State *L) {
    p_unix un = (p_unix) auxiliar_checkclass(L, "serial{client}", 1);
    return buffer_meth_receive(L, &un->buf);
}