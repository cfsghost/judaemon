#ifndef INTERNAL_JD_COMPONENT_H
#define INTERNAL_JD_COMPONENT_H

JdComponent *jd_component_new(JuDaemon *judaemon, const gchar *module_name);
void       jd_component_init(JuDaemon *judaemon, JdComponent *comp, JsonNode *node);

#endif
