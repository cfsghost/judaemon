#include <glib.h>
#include <glib/gi18n.h>
#include <judaemon/module.h>
#include <judaemon/conf.h>
#include <judaemon/component.h>

typedef struct {
} Power;

static void
power_constructor(JdComponent *comp, JsonNode *node)
{
	Power *power;
	JsonObject *object;

	g_print("TEST\n");

	/* Create private structure */
	power = g_slice_new0(Power);

	if (node) {
		/* Read Settings from config file */
		object = json_node_get_object(node);
	}

	comp->priv = (gpointer)power;
}

JdModuleClass module_class = {
	name: "power",
	version: "1.0",
	description: N_("Power Management"),

	constructor: power_constructor
};
