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
typedef  scalar_t__ gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GString ;
typedef  int /*<<< orphan*/  GMatchInfo ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_hash_table_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_match_info_fetch (int /*<<< orphan*/  const*,int) ; 
 int g_match_info_get_match_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_string_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean helper_eval_cb2 ( const GMatchInfo *info, GString *res, gpointer data )
{
    gchar *match;
    // Get the match
    int num_match = g_match_info_get_match_count(info);
    // Just {text} This is inside () 5.
    if ( num_match == 5 ) {
        match = g_match_info_fetch ( info, 4);
        if ( match != NULL ) {
            // Lookup the match, so we can replace it.
            gchar *r = g_hash_table_lookup ( (GHashTable *) data, match );
            if ( r != NULL ) {
                // Append the replacement to the string.
                g_string_append ( res, r );
            }
            // Free match.
            g_free ( match );
        }
    }
    // {} with [] guard around it.
    else if ( num_match == 4 ) {
        match = g_match_info_fetch ( info, 2);
        if ( match != NULL ) {
            // Lookup the match, so we can replace it.
            gchar *r = g_hash_table_lookup ( (GHashTable *) data, match );
            if ( r != NULL ) {
                // Add (optional) prefix
                gchar *prefix = g_match_info_fetch (info, 1);
                g_string_append ( res, prefix );
                g_free (prefix );
                // Append the replacement to the string.
                g_string_append ( res, r );
                // Add (optional) postfix
                gchar *post = g_match_info_fetch (info, 3);
                g_string_append ( res, post );
                g_free (post );
            }
            // Free match.
            g_free ( match );
        }
    }
    // Else we have an invalid match.
    // Continue replacement.
    return FALSE;
}