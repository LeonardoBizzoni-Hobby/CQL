#ifndef CQL_METACOMMAND_H
#define CQL_METACOMMAND_H

typedef enum {
  METACOMMAND_SUCCESS,
  METACOMMAND_UNRECOGNIZED,
} Metacommand;

Metacommand execute_metacommand(const char *);

#endif
