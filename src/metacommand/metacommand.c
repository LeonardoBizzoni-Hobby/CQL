#include <stdlib.h>
#include <string.h>

#include "metacommand.h"

Metacommand execute_metacommand(const char *command) {
  if (!strncmp(command, ".exit", 5)) {
    exit(EXIT_SUCCESS);
  } else {
    return METACOMMAND_UNRECOGNIZED;
  }
}
