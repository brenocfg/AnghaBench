#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gunichar ;
typedef  size_t glong ;
typedef  char gchar ;
typedef  scalar_t__ gboolean ;
typedef  enum CharClass { ____Placeholder_CharClass } CharClass ;
struct TYPE_2__ {scalar_t__ case_sensitive; } ;

/* Variables and functions */
 scalar_t__ CONSECUTIVE_SCORE ; 
 scalar_t__ FALSE ; 
 size_t FUZZY_SCORER_MAX_LENGTH ; 
 scalar_t__ GAP_SCORE ; 
 size_t LEADING_GAP_SCORE ; 
 size_t MAX (scalar_t__,int) ; 
 int MIN_SCORE ; 
 int NON_WORD ; 
 int PATTERN_NON_START_MULTIPLIER ; 
 int PATTERN_START_MULTIPLIER ; 
 scalar_t__ TRUE ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  g_free (int*) ; 
 int* g_malloc_n (size_t,int) ; 
 scalar_t__ g_unichar_isspace (scalar_t__) ; 
 scalar_t__ g_unichar_tolower (scalar_t__) ; 
 scalar_t__ g_utf8_get_char (char const*) ; 
 char* g_utf8_next_char (char const*) ; 
 int rofi_scorer_get_character_class (scalar_t__) ; 
 int rofi_scorer_get_score_for (int,int) ; 

int rofi_scorer_fuzzy_evaluate ( const char *pattern, glong plen, const char *str, glong slen )
{
    if ( slen > FUZZY_SCORER_MAX_LENGTH ) {
        return -MIN_SCORE;
    }
    glong    pi, si;
    // whether we are aligning the first character of pattern
    gboolean pfirst = TRUE;
    // whether the start of a word in pattern
    gboolean pstart = TRUE;
    // score for each position
    int      *score = g_malloc_n ( slen, sizeof ( int ) );
    // dp[i]: maximum value by aligning pattern[0..pi] to str[0..si]
    int      *dp = g_malloc_n ( slen, sizeof ( int ) );
    // uleft: value of the upper left cell; ulefts: maximum value of uleft and cells on the left. The arbitrary initial
    // values suppress warnings.
    int            uleft = 0, ulefts = 0, left, lefts;
    const gchar    *pit = pattern, *sit;
    enum CharClass prev = NON_WORD;
    for ( si = 0, sit = str; si < slen; si++, sit = g_utf8_next_char ( sit ) ) {
        enum CharClass cur = rofi_scorer_get_character_class ( g_utf8_get_char ( sit ) );
        score[si] = rofi_scorer_get_score_for ( prev, cur );
        prev      = cur;
        dp[si]    = MIN_SCORE;
    }
    for ( pi = 0; pi < plen; pi++, pit = g_utf8_next_char ( pit ) ) {
        gunichar pc = g_utf8_get_char ( pit ), sc;
        if ( g_unichar_isspace ( pc ) ) {
            pstart = TRUE;
            continue;
        }
        lefts = MIN_SCORE;
        for ( si = 0, sit = str; si < slen; si++, sit = g_utf8_next_char ( sit ) ) {
            left  = dp[si];
            lefts = MAX ( lefts + GAP_SCORE, left );
            sc    = g_utf8_get_char ( sit );
            if ( config.case_sensitive
                 ? pc == sc
                 : g_unichar_tolower ( pc ) == g_unichar_tolower ( sc ) ) {
                int t = score[si] * ( pstart ? PATTERN_START_MULTIPLIER : PATTERN_NON_START_MULTIPLIER );
                dp[si] = pfirst
                         ? LEADING_GAP_SCORE * si + t
                         : MAX ( uleft + CONSECUTIVE_SCORE, ulefts + t );
            }
            else {
                dp[si] = MIN_SCORE;
            }
            uleft  = left;
            ulefts = lefts;
        }
        pfirst = pstart = FALSE;
    }
    lefts = MIN_SCORE;
    for ( si = 0; si < slen; si++ ) {
        lefts = MAX ( lefts + GAP_SCORE, dp[si] );
    }
    g_free ( score );
    g_free ( dp );
    return -lefts;
}