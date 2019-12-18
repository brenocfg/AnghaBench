#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int length; int /*<<< orphan*/ * values; } ;
struct TYPE_8__ {TYPE_1__ array; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  TYPE_3__ json_value ;
struct TYPE_10__ {int /*<<< orphan*/  psz_artist; } ;
typedef  TYPE_4__ acoustid_mb_result_t ;

/* Variables and functions */
 scalar_t__ json_array ; 
 int /*<<< orphan*/  json_dupstring (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void parse_artists( const json_value *node, acoustid_mb_result_t *record )
{
    /* take only main */
    if ( !node || node->type != json_array || node->u.array.length < 1 )
        return;
    record->psz_artist = json_dupstring( node->u.array.values[ 0 ], "name" );
}