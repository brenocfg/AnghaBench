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
struct TYPE_7__ {float yaw; float pitch; float roll; float fov; } ;
struct TYPE_8__ {TYPE_1__ pose; int /*<<< orphan*/  projection_mode; } ;
typedef  TYPE_2__ video_format_t ;
typedef  TYPE_3__* jpeg_saved_marker_ptr ;
typedef  TYPE_4__* j_decompress_ptr ;
struct TYPE_10__ {TYPE_3__* marker_list; } ;
struct TYPE_9__ {scalar_t__ marker; int data_length; scalar_t__ data; struct TYPE_9__* next; } ;

/* Variables and functions */
 scalar_t__ EXIF_JPEG_MARKER ; 
 int /*<<< orphan*/  EXIF_XMP_STRING ; 
 int /*<<< orphan*/  PROJECTION_MODE_EQUIRECTANGULAR ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getRDFFloat (char*,float*,char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcmp (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 scalar_t__ strcasestr (char*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jpeg_GetProjection(j_decompress_ptr cinfo, video_format_t *fmt)
{
    jpeg_saved_marker_ptr xmp_marker = NULL;
    jpeg_saved_marker_ptr cmarker = cinfo->marker_list;

    while (cmarker)
    {
        if (cmarker->marker == EXIF_JPEG_MARKER)
        {
            if(cmarker->data_length >= 32 &&
               !memcmp(cmarker->data, EXIF_XMP_STRING, 29))
            {
                xmp_marker = cmarker;
                break;
            }
        }
        cmarker = cmarker->next;
    }

    if (xmp_marker == NULL)
        return;
    char *psz_rdf = malloc(xmp_marker->data_length - 29 + 1);
    if (unlikely(psz_rdf == NULL))
        return;
    memcpy(psz_rdf, xmp_marker->data + 29, xmp_marker->data_length - 29);
    psz_rdf[xmp_marker->data_length - 29] = '\0';

    /* Try to find the string "GSpherical:Spherical" because the v1
        spherical video spec says the tag must be there. */
    if (strcasestr(psz_rdf, "ProjectionType=\"equirectangular\"") ||
        strcasestr(psz_rdf, "ProjectionType>equirectangular"))
        fmt->projection_mode = PROJECTION_MODE_EQUIRECTANGULAR;

    /* pose handling */
    float value;
    if (getRDFFloat(psz_rdf, &value, "PoseHeadingDegrees"))
        fmt->pose.yaw = value;

    if (getRDFFloat(psz_rdf, &value, "PosePitchDegrees"))
        fmt->pose.pitch = value;

    if (getRDFFloat(psz_rdf, &value, "PoseRollDegrees"))
        fmt->pose.roll = value;

    /* initial view */
    if (getRDFFloat(psz_rdf, &value, "InitialViewHeadingDegrees"))
        fmt->pose.yaw = value;

    if (getRDFFloat(psz_rdf, &value, "InitialViewPitchDegrees"))
        fmt->pose.pitch = value;

    if (getRDFFloat(psz_rdf, &value, "InitialViewRollDegrees"))
        fmt->pose.roll = value;

    if (getRDFFloat(psz_rdf, &value, "InitialHorizontalFOVDegrees"))
        fmt->pose.fov = value;

    free(psz_rdf);
}