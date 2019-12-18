#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  psz_rating; int /*<<< orphan*/  rating; int /*<<< orphan*/  psz_name; } ;
struct TYPE_8__ {TYPE_4__ current; TYPE_4__ future; } ;
struct TYPE_9__ {int i_type; TYPE_1__ meta; scalar_t__ b_future; } ;
typedef  TYPE_2__ xds_t ;
struct TYPE_10__ {int* p_data; int /*<<< orphan*/  i_data; } ;
typedef  TYPE_3__ xds_packet_t ;
typedef  TYPE_4__ xds_meta_program_t ;

/* Variables and functions */
 int /*<<< orphan*/  XDS_META_PROGRAM_RATING_MPAA ; 
 int /*<<< orphan*/  XDS_META_PROGRAM_RATING_NONE ; 
 int /*<<< orphan*/  XDS_META_PROGRAM_RATING_TPG ; 
 int /*<<< orphan*/  XdsChangeString (TYPE_2__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  XdsStringUtf8 (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void XdsDecodeCurrentFuture( xds_t *h, xds_packet_t *pk )
{
    xds_meta_program_t *p_prg = h->b_future ? &h->meta.future : &h->meta.current;
    char name[2*32+1];
    int i_rating;

    switch( h->i_type )
    {
    case 0x03:
        XdsStringUtf8( name, pk->p_data, pk->i_data );
        if( XdsChangeString( h, &p_prg->psz_name, name ) )
        {
            //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Current/Future (Program Name) %d'\n", pk->i_data );
            //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: ====> program name %s\n", name );
        }
        break;
    case 0x05:
        i_rating = (pk->p_data[0] & 0x18);
        if( i_rating == 0x08 )
        {
            /* TPG */
            static const char *pppsz_ratings[8][2] = {
                { "None",   "No rating (no content advisory)" },
                { "TV-Y",   "All Children (no content advisory)" },
                { "TV-Y7",  "Directed to Older Children (V = Fantasy Violence)" },
                { "TV-G",   "General Audience (no content advisory)" },
                { "TV-PG",  "Parental Guidance Suggested" },
                { "TV-14",  "Parents Strongly Cautioned" },
                { "TV-MA",  "Mature Audience Only" },
                { "None",   "No rating (no content advisory)" }
            };
            p_prg->rating = XDS_META_PROGRAM_RATING_TPG;
            if( XdsChangeString( h, &p_prg->psz_rating, pppsz_ratings[pk->p_data[1]&0x07][0] ) )
            {
                //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Current/Future (Rating) %d'\n", pk->i_data );
                //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: ====> TPG Rating %s (%s)\n",
                //         pppsz_ratings[pk->p_data[1]&0x07][0], pppsz_ratings[pk->p_data[1]&0x07][1] );
            }
        }
        else if( i_rating == 0x00 || i_rating == 0x10 )
        {
            /* MPAA */
            static const char *pppsz_ratings[8][2] = {
                { "N/A",    "N/A" },
                { "G",      "General Audiences" },
                { "PG",     "Parental Guidance Suggested" },
                { "PG-13",  "Parents Strongly Cautioned" },
                { "R",      "Restricted" },
                { "NC-17",  "No one 17 and under admitted" },
                { "X",      "No one under 17 admitted" },
                { "NR",     "Not Rated" },
            };
            p_prg->rating = XDS_META_PROGRAM_RATING_MPAA;
            if( XdsChangeString( h, &p_prg->psz_rating, pppsz_ratings[pk->p_data[0]&0x07][0] ) )
            {
                //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Current/Future (Rating) %d'\n", pk->i_data );
                //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: ====> TPG Rating %s (%s)\n",
                //         pppsz_ratings[pk->p_data[0]&0x07][0], pppsz_ratings[pk->p_data[0]&0x07][1] );
            }
        }
        else
        {
            /* Non US Rating TODO */
            assert( i_rating == 0x18 ); // only left value possible */
            p_prg->rating = XDS_META_PROGRAM_RATING_NONE;
            if( XdsChangeString( h, &p_prg->psz_rating, NULL ) )
            {
                //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Current/Future (Rating) %d'\n", pk->i_data );
                //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: ====> 0x%2.2x 0x%2.2x\n", pk->p_data[0], pk->p_data[1] );
            }
        }
        break;

    default:
#ifdef TY_XDS_DEBUG
        fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Current/Future (Unknown 0x%x)'\n", h->i_type );
#endif
        break;
    }
}