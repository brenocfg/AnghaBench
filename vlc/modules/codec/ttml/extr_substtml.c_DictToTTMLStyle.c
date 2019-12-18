#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i_size; TYPE_2__** p_entries; } ;
typedef  TYPE_1__ vlc_dictionary_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_value; int /*<<< orphan*/  psz_key; struct TYPE_6__* p_next; } ;
typedef  TYPE_2__ vlc_dictionary_entry_t ;
typedef  int /*<<< orphan*/  ttml_style_t ;
typedef  int /*<<< orphan*/  ttml_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ComputeTTMLStyles (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FillTTMLStyle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DictToTTMLStyle( ttml_context_t *p_ctx, const vlc_dictionary_t *p_dict,
                             ttml_style_t *p_ttml_style )
{
    for( int i = 0; i < p_dict->i_size; ++i )
    {
        for ( vlc_dictionary_entry_t* p_entry = p_dict->p_entries[i];
              p_entry != NULL; p_entry = p_entry->p_next )
        {
            FillTTMLStyle( p_entry->psz_key, p_entry->p_value, p_ttml_style );
        }
    }
    ComputeTTMLStyles( p_ctx, p_dict, p_ttml_style );
}