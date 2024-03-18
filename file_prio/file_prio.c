#include "file_prio.h"
#include <stdlib.h>

file_prio* file_prio_create(int max_size){
  couple* ptr = malloc(sizeof(couple)*max_size);
  file_prio* ptr2 = malloc(sizeof(file_prio));
  ptr2->curr_siz=0;
  ptr2->max_siz=max_size;
  ptr2->data=ptr;
  return ptr2;
}
void file_prio_realoc(file_prio* file,int new_max_size){
  file->data =  realloc(file->data,sizeof(couple)*new_max_size);
  file->max_siz=new_max_size;
}
int parent(int index){return (index-1)/2;}
int fils_g(int index){return (index*2+1);}
int fils_d(int index){return (index*2+2);}
void file_prio_insert(file_prio *file,couple elem){
  if (file->curr_siz==file->max_siz) file_prio_realoc(file, file->max_siz*2);
  int index = file->curr_siz;
  while (index != 0 && file->data[parent(index)].cle>elem.cle){
    file->data[index]=file->data[parent(index)];
    index = parent(index);
  }
  file->data[index]=elem;
  file->curr_siz+=1;
}
couple file_prio_get(file_prio *file){
  couple to_return = file->data[0];
  file->curr_siz-=1;
  couple bouge=file->data[file->curr_siz];
  int index=0;
  while (index!=-1){
    if (fils_g(index)>=file->curr_siz || (fils_d(index)>=file->curr_siz && bouge.cle<=file->data[fils_g(index)].cle) ||
         (bouge.cle<=file->data[fils_g(index)].cle && bouge.cle<=file->data[fils_d(index)].cle)  ){
      //we reached end of tree or next elem(s) are superior already
      file->data[index]=bouge;
      index = -1;
    }
    else {
      if (fils_d(index)>=file->curr_siz) {
        //near end of tree (there is a inferior left, but no right)
        file->data[index]=file->data[fils_g(index)];
        file->data[fils_g(index)]=bouge;
        index = -1;
      } else {
        // one of the two son is inferior
        if (file->data[fils_g(index)].cle < file->data[fils_d(index)].cle){
          file->data[index]=file->data[fils_g(index)];
          index=fils_g(index);
        } else {
          file->data[index]=file->data[fils_d(index)];
          index=fils_d(index);
        }
      }
    }
  }
  return to_return;
}
bool file_prio_est_vide(file_prio *file){return file->curr_siz==0;}
void file_prio_delete(file_prio *file){
  free(file->data);
  free(file);
}
