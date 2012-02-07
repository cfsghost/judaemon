#ifndef JD_MODULE_H
#define JD_MODULE_H

JdModule *jd_module_load(const gchar *filename);
JdModule *jd_module_find_from_file(const gchar *module_name);
JdModule *jd_module_find(JuDaemon *judaemon, const gchar *module_name);
void      jd_module_constructor(JdComponent *comp, JsonNode *node);

#endif
