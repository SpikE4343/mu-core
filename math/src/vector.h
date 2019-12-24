
#ifndef __vector_h_included__
#define __vector_h_included__

#include <stdint.h>
#include "data_type.h"

typedef union {
  struct
  {
    float roll;
    float pitch;
    float yaw;
    float throttle;
  };

  struct
  {
    float x;
    float y;
    float z;
    float w;
  };
  float axis[4];
} Vector4f_t;

typedef union {
  struct
  {
    uint16_t roll;
    uint16_t pitch;
    uint16_t yaw;
    uint16_t throttle;
  };

  struct
  {
    uint16_t x;
    uint16_t y;
    uint16_t z;
    uint16_t w;
  };
  uint16_t axis[4];
} Vector4u16_t;

typedef union {
  struct
  {
    float roll;
    float pitch;
    float yaw;
  };

  struct
  {
    float x;
    float y;
    float z;
  };

  float axis[3];
} Vector3f_t;

typedef union {
  struct
  {
    uint16_t roll;
    uint16_t pitch;
    uint16_t yaw;
  };

  struct
  {
    uint16_t x;
    uint16_t y;
    uint16_t z;
  };

  uint16_t axis[3];
} Vector3u16_t;

typedef union {
  struct
  {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
  };

  struct
  {
    int16_t x;
    int16_t y;
    int16_t z;
  };

  int16_t axis[3];
} Vector3i16_t;

data_type_write_decl(Vector4f_t);
data_type_read_decl(Vector4f_t);

data_type_write_decl(Vector3f_t);
data_type_read_decl(Vector3f_t);

data_type_write_decl(Vector4u16_t);
data_type_read_decl(Vector4u16_t);

data_type_write_decl(Vector3u16_t);
data_type_read_decl(Vector3u16_t);

data_type_write_decl(Vector3i16_t);
data_type_read_decl(Vector3i16_t);

#endif