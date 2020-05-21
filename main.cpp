#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 25

typedef enum
{
  freshman = 0,
  sophomore,
  junior,
  senior
} schoolYearType; // enum type

struct studentRecord
{
  char studentName[MAX_NAME_LENGTH];
  char major[MAX_NAME_LENGTH];
  schoolYearType schoolYear;
  unsigned int IDNumber;
  struct studentRecord *next; // pointer to next node
} *list = NULL;               // Declare linked list 'list'

// forward declaration of functions (already implmented)
void flushStdIn();

void executeAction(char);

// functions that need implementation:
int addSort(char *studentName_input, char *major_input, char *schoolYear_input, unsigned int IDNumber_input); // 20 points
void displayList();
int countNodes();
int deleteNode(char *studentName_input);
void swapNodes(struct studentRecord *node1, struct studentRecord *node2);

int main()
{
  char selection = 'i'; // initialized to a dummy value
  printf("\nCSE240 HW6\n");
  do
  {
    printf("\nCurrently %d student(s) on the list.", countNodes()); // NOTE: countNodes() called here
    printf("\nEnter your selection:\n");
    printf("\t a: add a new student\n");
    printf("\t d: display student list\n");
    printf("\t r: remove a student from the list\n");
    printf("\t q: quit\n");
    selection = getchar();
    flushStdIn();
    executeAction(selection);
  } while (selection != 'q');

  return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
  char c;
  do
    c = getchar();
  while (c != '\n' && c != EOF);
}

// Ask for details from user for the given selection and perform that action
// Read the code in the function, case by case
void executeAction(char c)
{
  char studentName_input[MAX_NAME_LENGTH], major_input[MAX_NAME_LENGTH];
  unsigned int IDNumber_input, result = 0;
  char schoolYear_input[20];
  switch (c)
  {
  case 'a': // add student
    // input student details from user
    printf("\nEnter student name: ");
    fgets(studentName_input, sizeof(studentName_input), stdin);
    studentName_input[strlen(studentName_input) - 1] = '\0'; // discard the trailing '\n' char
    printf("Enter major: ");
    fgets(major_input, sizeof(major_input), stdin);
    major_input[strlen(major_input) - 1] = '\0'; // discard the trailing '\n' char

    printf("Enter whether student is 'freshman' or 'sophomore' or 'junior' or 'senior': ");
    fgets(schoolYear_input, sizeof(schoolYear_input), stdin);
    schoolYear_input[strlen(schoolYear_input) - 1] = '\0'; // discard the trailing '\n' char
    printf("Please enter ID number: ");
    scanf("%d", &IDNumber_input);
    flushStdIn();

    // add the student to the list
    result = addSort(studentName_input, major_input, schoolYear_input, IDNumber_input);
    if (result == 0)
      printf("\nStudent is already on the list! \n\n");
    else if (result == 1)
      printf("\nStudent successfully added to the list! \n\n");

    break;

  case 'd': // display the list
    displayList();
    break;

  case 'r': // remove a student
    printf("\nPlease enter student name: ");
    fgets(studentName_input, sizeof(studentName_input), stdin);
    studentName_input[strlen(studentName_input) - 1] = '\0'; // discard the trailing '\n' char

    // delete the node
    result = deleteNode(studentName_input);
    if (result == 0)
      printf("\nStudent does not exist! \n\n");
    else if (result == 1)
      printf("\nStudent successfully removed from the list. \n\n");
    else
      printf("\nList is empty! \n\n");
    break;

  case 'q': // quit
    break;
  default:
    printf("%c is invalid input!\n", c);
  }
}

