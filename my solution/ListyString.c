#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ListyString.h"

// Jose Nunez


// the two node functions i got from the notes since the paper said it was okay
// the deleterChar function im using to help my replaceChar delete characters
ListyNode *insert(ListyNode *head, char data);
ListyNode *create_node(char data);
void deleteChar(ListyString *listy, char key);

int main(int argc, char **argv)
{
  char *fileName = argv[1];

  processInputFile(fileName);

  return 0;
}

// reads textfile and creates a ListyString based on the text reads afterwards
// continues reading the textfile and manipulate ListyString based on read commands
int processInputFile(char *fileName)
{
  //calloc a str so we have a fresh string to work with, as well as declare our
  // ListyString listy and other variables
  char *str = calloc(1024, sizeof(char));
  ListyString *listy = NULL;
  char charRead;
  int i = 0;
  FILE *file = fopen(fileName,"r");

  // checks to see if the file exist, if not returns 1
    if(file == NULL)
      return 1;

  //reads the entire first line of the txtfile into str, and we use it to create
  // our ListyString.
  fscanf(file, "%s", str);
  listy = createListyString(str);
  free(str);

  // while loop that allows us to read the entire textfile
  while(!feof(file))
  {
    // reads a character from the textfile and then calls a switch statement
    // according to the character that was read
    fscanf(file, "%c ", &charRead);

    switch (charRead)
    {
      // when read, gets a key character and then a string, afterwards calls
      // the replaceChar function.
      case '@':
        // calloc a new str to work with, and then reads the first character which we will
        // replace, and then reads the remaining string in the line which we will be replacing
        // the previous character with
        str = calloc(1024, sizeof(char));
        fscanf(file, "%c ", &charRead);
        fscanf(file, "%s", str);

        replaceChar(listy, charRead, str);
        free(str);
        break;
      // when read, gets a string from our textfile and then calls listyCat and adds
      // that string into the end of our ListyString
      case '+':
        str = calloc(1024, sizeof(char));
        fscanf(file, "%s", str);
        listy = listyCat(listy,str);
        free(str);
        break;
      // when read, get a character from the textfile, and then calls replaceChar
      // function while passing it an empty string, so that it knows to delete the
      // character that was read.
      case '-':
        fscanf(file, "%c ", &charRead);
        replaceChar(listy, charRead, "");
        break;
      // when read, passes our ListyString into reverseListyString function so that
      // it can reverse it
      case '~':
        reverseListyString(listy);
        break;
      // when read, prints the length our of ListyString
      case '?':
        printf("%d\n", listyLength(listy));
        break;
      // when read, calls printListyString function and prints our ListyString
      case '!':
        printListyString(listy);
        break;
    }
  }

}

// converts a string into a linked list
ListyString *createListyString(char *str)
{
  int i = 0, lenght;
  ListyString *listy = NULL;

  // if str is NULL or empty, callocs a new ListyString and returns it
  if(str == NULL || *str == '\0')
  {
    listy = calloc(1, sizeof(ListyString));
    return listy;
  }
  // gets the length of str so that we know how many nodes we need then
  // sets the head of our ListyString by creating a new node for it
  // and then incrases its length by 1
  lenght = strlen(str);
  listy = calloc(1,sizeof(ListyString));
  listy->head = create_node(str[0]);
  listy->length++;

  // creates the remaining nodes for our ListyString
  for(i = 1; i < lenght; i++)
  {
    listy->head = insert(listy->head, str[i]);
    listy->length++;
  }
  return listy;
}

