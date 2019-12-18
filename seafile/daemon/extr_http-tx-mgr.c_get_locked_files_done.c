#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cb_data ;
struct TYPE_7__ {struct TYPE_7__* host; int /*<<< orphan*/  results; int /*<<< orphan*/  user_data; int /*<<< orphan*/  (* callback ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  success; } ;
struct TYPE_6__ {int /*<<< orphan*/  results; int /*<<< orphan*/  success; } ;
typedef  TYPE_1__ HttpLockedFiles ;
typedef  TYPE_2__ GetLockedFilesData ;
typedef  int /*<<< orphan*/  GDestroyNotify ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_2__*) ; 
 int /*<<< orphan*/  g_list_free_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ http_locked_files_res_free ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_locked_files_done (void *vdata)
{
    GetLockedFilesData *data = vdata;
    HttpLockedFiles cb_data;

    memset (&cb_data, 0, sizeof(cb_data));
    cb_data.success = data->success;
    cb_data.results = data->results;

    data->callback (&cb_data, data->user_data);

    g_list_free_full (data->results, (GDestroyNotify)http_locked_files_res_free);

    g_free (data->host);
    g_free (data);
}