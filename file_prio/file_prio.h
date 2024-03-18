#ifndef FILE_PRIO_H
#define FILE_PRIO_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct couple {
  int cle;
  void* val;
} couple;

typedef struct file_prio {
  int curr_siz;
  int max_siz;
  couple* data;
} file_prio;

//renvoie une nouvelle file prio
file_prio* file_prio_create(int max_size);
void file_prio_insert(file_prio *file,couple elem);
couple file_prio_get(file_prio *file);
bool file_prio_est_vide(file_prio *file);
void file_prio_delete(file_prio *file);

#endif //FILE_PRIO_H
