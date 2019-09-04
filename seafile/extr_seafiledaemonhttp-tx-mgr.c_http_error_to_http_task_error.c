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

/* Variables and functions */
 int HTTP_BAD_REQUEST ; 
 int HTTP_FORBIDDEN ; 
 int HTTP_INTERNAL_SERVER_ERROR ; 
 int HTTP_NOT_FOUND ; 
 int HTTP_NO_QUOTA ; 
 int HTTP_REPO_CORRUPTED ; 
 int HTTP_REPO_DELETED ; 
 int HTTP_TASK_ERR_BAD_REQUEST ; 
 int HTTP_TASK_ERR_FORBIDDEN ; 
 int HTTP_TASK_ERR_NO_QUOTA ; 
 int HTTP_TASK_ERR_REPO_CORRUPTED ; 
 int HTTP_TASK_ERR_REPO_DELETED ; 
 int HTTP_TASK_ERR_SERVER ; 
 int HTTP_TASK_ERR_UNKNOWN ; 

__attribute__((used)) static int
http_error_to_http_task_error (int status)
{
    if (status == HTTP_BAD_REQUEST)
        return HTTP_TASK_ERR_BAD_REQUEST;
    else if (status == HTTP_FORBIDDEN)
        return HTTP_TASK_ERR_FORBIDDEN;
    else if (status >= HTTP_INTERNAL_SERVER_ERROR)
        return HTTP_TASK_ERR_SERVER;
    else if (status == HTTP_NOT_FOUND)
        return HTTP_TASK_ERR_SERVER;
    else if (status == HTTP_NO_QUOTA)
        return HTTP_TASK_ERR_NO_QUOTA;
    else if (status == HTTP_REPO_DELETED)
        return HTTP_TASK_ERR_REPO_DELETED;
    else if (status == HTTP_REPO_CORRUPTED)
        return HTTP_TASK_ERR_REPO_CORRUPTED;
    else
        return HTTP_TASK_ERR_UNKNOWN;
}