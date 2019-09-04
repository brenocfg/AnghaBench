#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ (* open ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int is_open; scalar_t__ position; int /*<<< orphan*/  user_data; TYPE_1__ op; } ;
typedef  TYPE_2__ CdioDataSource_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_debug (char*) ; 
 int /*<<< orphan*/  cdio_warn (char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
_cdio_stream_open_if_necessary(CdioDataSource_t *p_obj)
{
  if (!p_obj) return false;

  if (!p_obj->is_open) {
    if (p_obj->op.open(p_obj->user_data)) {
      cdio_warn ("could not open input stream...");
      return false;
    } else {
      cdio_debug ("opened source...");
      p_obj->is_open = 1;
      p_obj->position = 0;
    }
  }
  return true;
}