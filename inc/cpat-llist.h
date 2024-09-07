/**
 * @brief Linked List Pattern
 *
 * @author Antonios Skourtis
 *
 * @date 09/07/2024
 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
//SECTION Types

/**
 * @brief Linked List Pattern
 */
typedef struct cpat_llnode_handler_s cpat_llnode_handler_t;


typedef void (*cpat_llnode_on_access_cb_t)(cpat_llnode_handler_t *list);
typedef void *(*cpat_llnode_on_alloc_cb_t)(cpat_llnode_handler_t *list, size_t sz);
typedef void (*cpat_llnode_on_free_cb_t)(cpat_llnode_handler_t *list, void *node);


struct cpat_llnode_handler_s {
  void *head;
  size_t next_offset;
  cpat_llnode_on_access_cb_t on_entry;
  cpat_llnode_on_access_cb_t on_exit;
  cpat_llnode_on_alloc_cb_t alloc;
  cpat_llnode_on_free_cb_t free;
  void *ctx;
};

//!SECTION


#define CPAT_LLNODE_NEXT(LIST, NODE) (*(void**) ((void*)(NODE) + (LIST)->next_offset))

#define CPAT_LLNODE_CALL(LIST, FNAME) ( (LIST)->FNAME != NULL ? (LIST)->FNAME((LIST)) : 0 )
#define CPAT_LLNODE_ALLOC(LIST, SZ) ( (LIST)->alloc == NULL ? malloc((SZ)) : (LIST)->alloc((LIST), (SZ)) )
#define CPAT_LLNODE_FREE(LIST, P) ( (LIST)->free == NULL ? free((P)) : (LIST)->free((LIST), (P)) )

#define CPAT_LLIST_ITERATE(LIST, ITERSYM) \
  for(void *(ITERSYM) = ( CPAT_LLNODE_CALL((LIST), on_entry), (LIST)->head ); (ITERSYM) == NULL ? ( CPAT_LLNODE_CALL((LIST), on_exit), 0) : ((ITERSYM) == (LIST)->head); (ITERSYM)=NULL) \
    for(; (ITERSYM) != NULL ; (ITERSYM)=CPAT_LLNODE_NEXT((LIST), (ITERSYM)))

#define CPAT_LLIST_PREPEND(LIST, V) cpat_llist_prepend_impl((LIST), &(V), sizeof((V)))



static void cpat_llist_prepend_impl(cpat_llnode_handler_t *list, void const* node, size_t sz)
{
  void *tmp = memcpy(CPAT_LLNODE_ALLOC(list, sz), node, sz);
  CPAT_LLNODE_NEXT(list, tmp) = list->head;
  list->head = tmp;
}
