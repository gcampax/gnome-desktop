/* randrwrap.h
 *
 * Copyright 2007, 2008, Red Hat, Inc.
 * 
 * This file is part of the Gnome Library.
 * 
 * The Gnome Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * The Gnome Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * 
 * You should have received a copy of the GNU Library General Public
 * License along with the Gnome Library; see the file COPYING.LIB.  If not,
 * write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * 
 * Author: Soren Sandmann <sandmann@redhat.com>
 */
#ifndef RANDR_WRAP_H
#define RANDR_WRAP_H

#ifndef GNOME_DESKTOP_USE_UNSTABLE_API
#error    GnomeRR is unstable API. You must define GNOME_DESKTOP_USE_UNSTABLE_API before including gnomerr.h
#endif

#include <glib.h>
#include <gdk/gdk.h>

typedef struct GnomeRRScreen GnomeRRScreen;
typedef struct GnomeRROutput GnomeRROutput;
typedef struct GnomeRRCrtc GnomeRRCrtc;
typedef struct GnomeRRMode GnomeRRMode;

typedef void (* GnomeRRScreenChanged) (GnomeRRScreen *screen, gpointer data);

typedef enum
{
    GNOME_RR_ROTATION_0 =	(1 << 0),
    GNOME_RR_ROTATION_90 =	(1 << 1),
    GNOME_RR_ROTATION_180 =	(1 << 2),
    GNOME_RR_ROTATION_270 =	(1 << 3),
    GNOME_RR_REFLECT_X =	(1 << 4),
    GNOME_RR_REFLECT_Y =	(1 << 5)
} GnomeRRRotation;

/* GnomeRRScreen */
GnomeRRScreen * gnome_rr_screen_new                (GdkScreen             *screen,
						    GnomeRRScreenChanged   callback,
						    gpointer               data);
GnomeRROutput **gnome_rr_screen_list_outputs       (GnomeRRScreen         *screen);
GnomeRRCrtc **  gnome_rr_screen_list_crtcs         (GnomeRRScreen         *screen);
GnomeRRMode **  gnome_rr_screen_list_modes         (GnomeRRScreen         *screen);
void            gnome_rr_screen_set_size           (GnomeRRScreen         *screen,
						    int                    width,
						    int                    height,
						    int                    mm_width,
						    int                    mm_height);
GnomeRRCrtc *   gnome_rr_screen_get_crtc_by_id     (GnomeRRScreen         *screen,
						    guint32                id);
gboolean        gnome_rr_screen_refresh            (GnomeRRScreen         *screen);
GnomeRROutput * gnome_rr_screen_get_output_by_id   (GnomeRRScreen         *screen,
						    guint32                id);
GnomeRROutput * gnome_rr_screen_get_output_by_name (GnomeRRScreen         *screen,
						    const char            *name);
void            gnome_rr_screen_get_ranges         (GnomeRRScreen         *screen,
						    int                   *min_width,
						    int                   *max_width,
						    int                   *min_height,
						    int                   *max_height);

/* GnomeRROutput */
guint32         gnome_rr_output_get_id             (GnomeRROutput         *output);
const char *    gnome_rr_output_get_name           (GnomeRROutput         *output);
gboolean        gnome_rr_output_is_connected       (GnomeRROutput         *output);
int             gnome_rr_output_get_size_inches    (GnomeRROutput         *output);
int             gnome_rr_output_get_width_mm       (GnomeRROutput         *outout);
int             gnome_rr_output_get_height_mm      (GnomeRROutput         *output);
const guint8 *  gnome_rr_output_get_edid_data      (GnomeRROutput         *output);
GnomeRRCrtc **  gnome_rr_output_get_possible_crtcs (GnomeRROutput         *output);
GnomeRRMode *   gnome_rr_output_get_current_mode   (GnomeRROutput         *output);
GnomeRRCrtc *   gnome_rr_output_get_crtc           (GnomeRROutput         *output);
void            gnome_rr_output_get_position       (GnomeRROutput         *output,
						    int                   *x,
						    int                   *y);
gboolean        gnome_rr_output_can_clone          (GnomeRROutput         *output,
						    GnomeRROutput         *clone);
GnomeRRMode **  gnome_rr_output_list_modes         (GnomeRROutput         *output);
GnomeRRMode *   gnome_rr_output_get_preferred_mode (GnomeRROutput         *output);
gboolean        gnome_rr_output_supports_mode      (GnomeRROutput         *output,
						    GnomeRRMode           *mode);

/* GnomeRRMode */
guint32         gnome_rr_mode_get_id               (GnomeRRMode           *mode);
guint           gnome_rr_mode_get_width            (GnomeRRMode           *mode);
guint           gnome_rr_mode_get_height           (GnomeRRMode           *mode);
int             gnome_rr_mode_get_freq             (GnomeRRMode           *mode);

/* GnomeRRCrtc */
guint32         gnome_rr_crtc_get_id               (GnomeRRCrtc           *crtc);
gboolean        gnome_rr_crtc_set_config           (GnomeRRCrtc           *crtc,
						    int                    x,
						    int                    y,
						    GnomeRRMode           *mode,
						    GnomeRRRotation        rotation,
						    GnomeRROutput        **outputs,
						    int                    n_outputs);
gboolean        gnome_rr_crtc_can_drive_output     (GnomeRRCrtc           *crtc,
						    GnomeRROutput         *output);
GnomeRRMode *   gnome_rr_crtc_get_current_mode     (GnomeRRCrtc           *crtc);
void            gnome_rr_crtc_get_position         (GnomeRRCrtc           *crtc,
						    int                   *x,
						    int                   *y);
GnomeRRRotation gnome_rr_crtc_get_current_rotation (GnomeRRCrtc           *crtc);
GnomeRRRotation gnome_rr_crtc_get_rotations        (GnomeRRCrtc           *crtc);
gboolean        gnome_rr_crtc_supports_rotation    (GnomeRRCrtc           *crtc,
						    GnomeRRRotation        rotation);

#endif