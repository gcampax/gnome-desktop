/* -*- mode: C; c-file-style: "linux"; indent-tabs-mode: t -*-
 *
 * Adapted from gnome-session/gnome-session/gs-idle-monitor.h
 *
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Authors: William Jon McCann <mccann@jhu.edu>
 */

#ifndef __GNOME_IDLE_MONITOR_H__
#define __GNOME_IDLE_MONITOR_H__

#ifndef GNOME_DESKTOP_USE_UNSTABLE_API
#error    This is unstable API. You must define GNOME_DESKTOP_USE_UNSTABLE_API before including gnome-idle-monitor.h
#endif

#include <glib-object.h>

G_BEGIN_DECLS

#define GNOME_TYPE_IDLE_MONITOR         (gnome_idle_monitor_get_type ())
#define GNOME_IDLE_MONITOR(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), GNOME_TYPE_IDLE_MONITOR, GnomeIdleMonitor))
#define GNOME_IDLE_MONITOR_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), GNOME_TYPE_IDLE_MONITOR, GnomeIdleMonitorClass))
#define GNOME_IS_IDLE_MONITOR(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GNOME_TYPE_IDLE_MONITOR))
#define GNOME_IS_IDLE_MONITOR_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), GNOME_TYPE_IDLE_MONITOR))
#define GNOME_IDLE_MONITOR_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), GNOME_TYPE_IDLE_MONITOR, GnomeIdleMonitorClass))

typedef struct GnomeIdleMonitorPrivate GnomeIdleMonitorPrivate;

typedef struct
{
        GObject                  parent;
        GnomeIdleMonitorPrivate *priv;
} GnomeIdleMonitor;

typedef struct
{
        GObjectClass          parent_class;
} GnomeIdleMonitorClass;

typedef void (*GnomeIdleMonitorWatchFunc) (GnomeIdleMonitor      *monitor,
                                           guint                  id,
                                           gpointer               user_data);

GType              gnome_idle_monitor_get_type     (void);

GnomeIdleMonitor * gnome_idle_monitor_new          (void);
GnomeIdleMonitor * gnome_idle_monitor_new_for_device (GdkDevice *device);

void               gnome_idle_monitor_add_watch    (GnomeIdleMonitor         *monitor,
                                                    guint                     interval,
                                                    GnomeIdleMonitorWatchFunc callback,
                                                    gpointer                  user_data,
                                                    GDestroyNotify            notify,
	                                            guint                    *watch_id);

void               gnome_idle_monitor_remove_watch (GnomeIdleMonitor         *monitor,
                                                    guint                     id);

gint64             gnome_idle_monitor_get_idletime (GnomeIdleMonitor         *monitor);

G_END_DECLS

#endif /* __GNOME_IDLE_MONITOR_H__ */