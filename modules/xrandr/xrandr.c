#include <glib.h>
#include <glib/gi18n.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <judaemon/module.h>
#include <judaemon/conf.h>
#include <judaemon/component.h>

typedef struct {
	JdComponent *component;

	gint rr_major_version;
	gint rr_minor_version;
	gint xrandr_event_base;
	gint xrandr_error_base;
} XRandR;

static void
xrandr_notify(XRandR *xrandr, XRRNotifyEvent *ne)
{
	switch(ne->subtype) {
	case RRNotify_OutputChange:
		g_print("Got Subevent RRNotify_OutputChange\n");
		break;
	case RRNotify_OutputProperty:
		g_print("Got Subevent RRNotify_OutputProperty\n");
		break;
	case RRNotify_CrtcChange:
		g_print("Got Subevent RRCrtcChangeNotify\n");
		break;
	}
}

static void
xrandr_constructor(JdComponent *comp, JsonNode *node)
{
	XRandR *xrandr;
	JsonObject *object;
	JsonNode *group_node;
	gchar *group_name;
	GList *members = NULL;
	GList *listnode = NULL;

	/* Create private structure */
	xrandr = g_slice_new0(XRandR);
	xrandr->component = comp;

	if (node) {
		/* Read Settings from config file */
		object = json_node_get_object(node);
/*
		members = json_object_get_members(object);
		for (listnode = members; listnode; listnode = g_list_next(listnode)) {
			group_name = (gchar *)listnode->data;

			group_node = json_object_get_member(object, group_name);

			xrandr_read_group_settings(power, group_node, group_name);
		}
*/
	}

	comp->priv = (gpointer)xrandr;

	/* Initializing XRandr extension */
	XRRQueryVersion(comp->display, &xrandr->rr_major_version, &xrandr->rr_minor_version);
	if (xrandr->rr_major_version < 1 || (xrandr->rr_major_version == 1 && xrandr->rr_minor_version < 2)) {
		g_print("RANDR extension is too old (must be at least 1.2)\n");
		return;
	}

	XRRSelectInput(comp->display, DefaultRootWindow(comp->display), RROutputChangeNotifyMask | RRScreenChangeNotifyMask);
	XRRQueryExtension(comp->display, &xrandr->xrandr_event_base, &xrandr->xrandr_error_base);
}

static void
xrandr_xevent_handler(JdComponent *comp, XEvent *ev)
{
	XRandR *xrandr = comp->priv;
	XRRScreenChangeNotifyEvent *sce;
	XRRNotifyEvent *ne;

	/* XRandr Extension Event */
	switch(ev->type - xrandr->xrandr_event_base) {
	case RRNotify:
		g_print("Got RRNotify\n");
		xrandr_notify(xrandr, (XRRNotifyEvent *)ev);
		break;
	case RRScreenChangeNotify:
		sce = (XRRScreenChangeNotifyEvent *)ev;

		g_print("Got RRScreenChangeNotify, %d x %d\n", sce->width, sce->height);
		break;
	}

}

JdModuleClass module_class = {
	name: "xrandr",
	version: "1.0",
	description: N_("XRandR Management"),

	constructor: xrandr_constructor,
	xevent_handler: xrandr_xevent_handler
};
