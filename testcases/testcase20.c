// Sean Szumlanski
// COP 3502, Fall 2017

// =========================
// ListyString: testcase20.c
// =========================
// Unit test for listyCat(): Test concatenation of a NULL string to a non-empty
// ListyString.


#include <stdio.h>
#include <string.h>
#include "ListyString.h"

int unit_test(int argc, char **argv)
{
	int i, length, success = 1;
	char *result = "Hello";

	ListyNode *temp;
	ListyString *listy;
	ListyString *retval;

	length = strlen(result);

	listy = createListyString("Hello");
	retval = listyCat(listy, NULL);

	if (listy != retval)
		success = 0;

	// Check contents of linked list.
	temp = listy->head;
	for (i = 0; i < length; i++)
	{
		if (temp->data != result[i])
			success = 0;
		temp = temp->next;
	}

	// Check for proper NULL termination of linked list.
	if (temp != NULL)
		success = 0;

	// Check length variable.
	if (listy->length != length)
		success = 0;

	printf("%s\n", success ? "Hooray!" : "fail whale :(");

	return 0;
}
