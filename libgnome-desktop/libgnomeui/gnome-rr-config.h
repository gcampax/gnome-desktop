/* gnome-rr-config.h
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
#ifndef GNOME_RR_CONFIG_H
#define GNOME_RR_CONFIG_H

#ifndef GNOME_DESKTOP_USE_UNSTABLE_API
#error   gnome-rr-config.h is unstable API. You must define GNOME_DESKTOP_USE_UNSTABLE_API before including gnome-rr-config.h
#endif

#include <libgnomeui/gnome-rr.h>
#include <glib.h>

typedef struct GnomeOutputInfo GnomeOutputInfo;
typedef struct GnomeRRConfig GnomeRRConfig;

struct GnomeOutputInfo
{
    char *		name;

    gboolean		on;
    int			width;
    int			height;
    int			rate;
    int			x;
    int			y;
    GnomeRRRotation	rotation;

    gboolean		connected;
    char		vendor[4];
    guint		product;
    guint		serial;
    double		aspect;
    int			pref_width;
    int			pref_height;
    char *		display_name;

    gpointer		user_data;
};

struct GnomeRRConfig
{
    gboolean		clone;
    
    GnomeOutputInfo **	outputs;
};

GnomeRRConfig  *gnome_rr_config_new_current  (GnomeRRScreen  *screen);
void            gnome_rr_config_free         (GnomeRRConfig  *configuration);
gboolean        gnome_rr_config_match        (GnomeRRConfig  *config1,
					      GnomeRRConfig  *config2);
gboolean        gnome_rr_config_save         (GnomeRRConfig  *configuration,
					      GError        **err);
void            gnome_rr_config_sanitize     (GnomeRRConfig  *configuration);
gboolean        gnome_rr_config_apply_stored (GnomeRRScreen  *screen);
gboolean        gnome_rr_config_applicable   (GnomeRRConfig  *configuration,
					      GnomeRRScreen  *screen);

#endif