// This function is used to insert a new student into the list. You can insert the new student to the end of the linked list.
// If the student already exists then return 0 without adding student to the list. If the student does not exist in the list then go on to add the student at the end of the list and return 1.
// Sorting should happen within the list. That is, you should not create a new linked list of students having sorted students.
int addSort(char *studentName_input, char *major_input, char *schoolYear_input, unsigned int IDNumber_input)
{

  struct studentRecord *tempList = list; // work on a copy of 'list'

  struct studentRecord *newData = (struct studentRecord *)malloc(sizeof(struct studentRecord));

  strcpy(newData->studentName, studentName_input);

  strcpy(newData->major, major_input);

  newData->IDNumber = IDNumber_input;

  if (strcmp(schoolYear_input, "freshman") == 0)
  {

    newData->schoolYear = freshman;
  }
  else if (strcmp(schoolYear_input, "sophomore") == 0)
  {

    newData->schoolYear = sophomore;
  }
  else if (strcmp(schoolYear_input, "junior") == 0)
  {

    newData->schoolYear = junior;
  }
  else
  {

    newData->schoolYear = senior;
  }
  newData->next = NULL;

  if (list == NULL)
  {
    list = (struct studentRecord *)malloc(sizeof(struct
                                                 studentRecord));

    list->next = newData;
  }
  else if (list->next == NULL)
  {

    list->next = newData;
  }
  else
  {
    do
    {
      if (strcmp(studentName_input, tempList->studentName) == 0)
      {
        return 0;
      }

      tempList = tempList->next;

    } while (tempList->next != NULL);

    tempList->next = newData;
  }
  return 1;
}

// This function displays the linked list of students, with all details (struct elements).
// Parse through the linked list and print the student details one after the other. See expected output screenshots in homework question file.
void displayList()
{
  struct studentRecord *tempList = list; // work on a copy of 'list'

  if (list == NULL)
  {
    printf("\nList is emtpy.\n");

    return;
  }
  else if (list->next == NULL)
  {
    printf("\nList is emtpy.\n");

    return;
  }

  tempList = tempList->next;

  while (tempList != NULL)
  {
    printf("\nStudent Name: %s\n", tempList->studentName);
    printf("Major: %s\n", tempList->major);

    if (tempList->schoolYear == freshman)
    {
      printf("School year: freshman\n");
    }

    if (tempList->schoolYear == sophomore)
    {
      printf("School year: sophomore\n");
    }

    if (tempList->schoolYear == junior)
    {
      printf("School year: junior\n");
    }

    if (tempList->schoolYear == senior)
    {
      printf("School year: senior\n");
    }

    printf("ID number: %d\n", tempList->IDNumber);

    tempList = tempList->next;
  }
}

// This function counts the number of students on the linked list and returns the number.
// This function is called in main() to display number of students along with the user menu.
int countNodes()
{

  int countOfNodes = 0;

  if (list == NULL)
  {

    return 0;
  }

  struct studentRecord *tempList = list->next;

  while (tempList != NULL)
  {

    countOfNodes = countOfNodes + 1;

    tempList = tempList->next;
  }

  return countOfNodes;
}

// This function deletes the node specified by the student name.
// Parse through the linked list and remove the node containing this student name.
int deleteNode(char *studentName_input)
{
  struct studentRecord *tempList = list->next;
  if (list == NULL)
  {

    return -1;
  }
  else if (list->next == NULL)
  {

    return -1;
  }

  tempList = tempList->next;

  struct studentRecord *prevNode = list;

  while (tempList != NULL)
  {

    if (strcmp(tempList->studentName, studentName_input) == 0)
    {

      prevNode->next = tempList->next;

      free(tempList);

      return 1;
    }

    prevNode = tempList;

    tempList = tempList->next;
  }

  return 0;
}

// This function swaps the elements of parameters 'node1' and 'node2' (Here node1 does NOT mean 1st node of the list. 'node1' is just the name of the node)
// This function should not alter the 'next' element of the nodes. Only then will the nodes be swapped.
void swapNodes(struct studentRecord *node1, struct studentRecord *node2)
{

  if (node1 == NULL || node2 == NULL || node1 == list || node2 == list)
    return;

  struct studentRecord *tempList = (struct studentRecord *)malloc(sizeof(struct studentRecord));

  strcpy(tempList->studentName, node2->studentName);

  strcpy(tempList->major, node2->major);

  tempList->schoolYear = node2->schoolYear;

  tempList->IDNumber = node2->IDNumber;

  strcpy(node2->studentName, node1->studentName);

  strcpy(node2->major, node1->major);

  node2->schoolYear = node1->schoolYear;

  node2->IDNumber = node1->IDNumber;

  strcpy(node1->studentName, tempList->studentName);

  strcpy(node1->major, tempList->major);

  node1->schoolYear = tempList->schoolYear;

  node1->IDNumber = tempList->IDNumber;
}