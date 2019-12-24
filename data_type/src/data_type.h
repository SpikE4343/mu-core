#ifndef __data_type_INCLUDED__
#define __data_type_INCLUDED__

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "cJSON.h"

// enum ConfigFieldTypes
// {
//   ce_uint8_t,
//   ce_uint16_t,
//   ce_uint32_t,
//   ce_uint64_t,
//   ce_string_t,
//   ce_float_t,
//   ce_double_t,
//   ce_int8_t,
//   ce_int16_t,
//   ce_int32_t,
//   ce_int64_t,
//   ce_SpiConfig_t,
//   ce_GyroConfig_t,
//   ce_WifiConfig_t,
//   ce_
// };

// typedef struct {
//   const char* name;
//   const uint8_t type;
//   const uint16_t offset;
//   const char optional;
// } ConfigField_t;
 

// #define FIELD_COUNT(cl) (sizeof(cl##_fields)/sizeof(ConfigField_t))
// #define FIELD(f) #f

#define name__j(f) f##__j

#define data_get_if_exisits(f) cJSON* name__j(f) = cJSON_GetObjectItem(json, #f); if( name__j(f) != NULL)


#define data_get_number(t, f) { data_get_if_exisits(f){ config->f = (t)(name__j(f))->valuedouble;}}
#define data_get_int(t, f) { data_get_if_exisits(f){ config->f = (t)name__j(f)->valueint; }}
#define data_get_string(f)  { data_get_if_exisits(f){ strncpy(config->f, name__j(f)->valuestring, sizeof(config->f)); }}
#define data_get_vector(t, f) { data_get_if_exisits(f){ t##_FromJson(&(config->f), name__j(f));}}

#define data_set_number(f) cJSON_AddNumberToObject(json, #f, config->f);
#define data_set_string(f) cJSON_AddStringToObject(json, #f, config->f);
#define data_set_vector(t, f) t##_ToJson(&config->f,cJSON_AddArrayToObject(json, #f))

#define data_get_array(t, f, mc) {data_get_if_exisits(f){array_##t##_FromJson(&(config->f), name__j(f), mc);}}
#define data_set_array(t, f, mc) array_##t##_ToJson(&config->f,cJSON_AddArrayToObject(json, #f), mc)


#define data_new_object(t, f) t##_ToJson(&config->f,cJSON_CreateObject());

#define data_set_object(t, f) t##_ToJson(&config->f,cJSON_AddObjectToObject(json, #f))
#define data_get_object(t, f) { data_get_if_exisits(f){ t##_FromJson(&(config->f), name__j(f));}}


// #define BEGIN_CONFIG_DESC(cl, ...)  static ConfigField_t cl##_fields[] = { __VA_ARGS__ };
// #define CONFIG_FIELD(cl, t, f) { #f, ce_##t, offsetof( cl, f) }
// #define END_CONFIG_DESC
// #define CONFIG_DESC

#define data_type_write(t, o, j) t##_ToJson(&o,j);
#define data_type_read(t, o, j) t##_FromJson(&o,j);

#define data_type_read_fromfile(t, o, p) { \
cJSON* t##_json = JsonFromFile(p); \
 if( t##_json != NULL) { \
   t##_FromJson(&o,t##_json); \
   cJSON_Delete(t##_json); \
 } \
} \

#define data_type_read_decl(ct) void ct##_FromJson(ct* config, cJSON* json)
#define data_type_write_decl(ct)  void ct##_ToJson(ct* config, cJSON* json)

#define data_type_read_array_decl(t) void array_##t##_FromJson(t* array, cJSON* json, int max)
#define data_type_write_array_decl(t)  void array_##t##_ToJson(t* array, cJSON* json, int max)


#define data_type(f, t) typedef struct f t; \
data_type_write_decl(t); \
data_type_read_decl(t);

#define data_set_array_of(t, f, c, max)                 \
{                                                       \
  cJSON_AddNumberToObject(json, #c, config->c);         \
  cJSON* array = cJSON_AddArrayToObject(json, #f);      \
  for(int m=0; m < config->c && m < max; ++m)           \
  {                                                     \
    cJSON* item = cJSON_CreateObject();                 \
    t##_ToJson(&config->f[m], item);                    \
    cJSON_AddItemToArray(array, item);                  \
  }                                                     \
}                                                       \

#define data_get_array_of(t, f, c, max)                 \
{                                                       \
  data_get_number(uint8_t, c);                          \
  cJSON* array = cJSON_GetObjectItem(json, #f);         \
  if(array != NULL) {                                   \
    for(int m=0; m < config->c && m < max; ++m)         \
    {                                                   \
      cJSON* item = cJSON_GetArrayItem(array, m);       \
      t##_FromJson(&(config->f[m]), item);              \
    }                                                   \
  }                                                     \
}  


#define data_set_static_array_of(t, f, max)             \
{                                                       \
  cJSON* array = cJSON_AddArrayToObject(json, #f);      \
  for(int m=0; m < max; ++m)                            \
  {                                                     \
    cJSON* item = cJSON_CreateObject();                 \
    t##_ToJson(&config->f[m], item);                    \
    cJSON_AddItemToArray(array, item);                  \
  }                                                     \
}                                                       \

#define data_get_static_array_of(t, f, max)             \
{                                                       \
  cJSON* array = cJSON_GetObjectItem(json, #f);         \
  if(array != NULL) {                                   \
    for(int m=0; m < max; ++m)                          \
    {                                                   \
      cJSON* item = cJSON_GetArrayItem(array, m);       \
      t##_FromJson(&(config->f[m]), item);              \
    }                                                   \
  }                                                     \
}  

// void ConfigFromJson(uint8_t* config, ConfigField_t* fields, int count, cJSON* json);
// void ConfigToJson(uint8_t* config, ConfigField_t* fields, int count, cJSON* json);
// void ConfigFromJsonFile(const char* path, void* config, ConfigField_t* fields, int count);


void JsonToFile(const char* path, cJSON* json);
cJSON* JsonFromFile(const char* path);

data_type_read_array_decl(float);// void array##_ct##_FromJson(ct* config, cJSON* json, int max)
data_type_write_array_decl(float); //  void array_##ct##_ToJson(ct* config, cJSON* json, int max)
data_type_read_array_decl(uint);// void array##_ct##_FromJson(ct* config, cJSON* json, int max)
data_type_write_array_decl(uint); 

#endif