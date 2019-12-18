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
struct TYPE_4__ {int /*<<< orphan*/  psz_protocol; scalar_t__ psz_path; } ;
typedef  TYPE_1__ vlc_url_t ;

/* Variables and functions */
 scalar_t__ protocol_is_smb (TYPE_1__ const*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool
protocol_store_path(const vlc_url_t *p_url)
{
    return p_url->psz_path
      && (strncasecmp(p_url->psz_protocol, "http", 4) == 0
      || strcasecmp(p_url->psz_protocol, "rtsp") == 0
      || protocol_is_smb(p_url));
}