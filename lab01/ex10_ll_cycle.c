#include <stddef.h>
#include "ex10_ll_cycle.h"

int ll_has_cycle(node *head) {
    /* TODO: Implement ll_has_cycle */
		if (!head)
			goto _EXIT;
			
		node *fast_ptr = head->next ? head->next->next : head->next;
		node *slow_ptr = head->next;

		for (; fast_ptr != NULL && fast_ptr->next != NULL; fast_ptr = fast_ptr->next->next, slow_ptr = slow_ptr->next) {
				if (fast_ptr == slow_ptr)
						return 1;
		}
		_EXIT:
			return 0;
}
