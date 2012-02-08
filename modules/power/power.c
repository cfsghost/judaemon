#include <glib.h>
#include <glib/gi18n.h>
#include <X11/Xlib.h>
#include <X11/extensions/dpms.h>
#include <judaemon/module.h>
#include <judaemon/conf.h>
#include <judaemon/component.h>

typedef struct {
	struct {
		CARD16 standby;
		CARD16 suspend;
		CARD16 off;
	} timeout;
} PowerDisplay;

typedef struct {
	JdComponent *component;

	PowerDisplay *display;
} Power;

static void
power_display_init(Power *power)
{
	int event = 0, error = 0;
	BOOL dpms_enabled = False;
	CARD16 power_level = 0;
	
	if (!DPMSQueryExtension(power->component->display, &event, &error)) {
		g_error("XDPMS extension not supported.\n");
		return;
	}

	if (!DPMSCapable(power->component->display)) {
		g_error("DPMS not supported.\n");
		return;
	}

	if (!DPMSInfo(power->component->display, &power_level, &dpms_enabled)) {
		g_error("unable to get DPMS state.\n");
		return;
	}

	if (!dpms_enabled) {
		if (!DPMSEnable(power->component->display)) {
			g_error("unable to set DPMS state\n");
			return;
		}
	}

	if (!DPMSGetTimeouts(power->component->display,
		&power->display->timeout.standby,
		&power->display->timeout.suspend,
		&power->display->timeout.off)) {

		g_error("unable to get DPMS timeouts.\n");
		return;
	}
}

static void
power_display_apply(Power *power)
{
	if (!DPMSSetTimeouts(power->component->display, power->display->timeout.standby, power->display->timeout.suspend, power->display->timeout.off)) {
		g_error("unable to set DPMS timeouts.\n");
	}
}

static void
power_read_group_settings(Power *power, JsonNode *node, const gchar *group_name)
{
	JsonObject *object;

	object = json_node_get_object(node);

	if (strcmp(group_name, "display") == 0) {
		power->display->timeout.standby = 0;
		power->display->timeout.suspend = 0;
		power->display->timeout.off = json_object_get_int_member(object, "timeout");

		/* Apply settings */
		power_display_apply(power);
	}
}

static void
power_constructor(JdComponent *comp, JsonNode *node)
{
	Power *power;
	JsonObject *object;
	JsonNode *group_node;
	gchar *group_name;
	GList *members = NULL;
	GList *listnode = NULL;

	/* Create private structure */
	power = g_slice_new0(Power);
	power->component = comp;
	power->display = g_slice_new0(PowerDisplay);

	if (node) {
		/* Read Settings from config file */
		object = json_node_get_object(node);

		members = json_object_get_members(object);
		for (listnode = members; listnode; listnode = g_list_next(listnode)) {
			group_name = (gchar *)listnode->data;

			group_node = json_object_get_member(object, group_name);

			power_read_group_settings(power, group_node, group_name);
		}
	}

	comp->priv = (gpointer)power;

	/* Initializing DPMS */
	power_display_init(power);
}

JdModuleClass module_class = {
	name: "power",
	version: "1.0",
	description: N_("Power Management"),

	constructor: power_constructor
};
