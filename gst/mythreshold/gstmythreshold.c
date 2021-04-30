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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gstmythreshold.h"
#include <string.h>

G_DEFINE_TYPE (GstMyThreshold, gst_mythreshold, GST_TYPE_VIDEO_FILTER);

GST_DEBUG_CATEGORY_STATIC (mythreshold_debug);
#define GST_CAT_DEFAULT mythreshold_debug

/* GstMyThreshold properties */
enum
{
  PROP_0,
  PROP_THRESHOLD
      /* FILL ME */
};

#define DEFAULT_PROP_THRESHOLD  0.5

static GstStaticPadTemplate gst_mythreshold_src_template =
GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS (GST_VIDEO_CAPS_MAKE ("{ AYUV, "
            "ARGB, BGRA, ABGR, RGBA, Y444, "
            "xRGB, RGBx, xBGR, BGRx, RGB, BGR, Y42B, NV12, "
            "NV21, YUY2, UYVY, YVYU, I420, YV12, IYUV, Y41B }"))
    );

static GstStaticPadTemplate gst_mythreshold_sink_template =
GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS (GST_VIDEO_CAPS_MAKE ("{ AYUV, "
            "ARGB, BGRA, ABGR, RGBA, Y444, "
            "xRGB, RGBx, xBGR, BGRx, RGB, BGR, Y42B, NV12, "
            "NV21, YUY2, UYVY, YVYU, I420, YV12, IYUV, Y41B }"))
    );

static void gst_mythreshold_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_mythreshold_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);

static GstFlowReturn gst_mythreshold_transform_frame_ip (GstVideoFilter * vfilter,
    GstVideoFrame * frame);

static void
gst_mythreshold_class_init (GstMyThresholdClass * g_class)
{
  GObjectClass *gobject_class = (GObjectClass *) g_class;
  GstElementClass *gstelement_class = (GstElementClass *) g_class;
  // GstBaseTransformClass *trans_class = (GstBaseTransformClass *) g_class;
  GstVideoFilterClass *vfilter_class = (GstVideoFilterClass *) g_class;

  GST_DEBUG_CATEGORY_INIT (mythreshold_debug, "threshold", 0, "threshold");

  gobject_class->set_property = gst_mythreshold_set_property;
  gobject_class->get_property = gst_mythreshold_get_property;

  g_object_class_install_property (gobject_class, PROP_THRESHOLD,
      g_param_spec_double ("threshold", "Threshold", "threshold value",
          0.0, 1.0, DEFAULT_PROP_THRESHOLD,
          GST_PARAM_CONTROLLABLE | G_PARAM_STATIC_STRINGS | G_PARAM_READWRITE));

  gst_element_class_set_static_metadata (gstelement_class,
      "Threshold effect", "Filter/Effect/Video",
      "Applies threshold effect on a video stream", "Alireza Ghodsipoor <salirezag@gmail.com>");

  gst_element_class_add_static_pad_template (gstelement_class,
      &gst_mythreshold_sink_template);
  gst_element_class_add_static_pad_template (gstelement_class,
      &gst_mythreshold_src_template);

  vfilter_class->transform_frame_ip =
      GST_DEBUG_FUNCPTR (gst_mythreshold_transform_frame_ip);
}

static void
gst_mythreshold_init (GstMyThreshold * gamma)
{
}

static void
gst_mythreshold_set_property (GObject * object, guint prop_id, const GValue * value,
    GParamSpec * pspec)
{
  GstMyThreshold *mythreshold = GST_MYTHRESHOLD (object);

  switch (prop_id) {
    case PROP_THRESHOLD:{
      mythreshold->threshold_value = g_value_get_double (value);
      break;
    }
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_mythreshold_get_property (GObject * object, guint prop_id, GValue * value,
    GParamSpec * pspec)
{
  GstMyThreshold *mythreshold = GST_MYTHRESHOLD (object);

  switch (prop_id) {
    case PROP_THRESHOLD:
      g_value_set_double (value, mythreshold->threshold_value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static GstFlowReturn
gst_mythreshold_transform_frame_ip (GstVideoFilter * vfilter, GstVideoFrame * frame)
{
  GstMyThreshold *mythreshold = GST_MYTHRESHOLD (vfilter);

  gint width  = GST_VIDEO_FRAME_COMP_WIDTH (frame, 0);
  gint height = GST_VIDEO_FRAME_COMP_HEIGHT (frame, 0);
  gint stride = GST_VIDEO_FRAME_PLANE_STRIDE (frame, 0);

  guint8 *data;
  data = GST_VIDEO_FRAME_PLANE_DATA (frame, 0);
  
  gint x, y;

  guint8 thresh = mythreshold->threshold_value * 256;

  for (y = 0; y < height; y++)
    for (x = 0; x < width; x++)
    {
      guint8 *d = data + y * stride + x;
      *d = *d > thresh ? 0 : 256;
    }
    // {
    //   guint offset = y * stride + x;
    //   guint8 *d = data[0] + offset;
    //   *d = *d > thresh ? 0 : 256;
    //   *(data[1] + offset) = 0;
    //   *(data[2] + offset) = 0;
    // } 

  return GST_FLOW_OK;
}
