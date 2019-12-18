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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  input_attachment_t ;
typedef  int /*<<< orphan*/  i_attachments ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  EnsureUTF8 (char*) ; 
 size_t GetDWBE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RM (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strndup (char const*,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_input_attachment_New (char*,char*,char*,int /*<<< orphan*/  const*,size_t) ; 

input_attachment_t* ParseFlacPicture( const uint8_t *p_data, size_t size,
    int i_attachments, int *i_cover_score, int *i_cover_idx )
{
    /* TODO: Merge with ID3v2 copy in modules/meta_engine/taglib.cpp. */
    static const char pi_cover_score[] = {
        0,  /* Other */
        5,  /* 32x32 PNG image that should be used as the file icon */
        4,  /* File icon of a different size or format. */
        20, /* Front cover image of the album. */
        19, /* Back cover image of the album. */
        13, /* Inside leaflet page of the album. */
        18, /* Image from the album itself. */
        17, /* Picture of the lead artist or soloist. */
        16, /* Picture of the artist or performer. */
        14, /* Picture of the conductor. */
        15, /* Picture of the band or orchestra. */
        9,  /* Picture of the composer. */
        8,  /* Picture of the lyricist or text writer. */
        7,  /* Picture of the recording location or studio. */
        10, /* Picture of the artists during recording. */
        11, /* Picture of the artists during performance. */
        6,  /* Picture from a movie or video related to the track. */
        1,  /* Picture of a large, coloured fish. */
        12, /* Illustration related to the track. */
        3,  /* Logo of the band or performer. */
        2   /* Logo of the publisher (record company). */
    };

    uint32_t type, len;

    if( size < 8 )
        return NULL;
#define RM(x) \
    do { \
        assert(size >= (x)); \
        size -= (x); \
        p_data += (x); \
    } while (0)

    type = GetDWBE( p_data );
    RM(4);
    len = GetDWBE( p_data );
    RM(4);

    if( size < len )
        return NULL;

    char *mime = strndup( (const char *)p_data, len );
    if( unlikely(mime == NULL) )
        return NULL;
    RM(len);

    if( size < 4 )
    {
        free( mime );
        return NULL;
    }

    len = GetDWBE( p_data );
    RM(4);

    if( size < len )
    {
        free( mime );
        return NULL;
    }

    input_attachment_t *p_attachment = NULL;
    char *description = strndup( (const char *)p_data, len );
    if( unlikely(description == NULL) )
        goto error;
    RM(len);

    EnsureUTF8( description );

    if( size < 20 )
        goto error;

    RM(4 * 4); /* skip */

    len = GetDWBE( p_data );
    RM(4);

    if( size < len )
        goto error;

    /* printf( "Picture type=%"PRIu32" mime=%s description='%s' "
               "file length=%zu\n", type, mime, description, len ); */

    char name[7 + (sizeof (i_attachments) * 3) + 4 + 1];

    snprintf( name, sizeof (name), "picture%u", i_attachments );

    if( !strcasecmp( mime, "image/jpeg" ) )
        strcat( name, ".jpg" );
    else if( !strcasecmp( mime, "image/png" ) )
        strcat( name, ".png" );

    p_attachment = vlc_input_attachment_New( name, mime, description, p_data,
                                             size /* XXX: len instead? */ );

    if( type < ARRAY_SIZE(pi_cover_score) &&
        *i_cover_score < pi_cover_score[type] )
    {
        *i_cover_idx = i_attachments;
        *i_cover_score = pi_cover_score[type];
    }

error:
    free( mime );
    free( description );
    return p_attachment;
}