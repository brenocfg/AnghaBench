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
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t HTTP_TASK_ERR_CONNECT ; 
 size_t HTTP_TASK_ERR_NET ; 
 size_t HTTP_TASK_ERR_RESOLVE_HOST ; 
 size_t HTTP_TASK_ERR_RESOLVE_PROXY ; 
 size_t HTTP_TASK_ERR_SSL ; 
 size_t HTTP_TASK_ERR_TX ; 
 size_t HTTP_TASK_ERR_TX_TIMEOUT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * http_task_error_strs ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

gboolean
is_http_task_net_error (char *err_detail)
{
    if (err_detail &&
        (strcmp (err_detail,  http_task_error_strs[HTTP_TASK_ERR_NET]) == 0 ||
         strcmp (err_detail,  http_task_error_strs[HTTP_TASK_ERR_RESOLVE_PROXY]) == 0 ||
         strcmp (err_detail,  http_task_error_strs[HTTP_TASK_ERR_RESOLVE_HOST]) == 0 ||
         strcmp (err_detail,  http_task_error_strs[HTTP_TASK_ERR_CONNECT]) == 0 ||
         strcmp (err_detail,  http_task_error_strs[HTTP_TASK_ERR_SSL]) == 0 ||
         strcmp (err_detail,  http_task_error_strs[HTTP_TASK_ERR_TX]) == 0 ||
         strcmp (err_detail,  http_task_error_strs[HTTP_TASK_ERR_TX_TIMEOUT]) == 0))
        return TRUE;
    else
        return FALSE;
}