#ifndef JD_CONFIG_H
#define JD_CONFIG_H

#include <glib.h>
#include <json-glib/json-glib.h>

typedef struct _JdConf JdConf;

JdConf  *jd_conf_new();
gboolean  jd_conf_load_from_file(JdConf *conf, const gchar *filename);
gint      jd_conf_count_members(JdConf *conf, JsonNode *node);
GList    *jd_conf_get_members(JdConf *conf, JsonNode *node, GError **error);
GList    *jd_conf_get_nodes(JdConf *conf, JsonNode *node, GError **error);
JsonNode *jd_conf_get_member(JdConf *conf, JsonNode *node, const gchar *key, GError **error);

#endif
