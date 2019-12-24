#include "vector.h"
#include <assert.h>

data_type_write_decl(Vector4f_t)
{
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[0]));
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[1]));
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[2]));
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[3]));
}

data_type_read_decl(Vector4f_t)
{
  assert(cJSON_GetArraySize(json) == 4);
  config->axis[0] = cJSON_GetArrayItem(json, 0)->valuedouble;
  config->axis[1] = cJSON_GetArrayItem(json, 1)->valuedouble;
  config->axis[2] = cJSON_GetArrayItem(json, 2)->valuedouble;
  config->axis[3] = cJSON_GetArrayItem(json, 3)->valuedouble;
}

data_type_write_decl(Vector3f_t)
{
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[0]));
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[1]));
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[2]));
}

data_type_read_decl(Vector3f_t)
{
  assert(cJSON_GetArraySize(json) == 3);
  config->axis[0] = cJSON_GetArrayItem(json, 0)->valuedouble;
  config->axis[1] = cJSON_GetArrayItem(json, 1)->valuedouble;
  config->axis[2] = cJSON_GetArrayItem(json, 2)->valuedouble;
}

data_type_write_decl(Vector4u16_t)
{
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[0]));
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[1]));
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[2]));
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[2]));
}

data_type_read_decl(Vector4u16_t)
{
  assert(cJSON_GetArraySize(json) == 4);
  config->axis[0] = cJSON_GetArrayItem(json, 0)->valuedouble;
  config->axis[1] = cJSON_GetArrayItem(json, 1)->valuedouble;
  config->axis[2] = cJSON_GetArrayItem(json, 2)->valuedouble;
  config->axis[3] = cJSON_GetArrayItem(json, 3)->valuedouble;
}

data_type_write_decl(Vector3u16_t)
{
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[0]));
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[1]));
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[2]));
}

data_type_read_decl(Vector3u16_t)
{
  assert(cJSON_GetArraySize(json) == 3);
  config->axis[0] = cJSON_GetArrayItem(json, 0)->valuedouble;
  config->axis[1] = cJSON_GetArrayItem(json, 1)->valuedouble;
  config->axis[2] = cJSON_GetArrayItem(json, 2)->valuedouble;
}

data_type_write_decl(Vector3i16_t)
{
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[0]));
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[1]));
  cJSON_AddItemToArray(json, cJSON_CreateNumber((double)config->axis[2]));
}

data_type_read_decl(Vector3i16_t)
{
  assert(cJSON_GetArraySize(json) == 3);
  config->axis[0] = cJSON_GetArrayItem(json, 0)->valuedouble;
  config->axis[1] = cJSON_GetArrayItem(json, 1)->valuedouble;
  config->axis[2] = cJSON_GetArrayItem(json, 2)->valuedouble;
}