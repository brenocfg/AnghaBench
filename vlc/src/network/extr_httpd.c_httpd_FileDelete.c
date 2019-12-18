#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  url; int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_1__ httpd_file_t ;
typedef  int /*<<< orphan*/  httpd_file_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  httpd_UrlDelete (int /*<<< orphan*/ ) ; 

httpd_file_sys_t *httpd_FileDelete(httpd_file_t *file)
{
    httpd_file_sys_t *p_sys = file->p_sys;

    httpd_UrlDelete(file->url);
    free(file);
    return p_sys;
}