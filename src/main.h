#define REALLOC_CHECK(str, capacity)                                           \
  if (!(str = realloc(str, capacity * sizeof(char)))) {                        \
    fprintf(stderr, "Memory allocation for CQL command failed.");              \
    free(str);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  }

char *read_command();