// using this function from our notes. it creates a new nodes
// and returns its address.
ListyNode *create_node(char data)
{
	ListyNode *new_node = malloc(sizeof(ListyNode));

	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

// using this function from our notes. it goes to the end of our ListyString
// and then calls create_node to insert it at the end.
ListyNode *insert(ListyNode *head, char data)
{
	ListyNode *original_head = head;

	if (head == NULL)
		return create_node(data);

	while (head->next != NULL)
		head = head->next;

	head->next = create_node(data);
	return original_head;
}


// prints our ListyString
void printListyString(ListyString *listy)
{
  ListyNode *head;

  if(listy == NULL || listy->head == NULL)
  {
    printf("(empty string)\n");
    return;
  }

  head = listy->head;
  // goes through each node in ListyString and prints it out
  while(head != NULL)
  {
      printf("%c", head->data);
      head = head->next;
  }
  printf("\n");

}
// destroyes our ListyString
ListyString *destroyListyString(ListyString *listy)
{
	ListyNode *current = NULL;
	ListyNode *temp = NULL;

  if(listy == NULL || listy->head == NULL)
    return NULL;

  current = listy->head;

  // goes through each node, and uses a temp node to get the next node in our
  // list and then frees the one we are.
  while (current != NULL)
	{
		temp = current->next;
		free(current);
		current = temp;
	}

  free(listy);
	return NULL;
}

// creates a new ListyString and copies the contents of the ListyString that
// was passed into the function.
ListyString *cloneListyString(ListyString *listy)
{
  ListyString *newListy = NULL;
  ListyNode *current;
  ListyNode *temp;
  ListyNode *newCurrent;

  if(listy == NULL)
    return NULL;
  else if(listy->head == NULL)
  {
    newListy = calloc(1, sizeof(ListyString));
    return newListy;
  }

  current = listy->head;
  newListy = malloc(sizeof(ListyString));
  newListy->length = listy->length;
  newListy->head = create_node(current->data);
  newCurrent = newListy->head;

  // goes through each node in the ListyString that was passed into the function
  // and then inserts a new node into the new ListyString that we are copying into
  // with the same data as the original
  while(current != NULL)
  {
    temp = current->next;
    if(temp != NULL)
      newCurrent = insert(newCurrent,temp->data);
      current = temp;
  }

  return newListy;

}

// reverses the ListyString that is passed into the function
void reverseListyString(ListyString *listy)
{
  ListyNode *current;
  ListyNode *previous = NULL;
  ListyNode *next = NULL;

  if(listy == NULL || listy->head == NULL)
    return;

  current = listy->head;

  // goes through each node in our ListyString and swaps them around so that the
  // end result is a reverses ListyString
  while(current != NULL){
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }
  listy->head = previous;
}

// compares two ListyString and returns 0 if they are the statement
// or 1 if they are different
int listyCmp(ListyString *listy1, ListyString *listy2)
{
  ListyNode *current1;
  ListyNode *temp1;
  ListyNode *current2;
  ListyNode *temp2;
  int i;

  if(listy1 == NULL && listy2 == NULL)
    return 0;
  else if((listy1 == NULL && listy2 != NULL) || (listy1 != NULL && listy2 == NULL))
    return 1;
  else if(listy1->head == NULL && listy2->head == NULL)
    return 0;
  else if(listy1->length != listy2->length)
    return 1;

  current1 = listy1->head;
  current2 = listy2->head;

  // goes through each node both ListyString's and compares the
  // data in each. if it finds one thats not equal then returns 1
  for(i = 0; i < listy1->length; i++)
  {
    if(current1->data != current2->data)
      return 1;

    temp1 = current1->next;
    temp2 = current2->next;
    current1 = temp1;
    current2 = temp2;

  }

    return 0;
}

// concatenates a string into the end of our ListyString
ListyString *listyCat(ListyString *listy, char *str)
{
  ListyNode *strHead = NULL;
  ListyNode *head = NULL;
  ListyString *newListy = NULL;
  int strLength, i;

  // if the ListyString is NULL but the string passed
  // is non-empty we create a new ListyString and return it
  if(listy == NULL && str != NULL && *str != '\0')
  {
    newListy = createListyString(str);
    return newListy;
  }
  else if(listy == NULL && str == NULL)
  {
    return NULL;
  }
  // if ListyString is NULL and the string passed was empty, we calloc a new
  // ListyString and return it.
  else if(listy == NULL && *str == '\0')
  {
    newListy = calloc(1, sizeof(ListyString));
    return newListy;
  }
  else if(str == NULL || *str == '\0')
  {
    return listy;
  }


  strLength = strlen(str);
  head = listy->head;

  // creates the head of the Linked list we are gona make for the string that was
  // passed in
  strHead = create_node(str[0]);

  // inserts a node into the Linked list for each character that was in the
  // string that was passed in
  for(i = 1; i < strLength; i++)
    strHead = insert(strHead, str[i]);

  if(listy->head == NULL)
  {
    listy->head = strHead;
    listy->length += strLength;
    return listy;
    }

  // reads to the end of our ListyString
  while(head->next != NULL)
    head = head->next;


  // makes the tail of our ListyString point to the head of the
  // linked list we just made for the string we passed in, and then incrase
  // ListyString length by the number of characters it had.
  head->next = strHead;
  listy->length += strLength;

  return listy;
}

// replaces a character in ListyString with a string that we passed in, or if
// the string we pass in is empty, we delete that character from ListyString
void replaceChar(ListyString *listy, char key, char *str)
{
  ListyNode *head = NULL;
  ListyNode *strHead = NULL;
  ListyNode *previous = NULL;
  ListyNode *temp = NULL;
  int strLength, i;

  if(listy == NULL || listy->head == NULL)
    return;

  if(str == NULL || *str == '\0')
  {
    // if ListyString is empty calls deleteChar so that it can delete all
    // instances of key from ListyString
    deleteChar(listy, key);
    return;
  }


  strLength = strlen(str);
  head = listy->head;

  // goes through each node in ListyString
  while(head != NULL)
  {
    if(head->data == key)
    {
      // creates a linked list for the string that was passed in
      strHead = create_node(str[0]);

      for(i = 1; i < strLength; i++)
        strHead = insert(strHead, str[i]);

      // make the temp pointer go to the end of the
      // linked list we just created
      temp = strHead;
      while(temp->next != NULL)
        temp = temp->next;

      // if the node we are gona replace is the head of our ListyString
      if(listy->head == head)
      {
        // make the head of our ListyString be the head of the linked list we
        // created, and make the tail of the list point to the next node in ListyString
        // and make previous become the tail of list.
        listy->head = strHead;
        temp->next = head->next;
        previous = temp;
        free(head);
        head = temp->next;
        listy->length += strLength - 1;
      }
      else
      {
        temp->next = head->next;
        previous->next = strHead;
        free(head);
        head = temp->next;
        previous = temp;
        listy->length += strLength - 1;
      }

    }
    // if a node doesnt contain a character to delete just move the head and
    // previous pointer forward
    else
    {
        previous = head;
        head = head->next;
    }

  }

}

// removes all instances of a character from our ListyString
void deleteChar(ListyString *listy, char key)
{
  ListyNode *head = NULL;
  ListyNode *previous = NULL;
  ListyNode *temp = NULL;

  head = listy->head;

  // goes through each node in ListyString
  while(head != NULL)
  {
    // if the node we are in contains the character we need to remove
    if(head->data == key)
    {
      // if the head of our ListyString is the node we need to remove
      if(listy->head == head)
      {
        // make temp point to the next node in ListyString, and make that the
        // head of ListyString, then frees the node we are currently on
        // and then just move it to temp
        temp = head->next;
        listy->head = temp;
        free(head);
        head = temp;
        listy->length -=1;
      }
      else
      {
        temp = head->next;
        previous->next = temp;
        free(head);
        head = temp;
        listy->length -=1;
      }
    }
    // if a node doesnt contain a character to delete just move the head and
    // previous pointer forward
    else
    {
      previous = head;
      head = head->next;
    }
  }

}

// returns -1 if ListyString is NULL or 0 if the head of ListyString is NULL
// else returns the lenght of our ListyString
int listyLength(ListyString *listy)
{

  if(listy == NULL)
    return -1;
  else if(listy->head == NULL)
    return 0;
  else
    return listy->length;
}

// wayyyyy harder than SmartArray O.O.....
double difficultyRating(void)
{
  return 4.5;
}

double hoursSpent(void)
{
  return 23.00;
}
