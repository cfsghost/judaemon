#include <stdlib.h>
#include <glib.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <sys/stat.h>
#include <judaemon/conf.h>
#include "judaemon.h"
#include "conf.h"

JdConf *
jd_conf_new()
{
	JdConf *conf;

	conf = (JdConf *)g_slice_new0(JdConf);
	conf->parser = json_parser_new();

	return conf;
}

gboolean
jd_conf_load_from_file(JdConf *conf, const gchar *filename)
{
	GError *error = NULL;

	DEBUG("Loading config file: %s\n", filename);
	if (!json_parser_load_from_file(conf->parser, filename, &error)) {
		g_error("Unable to read file\n%s\n", error->message);
		return FALSE;
	}

	DEBUG("Parsing config file\n", filename);
	conf->root = json_parser_get_root(conf->parser);

	return TRUE;
}

gint
jd_conf_count_members(JdConf *conf, JsonNode *node)
{
	JsonObject *object;

	/* We consider it is a object */
	if (node)
		object = json_node_get_object(node);
	else
		object = json_node_get_object(conf->root);

	return json_object_get_size(object);
}

GList *
jd_conf_get_members(JdConf *conf, JsonNode *node, GError **error)
{
	JsonObject *object;

	/* We consider it is a object */
	if (node)
		object = json_node_get_object(node);
	else
		object = json_node_get_object(conf->root);

	return json_object_get_members(object);
}

GList *
jd_conf_get_nodes(JdConf *conf, JsonNode *node, GError **error)
{
	JsonObject *object;

	/* We consider it is a object */
	if (node)
		object = json_node_get_object(node);
	else
		object = json_node_get_object(conf->root);

	return json_object_get_values(object);
}

JsonNode *
jd_conf_get_member(JdConf *conf, JsonNode *node, const gchar *key, GError **error)
{
	JsonObject *object;

	/* We consider it is a object */
	if (node)
		object = json_node_get_object(node);
	else
		object = json_node_get_object(conf->root);

	return json_object_get_member(object, key);
}
