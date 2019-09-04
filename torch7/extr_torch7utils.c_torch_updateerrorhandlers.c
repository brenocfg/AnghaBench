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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  THSetArgErrorHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THSetErrorHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaTorchArgErrorHandlerFunction ; 
 int /*<<< orphan*/  luaTorchErrorHandlerFunction ; 

__attribute__((used)) static int torch_updateerrorhandlers(lua_State *L)
{
  THSetErrorHandler(luaTorchErrorHandlerFunction, L);
  THSetArgErrorHandler(luaTorchArgErrorHandlerFunction, L);
  return 0;
}