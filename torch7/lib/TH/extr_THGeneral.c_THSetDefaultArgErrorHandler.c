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
typedef  scalar_t__ THArgErrorHandlerFunction ;

/* Variables and functions */
 scalar_t__ defaultArgErrorHandler ; 
 void* defaultArgErrorHandlerData ; 
 scalar_t__ defaultArgErrorHandlerFunction ; 

void THSetDefaultArgErrorHandler(THArgErrorHandlerFunction new_handler, void *data)
{
  if (new_handler)
    defaultArgErrorHandler = new_handler;
  else
    defaultArgErrorHandler = defaultArgErrorHandlerFunction;
  defaultArgErrorHandlerData = data;
}