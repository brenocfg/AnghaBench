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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 scalar_t__ ID_BROWSE_GOTOFAV_FIRST ; 
 int /*<<< orphan*/  get_fav_url_from_id (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_fav_menu_data(HMENU menu)
{
    LPWSTR url;
    int i;

    for(i = 0; (url = get_fav_url_from_id(menu, ID_BROWSE_GOTOFAV_FIRST + i)); i++)
        heap_free( url );
}