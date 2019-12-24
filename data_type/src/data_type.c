
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#include "data_type.h"
// void ConfigFromJson(uint8_t* config, ConfigField_t* fields, int count, cJSON* json)
// {
//   for(int i=0; i < count; ++i)
//   {
//     ConfigField_t* field = fields+i;
//     cJSON* value = cJSON_GetObjectItem(json, field->name);

//     if( value == NULL)
//       return;

//     switch(value->type)
//     {
//       case cJSON_Number:
      
//         switch(field->type)
//         {
//         case ce_uint8_t:
//           *(config + field->offset) = (uint8_t)value->valueint;        
//           break;

//         case ce_uint16_t:
//           *((uint16_t*)(config + field->offset)) = (uint16_t)value->valueint;
//           break;

//         case ce_uint32_t:
//           *((uint32_t*)(config + field->offset)) = (uint32_t)value->valueint;
//           break;

        

//         case ce_uint64_t:
//           break;

//         case ce_float_t:
//           break;

//         case ce_double_t:
//           break;

//         case ce_int8_t:
//           break;

//         case ce_int16_t:
//           break;

//         case ce_int32_t:
//           break;

//         case ce_int64_t:
//           break;
//         }
//       break;
    
//       case cJSON_String:
//         switch(field->type)
//         {
//         case ce_string_t:
//           *((char**)(config + field->offset)) = value->valuestring;
//           break;
//         }
//         break;

//       default:
//         printf("Invalid json type: %d for field: %s\n", value->type, field->name);
//         return;
//     }
//   }
// }

// void ConfigToJson(uint8_t* config, ConfigField_t* fields, int count, cJSON* json)
// {
//   for(int i=0; i < count; ++i)
//   {
//       ConfigField_t* field = fields+i;
//       double value = 0.0;
//       char* stringValue = NULL;
//       int jsonType = cJSON_Number;

//       switch(field->type)
//       {
//       case ce_uint8_t:
//         value = *((uint8_t*)(config + field->offset));
//         break;

//       case ce_uint16_t:
//         value = *((uint16_t*)(config + field->offset));
//         break;

//       case ce_uint32_t:
//         value = *((uint32_t*)(config + field->offset));
//         break;

//       case ce_uint64_t:
//         value = *((uint64_t*)(config + field->offset));
//         break;

//       case ce_float_t:
//         value = *((float*)(config + field->offset));
//         break;

//       case ce_double_t:
//         value = *((uint8_t*)(config + field->offset));
//         break;
//       case ce_int8_t:
//         value = *((uint8_t*)(config + field->offset));
//         break;
//       case ce_int16_t:
//         value = *((uint8_t*)(config + field->offset));
//         break;
//       case ce_int32_t:
//         value = *((uint8_t*)(config + field->offset));
//         break;
//       case ce_int64_t:
//         value = *((uint8_t*)(config + field->offset));
//         break;
        
//       case ce_string_t:
//         jsonType = cJSON_String;
//         stringValue = *((char**)(config + field->offset));
//         break;
//       }

//       // Create json value
//       switch(jsonType)
//       {
//         case cJSON_Number:
//           cJSON_AddNumberToObject(json, field->name, value);
//           break;

//         case cJSON_String:
//           cJSON_AddStringToObject(json, field->name, stringValue);
//           break;
//       }
//   }
// }

// void ConfigFromJsonFile(const char* path, void* config, ConfigField_t* fields, int count)
// {
//   struct stat st;
//   if (stat(path, &st) != 0)
//     return;

//   FILE* f = fopen(path, "r");
//   if(f == NULL)
//   {
//     printf("Unable to open file:%s\n", path);
//     return;
//   }

//   fseek(f, 0L, SEEK_END);
//   size_t size = ftell(f);
//   rewind(f);

//   char* buffer = malloc(size);
//   size_t read = fread(buffer, sizeof(char), size, f);
//   if(read != size)
//   {
//     printf("Only read: %u bytes from file: %s\n", read, path);
//     fclose(f);
//     return;
//   }

//   fclose(f);

//   cJSON* configJson = cJSON_Parse(buffer);

//   ConfigFromJson(config, fields, count, configJson);  

//   cJSON_Delete(configJson);
//   free(buffer);
// }


void JsonToFile(const char* path, cJSON* json)
{
  FILE* f = fopen(path, "w");
  if(f == NULL)
  {
    printf("Unable to open file:%s\n", path);
    return;
  }

  char *data = cJSON_Print(json);

  int size = strlen(data);
  int written = fwrite(data, sizeof(char), size, f);

  if(size != written)
    printf("Error: unable to write entire string to file\n");
  
  fclose(f);
  cJSON_free(data);
}

cJSON* JsonFromFile(const char* path)
{
  struct stat st;
  if (stat(path, &st) != 0)
  {
    printf("File not found:%s\n", path);
    return NULL;
  }

  FILE* f = fopen(path, "r");
  if(f == NULL)
  {
    printf("Unable to open file:%s\n", path);
    return NULL;
  }

  printf("Opened: %s\n", path);

  fseek(f, 0L, SEEK_END);
  size_t size = ftell(f);
  rewind(f);

  char* buffer = malloc(size+1);
  size_t read = fread(buffer, sizeof(char), size, f);
  if(read != size)
  {
    printf("Only read: %u bytes from file: %s\n", read, path);
    fclose(f);
    return NULL;
  }


  buffer[read] = 0;
  printf("read: %u, of: %u, from: %s\n",read, size, path);

  printf("%s\n\n", buffer);

  fclose(f);

  cJSON* json = cJSON_Parse(buffer);

  if( cJSON_GetErrorPtr() != NULL )
  {
     printf("Error parsing json: %s, from: %s\n",cJSON_GetErrorPtr(), path);
  }

  cJSON_free(buffer);

  return json;
}

data_type_read_array_decl(float)// void array##_ct##_FromJson(ct* config, cJSON* json, int max)
{
  int size = cJSON_GetArraySize(json);
  for( int f=0; f < max && f < size; ++f)
    array[f] = cJSON_GetArrayItem(json, f)->valuedouble;
}

data_type_write_array_decl(float) //  void array_##ct##_ToJson(ct* config, cJSON* json, int max)
{
  for( int f=0; f < max; ++f)
    cJSON_AddItemToArray(json, cJSON_CreateNumber(array[f]));
}

data_type_read_array_decl(uint)// void array##_ct##_FromJson(ct* config, cJSON* json, int max)
{
  int size = cJSON_GetArraySize(json);
  for( int f=0; f < max && f < size; ++f)
    array[f] = (uint)cJSON_GetArrayItem(json, f)->valuedouble;
}

data_type_write_array_decl(uint) //  void array_##ct##_ToJson(ct* config, cJSON* json, int max)
{
  for( int f=0; f < max; ++f)
    cJSON_AddItemToArray(json, cJSON_CreateNumber(array[f]));
}
