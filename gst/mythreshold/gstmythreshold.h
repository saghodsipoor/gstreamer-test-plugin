/* GStreamer
 * Copyright (C) <2020> Alireza Ghodsipoor <salirezag@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */


#ifndef __GST_MYTHRESHOLD_H__
#define __GST_MYTHRESHOLD_H__

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/video/gstvideofilter.h>

G_BEGIN_DECLS

#define GST_TYPE_MYTHRESHOLD \
  (gst_mythreshold_get_type())
#define GST_MYTHRESHOLD(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_MYTHRESHOLD,GstMyThreshold))
#define GST_MYTHRESHOLD_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_MYTHRESHOLD,GstMyThresholdClass))
#define GST_IS_MYTHRESHOLD(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_MYTHRESHOLD))
#define GST_IS_MYTHRESHOLD_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_MYTHRESHOLD))

typedef struct _GstMyThreshold GstMyThreshold;
typedef struct _GstMyThresholdClass GstMyThresholdClass;

/**
 * GstMyThreshold:
 *
 * Opaque data structure.
 */
struct _GstMyThreshold
{
  GstVideoFilter videofilter;
  gdouble threshold_value;
};

struct _GstMyThresholdClass
{
  GstVideoFilterClass parent_class;
};

GType gst_mythreshold_get_type(void);

G_END_DECLS

#endif /* __GST_MYTHRESHOLD_H__ */
