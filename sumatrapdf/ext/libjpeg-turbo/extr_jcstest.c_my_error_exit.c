#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* j_common_ptr ;
struct TYPE_8__ {int /*<<< orphan*/  jb; } ;
typedef  TYPE_3__ error_mgr ;
struct TYPE_7__ {TYPE_1__* err; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* output_message ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void my_error_exit(j_common_ptr cinfo)
{
  error_mgr *myerr = (error_mgr *)cinfo->err;
  (*cinfo->err->output_message)(cinfo);
  longjmp(myerr->jb, 1);
}