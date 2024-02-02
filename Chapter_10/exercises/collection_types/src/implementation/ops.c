#include "../include/collection.h" // include public interface

/* Herein lie the definitions of structures 
 We could've gotten away with defining them here in this file,
 But for the sake of adhering the book's word, we shall
 Make another header for the internal purposes of the implementation */

#include "./include/internal_collection.h" // include interface available only to implementation

unsigned char debug = 1;

#include "./debug/debug.h"
#include <string.h>

void start_collection(void)
{
	collection_type *head = NULL;
	char arr[] = "Random data";

	PRINT_DBG("[%s:%s:%d] Debugging!\n", __FILE__, __FUNCTION__, __LINE__);

	if (-1 == create_collection(&head)) {
		return;
	}

	for (int i = 0; i < 100; i++) {
		if (i == 100) {
			head->add_to_collection(head, (void *) "Alpha", strlen("Alpha") + 1);				
		} else if (i == 55) {
			head->add_to_collection(head, (void *) "Beta", strlen("Beta") + 1);
		} else if (i == 31) {
			head->add_to_collection(head, (void *) "Gamma", strlen("Gamma") + 1);
		} else {
			head->add_to_collection(head, (void *) arr, sizeof(arr));
		}
	}

	if (!head->find_in_collection(head, (const void *) arr, sizeof(arr))) {
		PRINT_DBG("%s", "Couldn't find the requested data in collection.\n");
	}

	if (!head->remove_from_collection(head, (const void *) "Gamma", strlen("Gamma") + 1))  {
		PRINT_DBG("%s", "Couldn't remove the requested data in collection.\n");
	}

	if (!head->remove_from_collection(head, (const void *) arr, sizeof(arr))) {
		PRINT_DBG("%s", "Couldn't remove the requested data in collection.\n");
	}

	if (!head->remove_from_collection(head, (const void *) "Alpha", strlen("Alpha") + 1)) {
		PRINT_DBG("%s", "Couldn't remove the requested data in collection.\n");
	}

	if (!head->remove_from_collection(head, (const void *) "Beta", strlen("Beta") + 1)) {
		PRINT_DBG("%s", "Couldn't remove the requested data in collection.\n");
	}


	head->destroy_collection(head);
	head = NULL;
}

int create_collection(collection_type **result)
{
	PRINT_DBG("[%s:%s:%d] Debugging!\n", __FILE__, __FUNCTION__, __LINE__);
	if (*result == NULL) {
		*result = malloc(sizeof(collection_type));
		if (*result == NULL) {
			return  -1;
		}
	} else {
		PRINT_DBG("%s",
			"Collection already exists.\n"
			"Provide null pointer or destroy the current collection.\n"
				);
		return -1;
	}
	PRINT_DBG("[%s:%s:%d] Debugging!\n", __FILE__, __FUNCTION__, __LINE__);

	(*result)->destroy_collection = &destroy_collection;
	(*result)->find_in_collection = &find_in_collection;
	(*result)->add_to_collection = &add_to_collection;
	(*result)->remove_from_collection = &remove_from_collection;
	(*result)->listp = calloc(1, sizeof(struct list));
	if ((*result)->listp == NULL) {
		return -1;
	}

	PRINT_DBG("%s", "Collection has been created.\n");

	return 0;
}

void destroy_collection(collection_type *col)
{
	for (struct node_type *tmp_head = col->listp->head, *tmp = NULL; tmp_head != NULL; tmp_head = tmp) {
		free(tmp_head->data);
		tmp = tmp_head->next;
		free(tmp_head);
	}
	free(col->listp);
	free(col);
}

void add_to_collection(collection_type *col, const void *data, size_t byteCount)
{
		struct node_type *tmp_head = NULL;

		for (tmp_head = col->listp->head; tmp_head != NULL; tmp_head = tmp_head->next)
			;

		tmp_head = calloc(1, sizeof(struct node_type));
		if (tmp_head == NULL) {
			return;
		}

		tmp_head->data = calloc(1, byteCount);
		memcpy(tmp_head->data, data, byteCount);
		tmp_head->size = byteCount;

		tmp_head->next = col->listp->head;
		col->listp->head = tmp_head;
		col->listp->num_elements++;
		PRINT_DBG(
			"Added to collection!\n"
			"Num of elements total = %zu\n", 
			col->listp->num_elements
		);
}

int remove_from_collection(collection_type *col, const void *data, size_t byteCount)
{
	int ret = 0;

	for (struct node_type *tmp_head = col->listp->head, *prev = tmp_head; tmp_head != NULL; prev = tmp_head, tmp_head = tmp_head->next) {
		if (!memcmp(tmp_head->data, data, byteCount)) {
			PRINT_DBG("%s", "Removing from collection!\n");
			if (tmp_head == prev) {
				PRINT_DBG("%s", "Removing from at the beginning!\n");
				col->listp->head = tmp_head->next;
			} else if (tmp_head->next == NULL) {
				PRINT_DBG("%s", "Removing from at the end!\n");
				prev->next = NULL;
			} else {
				PRINT_DBG("%s", "Removing from in the middle!\n");
				prev->next = tmp_head->next;
			}
			free(tmp_head->data);
			tmp_head->data = NULL;
			free(tmp_head);
			tmp_head = NULL;
			PRINT_DBG("%s", "Removed from collection!\n");
			ret = 1;
			break;
		}
	}

	return ret;
}

int find_in_collection(const collection_type *col, const void *data, size_t byteCount)
{
	int ret = 0;
	for (struct node_type *tmp_head = col->listp->head; tmp_head != NULL; tmp_head = tmp_head->next) {
		if (!memcmp(tmp_head->data, data, byteCount)) {
			PRINT_DBG(
				"Found record in collection:\n"
				"node = %p\n"
				"node->data=%p\n"
				"node->size=%zu\n"
				"node->next=%p\n",
				(void *) tmp_head,
				(void *) tmp_head->data,
				tmp_head->size,
				(void *) tmp_head->next
			);
			ret = 1;
			break;
		}
	}

	return ret;
}
