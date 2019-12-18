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
struct vlc_http_resource {int dummy; } ;
struct vlc_http_mgr {int dummy; } ;
struct vlc_http_file {struct vlc_http_resource resource; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_http_file*) ; 
 struct vlc_http_file* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_http_file_callbacks ; 
 scalar_t__ vlc_http_res_init (struct vlc_http_resource*,int /*<<< orphan*/ *,struct vlc_http_mgr*,char const*,char const*,char const*) ; 

struct vlc_http_resource *vlc_http_file_create(struct vlc_http_mgr *mgr,
                                               const char *uri, const char *ua,
                                               const char *ref)
{
    struct vlc_http_file *file = malloc(sizeof (*file));
    if (unlikely(file == NULL))
        return NULL;

    if (vlc_http_res_init(&file->resource, &vlc_http_file_callbacks, mgr,
                          uri, ua, ref))
    {
        free(file);
        return NULL;
    }

    file->offset = 0;
    return &file->resource;
}