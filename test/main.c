#include "../inc/cpat-llist.h"


#include <stdio.h>



void m_on_entry(cpat_llnode_handler_t *list) {
  printf("ENTERING\n");
}

void m_on_exit(cpat_llnode_handler_t *list) {
  printf("EXITING\n");
}


int main() {
  typedef struct {
    void *next;
    int x;
  } llist_t;


  llist_t x = {.x = 1};
   x.next = &(llist_t) {
    .x = 30,
    .next = &(llist_t) {
      .x = 50
    }
  };


  cpat_llnode_handler_t h = {
    .head = &x,
    .next_offset = offsetof(llist_t, next),
    .on_entry = m_on_entry,
    .on_exit = m_on_exit
  };


  CPAT_LLIST_PREPEND(&h, (llist_t) {.x = 1});
 CPAT_LLIST_PREPEND(&h, (llist_t) {.x = 2});
  CPAT_LLIST_PREPEND(&h, (llist_t) {.x = 3});
   CPAT_LLIST_PREPEND(&h, (llist_t) {.x = 4});


  CPAT_LLIST_ITERATE(&h, iter) {
    llist_t *citer = iter;
    printf("%d\n", citer->x);
  }
}
