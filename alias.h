/* alias.h */
#ifndef ALIAS_H
#define ALIAS_H

typedef struct Alias {
    char *name;
    char *value;
} Alias;

void list_aliases(Alias aliases[], int alias_count);
int add_alias(Alias aliases[], int alias_count, char *name, char *value);

#endif

