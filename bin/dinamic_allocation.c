/**
 * @file dinamic_allocation.cpp
 *
 * @version 01.01 2020-08-15
 *
 * @brief Test an easy dinamic allocation in c
 *
 * @ingroup dinamic_allocation
 * (Note: this needs exactly one @defgroup somewhere)
 *
 * @author Castellani Davide
 *
 * Contact: contacts@castellanidavide.it
 *
 */
#include <stdio.h>
#include <stdlib.h>

// Structure
struct listNode
{
	char data;
	struct listNode *nextPtr;
};

// Typedef
typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

// Prototypes
void insert(ListNodePtr *sPtr, char value);
char delete (ListNodePtr *sPtr, char value);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);
void istructions(void);

int main()
{
	ListNodePtr startPtr = NULL;
	unsigned int choise;
	char item;

	istructions(); // Print istructions
	printf("%s", "The number you want is: ");
	scanf("%u", &choise);

	while (choise != 3)
	{
		switch (choise)
		{
		case 1:
			printf("%s", "Enter a character: ");
			scanf("\n%c", &item);
			insert(&startPtr, item);
			printList(startPtr);
			break;

		case 2:
			if (!isEmpty(startPtr))
			{
				printf("%s", "Enter the char you want to delate: ");
				scanf("\n%c", &item);

				if (delete (&startPtr, item))
				{
					printf("%c delated\n", item);
					printList(startPtr);
				}
				else
				{
					printf("%c is not in the dynamic list\n", item);
				}
			}
			else
			{
				puts("The dynamic list is empty, please, insert an element before delate it.");
			}
			break;

		default:
			puts("Invalid choise");
			istructions();
			break;
		}

		printf("%s", "The number you want is: ");
		scanf("%u", &choise);
	}

	return 0;
}

void insert(ListNodePtr *sPtr, char value)
{
	ListNodePtr newPtr = malloc(sizeof(ListNode));
	if (newPtr != NULL)
	{
		newPtr->data = value;
		newPtr->nextPtr = NULL;

		ListNodePtr previousPtr = NULL;
		ListNodePtr currentPtr = *sPtr;

		// Find the correct position
		while (currentPtr != NULL && value > currentPtr->data)
		{
			// Go to the next element
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}

		if (previousPtr == NULL)
		{
			// First element
			newPtr->nextPtr = *sPtr;
			*sPtr = newPtr;
		}
		else
		{
			// Not the first
			previousPtr->nextPtr = newPtr;
			newPtr->nextPtr = currentPtr;
		}
		printf("%c added\n", value);
	}
	else
	{
		printf("%s", "Error the char was not salved");
	}
}

char delete (ListNodePtr *sPtr, char value)
{
	if (value == (*sPtr)->data)
	{
		ListNodePtr tempPtr = *sPtr;
		*sPtr = (*sPtr)->nextPtr;
		free(tempPtr);
		return value;
	}
	else
	{
		ListNodePtr previousPtr = *sPtr;
		ListNodePtr currentPtr = (*sPtr)->nextPtr;

		// Find the element
		while (currentPtr != NULL && currentPtr->data != value)
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}

		if (currentPtr != NULL)
		{
			ListNodePtr tempPtr = currentPtr;
			previousPtr->nextPtr = currentPtr->nextPtr;
			free(tempPtr);
			return value;
		}
	}

	return '\0';
}

int isEmpty(ListNodePtr sPtr)
{
	return sPtr == NULL;
}

void printList(ListNodePtr currentPtr)
{
	if (isEmpty(currentPtr))
	{
		puts("The list is empty");
	}
	else
	{
		puts("The list is:");

		// Scan every element
		while (currentPtr != NULL)
		{
			printf("%c ---> ", currentPtr->data);
			currentPtr = currentPtr->nextPtr;
		}

		puts("NULL\n");
	}
}

void istructions(void)
{
	// Print's the istructions
	puts("---Dynamic-Allocation---\nEnter the choise:\n1) Insert an element\n2) Delate an element\n3) End");
}
