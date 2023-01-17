/* Name: Myungsoo Son Student ID: 20417585 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct visitData {
  char *SrNo;
  char *ticketNo;
  char *Name;
  char *ID;
};

struct ticket {
  struct visitData visitor;
  struct ticket *nextPtr;
};

struct ticket *first = NULL; // first pointer of the structure
int cnt = 0; // count people
int serialNumber = 0; //serial number

// prototype for the functions
// modify the name, id and generate the ticket number, serial number
char *modifyName(char *name);
char *modifyId(char *id);
char *generateTicketNumber(char *name, char *srno);
char *generateSerialNumber(int cnt);

// load previous visitors information from Ticket.txt file
void load(char *SrNo, char*ticetNo, char*fullName, char*ID);
// Add a new visitor information which must have the following
void insert(char *fullName, char *id);
// Search visitor information based on Ticket Number, Name, or ID
void searchByTicketNumber(char *ticketNo);
void searchByName(char *fullName);
void searchById(char *id);
// Delete the visitor information based on ticket number, Name, or ID
void deleteByTicketNumber(char *ticketNo);
void deleteByName(char *Name);
void deleteById(char *ID);
// Display Total No of tickets sold in ascending order
void display(void);
// Update all the Tickets.txt files after insert and delete function
void update(void);

FILE *fp, *fip, *fop; // file pointer declaration (fp = read Ticket.txt, fip = write Ticket.txt, fop = append write output.txt)

int main(void) {

  // before start load the previous visitor information from the Ticket.txt file
  if ((fp = fopen("Tickets.txt", "r")) == NULL){
    puts("There is no previous visitor information in Ticket.txt file.\n");
  }
  char buffer[1024];
  fgets(buffer, sizeof(buffer), fp); // read first line which is total visitors
  if (buffer[0]){ // if there is something written on Ticket.txt file
    char buffer[1024] = {'\0', };
    while (fgets(buffer, sizeof(buffer), fp)){ // read each line
      // make new memory locations
      char *newSrNo = (char *)malloc(sizeof(char)*3);
      char *newTicketNo = (char *)malloc(sizeof(char) * 20);
      char *newId = (char *)malloc(sizeof(char) * 20);
      char *newName = (char *)malloc(sizeof(char) * 30);
      char *temp = (char *)malloc(sizeof(char)*1024);

      // copy and paste each information
      temp = strtok(buffer," ");
      for (int i=0;i<strlen(temp);i++) newSrNo[i] = temp[i];
      newSrNo[strlen(temp)] = '\0';
      temp = strtok(NULL, " ");
      for (int i=0;i<strlen(temp);i++) newTicketNo[i] = temp[i];
      newTicketNo[strlen(temp)] = '\0';
      temp = strtok(NULL, " ");
      for (int i=0;i<strlen(temp);i++) newName[i] = temp[i];
      newName[strlen(temp)] = '\0';
      temp = strtok(NULL, " ");
      for (int i=0;i<strlen(temp);i++) newId[i] = temp[i];
      newId[strlen(temp)-1] = '\0';

      load(newSrNo, newTicketNo, newName, newId); //call the load function

      serialNumber = (newSrNo[0]-48)*10 + (newSrNo[1]-48); // update the serial number
      cnt += 1; // add counters
      char buffer[1024] = {'\0',}; // initialize the buffer
    }
  }
  fclose(fp); // close the read file pointer of Ticket.txt file

  // open the files to write
  if ((fip = fopen("Tickets.txt", "w")) == NULL){
    puts("File Tickets.txt could not be opened");
  }
  if ((fop = fopen("output.txt", "a")) == NULL){
    puts("File output.txt could not be opended");
  }

  // display the request options
  printf("%s", "Enter request\n"
               " 1 - Add a new visitor information\n"
               " 2 - Search visitor information based on Ticket No\n"
               " 3 - Search visitor information based on full name\n"
               " 4 - Search visitor information based on ID\n"
               " 5 - Delete the visitor information based on ticket number\n"
               " 6 - Delete the visitor information based on full name\n"
               " 7 - Delete the visitor information based on ID\n"
               " 8 - Display Total No of tickets sold\n"
               " 9 - End of run\n");

  // infinite while loop
  while (1) {
    puts("----------------------------------------------------------");
    printf("Enter in the request Number : ");

    int request; // input the request number
    scanf("%d", &request);
    puts("");

    if (request == 9) { // end of loop
      printf("End of run\n");
      break;
    }

    switch (request) {
    case 1: // Add a new visitor information of serial number, full name, ticket number and ID
    {
      char tempName[30]; // input full name
      printf("Enter in Full Name and ID.\n");
      printf("1. Full Name: ");
      while (getchar() != '\n') {};
      scanf(" %[^\n]s", tempName);

      char tempId[20]; // input ID
      printf("2. ID: ");
      while (getchar() != '\n') {};
      scanf(" %[^\n]s", tempId);

      insert(tempName, tempId); // call insert function
      break;
    }

    case 2: // Search visitor information based on Ticket Number
    {
      char tempTicketNumber[18];
      printf("Enter in the ticket number : ");
      while (getchar() != '\n') {};
      scanf("%s", tempTicketNumber);
      searchByTicketNumber(tempTicketNumber); // call search by ticket number function
      break;
    }

    case 3: // Search visitor information based on full name
    {
      char tempName[30];
      printf("Enter in the name : ");
      while (getchar() != '\n') {};
      fgets(tempName, 30, stdin);
      tempName[strlen(tempName) - 1] = '\0';
      searchByName(modifyName(tempName)); // call search by name function
      break;
    }
    case 4: // Search visitor information based on ID
    {
      char tempId[20];
      printf("Enter in the ID : ");
      while (getchar() != '\n') {};
      scanf("%s", tempId);
      searchById(modifyId(tempId)); // call search by ID function
      break;
    }

    case 5: // Delete the visitor information based on ticket number written on ticket
    {
      char tempTicketNumber[18];
      printf("Enter in the Ticket Number: ");
      while (getchar() != '\n') {};
      scanf("%s", tempTicketNumber);
      deleteByTicketNumber(tempTicketNumber); // call delete by ticket number function
      break;
    }
    case 6: // Delete the visitor information based on full name
    {
      char tempName[30];
      printf("Enter in the Full Name: ");
      while (getchar() != '\n') {};
      fgets(tempName, 30, stdin);
      tempName[strlen(tempName) - 1] = '\0';
      deleteByName(modifyName(tempName)); // call delete by name function
      break;
    }
    case 7: // Delete the visitor information based on ID
    {
      char tempId[20];
      printf("Enter in the ID: ");
      while (getchar() != '\n') {};
      scanf("%s", tempId);
      deleteById(modifyId(tempId)); // call delete by ID function
      break;
    }
    case 8: // Display Total No of tickets sold
      display(); // call display by ascending order function
      break;

    default: // wrong number...
      printf("Enter in the correct number.");
      break;
    }

    fprintf(fop, "\n");
  }

  update(); // call update function

  // close the file
  fclose(fip);
  fclose(fop);
}


// the original name with spaces is in the parameter
char *modifyName(char *name) {
  char *newName = (char *)malloc(sizeof(char) * 30);

  int l = strlen(name); //length of the full name
  for (int i=0;i<l;i++){
    if (name[i]==' ' || name[i]=='_') l--;
  }

  int idx = 0;
  if (l<6){ // if length of name < 6, add spaces left
    for (int i=0;i<6-l;i++){
        newName[idx++] = ' ';
    }
  }
  for (int i = 0; i < 30; i++) {
    if (name[i] == '\0') {
      newName[idx++] = '\0';
      break;
    } else if (name[i] == ' ') newName[idx++] = '_';
    else {
      if (i == 0)
        newName[idx++] = toupper(name[i]);
      else if (name[i - 1] == ' ')
        newName[idx++] = toupper(name[i]);
      else
        newName[idx++] = tolower(name[i]);
    }
  }
  return newName;
}

// the original id without 'PASS' of 'IC' is in the parameter
char *modifyId(char *id) {
  int lori;
  char *newId = (char *)malloc(sizeof(char) * 20);
  int idx = 0;
  while (1) {
    printf("Are you 1.local or 2.international?: ");
    scanf("%d", &lori);

    if (lori == 1) {
      newId[idx++] = 'I';
      newId[idx++] = 'C';
      break;
    } else if (lori == 2) {
      newId[idx++] = 'P';
      newId[idx++] = 'A';
      newId[idx++] = 'S';
      newId[idx++] = 'S';
      break;
    } else {
      printf("You wrote the invalid number. Try again.\n");
      continue;
    }
  }

  for (int i = 0; i < 20; i++) {
    if (id[i] == '\0') {
      newId[idx++] = '\0';
      break;
    }
    newId[idx++] = id[i];
  }
  return newId;
}

// name should be original name with space(not the modified name)
// srno should be modified
char *generateTicketNumber(char *name, char *srno) {
  // max alphabet ASCII code length = 3, serial number = 2, there are 6
  // alphabets so 3*6+2 = 20;
  char *newTicketNo = (char *)malloc(sizeof(char) * 20);
  int idx = 0;
  int countChar = 0;
  char temp[4];

  // change the alphabet to ASCII code decimal
  for (int i = 0; countChar<6; i++) {
    if (name[i] == '\0') break;
    if (name[i]=='_') continue;

    countChar++;
    sprintf(temp, "%d", (int)name[i]);
    for (int j = 0; j < 4; j++) {
      if (temp[j] == '\0') break;
      newTicketNo[idx++] = temp[j];
    }
  }

  newTicketNo[idx] = '\0';
  strcat(newTicketNo, srno); // add serial number at the last
  return newTicketNo;
}

char *generateSerialNumber(int serialNumber) {
  char *newSrNo = (char *)malloc(sizeof(char)*3);
  char *temp = (char *)malloc(sizeof(char)*3);
  if (serialNumber < 10) { // if cnt<10 then put '0'in front the number
    temp[0] = '0';
    temp[1] = (char)(serialNumber+48);
  } else {
    temp[0] = (char)(serialNumber/10+48);
    temp[1] = (char)(serialNumber%10+48);
  }
  temp[2] = '\0';
  newSrNo = temp;
  return newSrNo;
}

// load previous visitors information from Ticket.txt file and put in the linked list
void load(char *newSrNo, char*newTicketNo, char*newName, char*newId){
  // make the new visitor structure
  struct ticket *newVisitor = (struct ticket *)malloc(sizeof(struct ticket));
  newVisitor->nextPtr = NULL;
  newVisitor->visitor.ID = newId;
  newVisitor->visitor.Name = newName;
  newVisitor->visitor.SrNo = newSrNo;
  newVisitor->visitor.ticketNo = newTicketNo;

  struct ticket *ptr;
  if (first == NULL) { // if it is empty
    first = newVisitor;
    return;
  } else {
    if (strcmp(first->visitor.Name, newVisitor->visitor.Name) > 0) { // not empty, insert at first
      newVisitor->nextPtr = first;
      first = newVisitor;
      return;
    }

    for (ptr = first; ptr->nextPtr; ptr = ptr->nextPtr) { // insert at middle
      if (strcmp(ptr->visitor.Name, newVisitor->visitor.Name) <= 0 && strcmp(ptr->nextPtr->visitor.Name, newVisitor->visitor.Name) > 0) {
        newVisitor->nextPtr = ptr->nextPtr;
        ptr->nextPtr = newVisitor;
        return;
      }
    }

    ptr->nextPtr = newVisitor; // insert at last
    return;
  }
}


// Add a new visitor information which must have the following
// full name and id should be modified parameter
void insert(char *fullName, char *id) {

  // the limit is 40 people
  if (cnt == 40) {
    printf("The booking list is full.\n");
    fprintf(fop, "The booking list is full.\n");
    return;
  }
  cnt += 1;
  serialNumber += 1;

  // modify serial number, ticket number, name and ID
  char *newSrNo = generateSerialNumber(serialNumber);
  char *newTicketNo = generateTicketNumber(fullName, newSrNo);
  char *newName = modifyName(fullName);
  char *newId = modifyId(id);

  // make the new visitor structure
  struct ticket *newVisitor = (struct ticket *)malloc(sizeof(struct ticket));
  newVisitor->nextPtr = NULL;
  newVisitor->visitor.ID = newId;
  newVisitor->visitor.Name = newName;
  newVisitor->visitor.SrNo = newSrNo;
  newVisitor->visitor.ticketNo = newTicketNo;

  puts("");
  printf("The information of the visitor %s is recorded.\n", newName);
  fprintf(fop, "The information of the visitor %s is recorded.\n", newName);

  struct ticket *ptr;
  if (first == NULL) { // if it is empty
    first = newVisitor;
    return;
  } else {
    if (strcmp(first->visitor.Name, newVisitor->visitor.Name) > 0) { // not empty, insert at first
      newVisitor->nextPtr = first;
      first = newVisitor;
      return;
    }

    for (ptr = first; ptr->nextPtr; ptr = ptr->nextPtr) { // insert at middle
      if (strcmp(ptr->visitor.Name, newVisitor->visitor.Name) <= 0 && strcmp(ptr->nextPtr->visitor.Name, newVisitor->visitor.Name) > 0) {
        newVisitor->nextPtr = ptr->nextPtr;
        ptr->nextPtr = newVisitor;
        return;
      }
    }

    ptr->nextPtr = newVisitor; // insert at last
    return;
  }
}

// Search visitor information based on Ticket Number
// ticket number should be modified parameter
void searchByTicketNumber(char *ticketNo) {
  if (first == NULL) { // empty list
    printf("The booking list is empty!\n");
    fprintf(fop, "The booking list is empty!\n");
    return;
  }

  struct ticket *ptr;
  for (ptr = first; ptr; ptr = ptr->nextPtr) {
    if (strcmp(ptr->visitor.ticketNo, ticketNo) == 0) { // Found data
      printf("The following record of the visitor is found:\n");
      printf("%s %s %s %s\n", ptr->visitor.SrNo, ptr->visitor.ticketNo, ptr->visitor.Name, ptr->visitor.ID);
      fprintf(fop, "The following record of the visitor is found:\n");
      fprintf(fop, "%s %s %s %s\n", ptr->visitor.SrNo, ptr->visitor.ticketNo, ptr->visitor.Name, ptr->visitor.ID);
      return;
    }
  }
  printf("The following record of the visitor is not found.\n");
  fprintf(fop, "The following record of the visitor is not found.\n");
  return; // No data found
}

// Search visitor information based on Name
// full name should be modified parameter
void searchByName(char *fullName) {
  if (first == NULL) { // empty list
    printf("The booking list is empty!\n");
    fprintf(fop, "The booking list is empty!\n");
    return;
  }

  struct ticket *ptr;
  int cnt = 0;
  for (ptr = first; ptr; ptr = ptr->nextPtr) {
    if (strcmp(ptr->visitor.Name, fullName) == 0) { // Found data
      if (cnt == 0) {
        printf("The following record of the visitor is found:\n");
        fprintf(fop, "The following record of the visitor is found:\n");
        cnt++;
      }
      printf("%s %s %s %s\n", ptr->visitor.SrNo, ptr->visitor.ticketNo, ptr->visitor.Name, ptr->visitor.ID);
      fprintf(fop, "%s %s %s %s\n", ptr->visitor.SrNo, ptr->visitor.ticketNo, ptr->visitor.Name, ptr->visitor.ID);
    }
  }
  if (cnt == 0) {
    printf("The following record of the visitor is not found.\n");
    fprintf(fop, "The following record of the visitor is not found.\n");
    return; // No data found
  }
  return;
}

// Search visitor information based on ID
// ID should be modified parameter
void searchById(char *id) {
  if (first == NULL) { // empty list
    printf("The booking list is empty!\n");
    fprintf(fop, "The booking list is empty!\n");
    return;
  }

  struct ticket *ptr;
  for (ptr = first; ptr; ptr = ptr->nextPtr) {
    if (strcmp(ptr->visitor.ID, id) == 0) { // Found data
      printf("The following record of the visitor is found:\n");
      printf("%s %s %s %s\n", ptr->visitor.SrNo, ptr->visitor.ticketNo, ptr->visitor.Name, ptr->visitor.ID);
      fprintf(fop, "The following record of the visitor is found:\n");
      fprintf(fop, "%s %s %s %s\n", ptr->visitor.SrNo, ptr->visitor.ticketNo, ptr->visitor.Name, ptr->visitor.ID);
      return;
    }
  }
  printf("The following record of the visitor is not found.\n");
  fprintf(fop, "The following record of the visitor is not found.\n");
  return; // No data found
}

// Delete the visitor information based on ticket number
// ticket number should be modified parameter
void deleteByTicketNumber(char *ticketNo) {
  struct ticket *cur, *prev;
  cur = prev = first;

  if (first == NULL) { // empty list
    printf("The booking list is empty!\n");
    fprintf(fop, "The booking list is empty!\n");
    return;
  }

  if (strcmp(first->visitor.ticketNo, ticketNo) == 0) { // delete the first visitor information
    first = cur->nextPtr;
    cur->nextPtr = NULL;
    free(cur);
    printf("The visitor with Ticket No.: %s, information is deleted.\n", ticketNo);
    fprintf(fop, "The visitor with Ticket No.: %s, information is deleted.\n", ticketNo);
    cnt--;
    return;
  }

  for (; cur; cur = cur->nextPtr) { // delete the middle or last visitor information
    if (strcmp(cur->visitor.ticketNo, ticketNo) == 0) {
      printf("The visitor with Ticket No.: %s, information is deleted.\n", ticketNo);
      fprintf(fop, "The visitor with Ticket No.: %s, information is deleted.\n", ticketNo);
      prev->nextPtr = cur->nextPtr;
      cur->nextPtr = NULL;
      free(cur);
      cnt--;
      return;
    }
    prev = cur;
  }

  printf("The visitor with Ticket No.: %s, information is not found.\n", ticketNo); // Not found
  fprintf(fop, "The visitor with Ticket No.: %s, information is not found.\n", ticketNo);
  return;
}

// Delete the visitor information based on full name
// only delete one first appears in the booking list
// Name should be modified parameter
void deleteByName(char *Name) {
  struct ticket *cur, *prev;
  cur = prev = first;

  if (first == NULL) { // empty list
    printf("The booking list is empty!\n");
    fprintf(fop, "The booking list is empty!\n");
    return;
  }

  int cntDeleteName = 0;
  struct ticket * temp;

  if (strcmp(first->visitor.Name, Name) == 0) { // delete the first visitor information
    cntDeleteName++;
    temp = first;
    cur = cur->nextPtr;
  }

  for (; cur; cur = cur->nextPtr) { // delete the middle or last visitor information
    if (strcmp(cur->visitor.Name, Name) == 0) {
      if (cntDeleteName == 0) {
        temp = cur;
      }
      else if (cntDeleteName == 1){
        printf("The following visitors have same names,\n");
        printf("%s %s %s %s\n", temp->visitor.SrNo, temp->visitor.ticketNo, temp->visitor.Name, temp->visitor.ID);
        printf("%s %s %s %s\n", cur->visitor.SrNo, cur->visitor.ticketNo, cur->visitor.Name, cur->visitor.ID);
      }
      else{
        printf("%s %s %s %s\n", cur->visitor.SrNo, cur->visitor.ticketNo, cur->visitor.Name, cur->visitor.ID);
      }
      cntDeleteName++;
    }
    prev = cur;
  }

  if (cntDeleteName == 0) { // Not found
    printf("The visitor: %s information is not found.\n", Name);
    fprintf(fop, "The visitor: %s information is not found.\n", Name);
  }
  else if (cntDeleteName==1){ // only one name
    cnt--;
    cur=first;
    if (temp==first){ // delete the first visitor information
        first = cur->nextPtr;
        cur->nextPtr = NULL;
        free(cur);
    }
    else{
        for (; cur; cur = cur->nextPtr) { // delete the middle or last visitor information
            if (strcmp(cur->visitor.Name, Name) == 0) {
                prev->nextPtr = cur->nextPtr;
                cur->nextPtr = NULL;
                free(cur);
            }
            prev = cur;
        }
    }
    printf("The visitor: %s information is deleted.\n", Name);
    fprintf(fop, "The visitor: %s information is deleted.\n", Name);
  }
  else{ //if there are more than 1 name, delete by ID
    char tempId[20];
    printf("Please enter the ID to deleted: ");
    scanf("%s", tempId);
    deleteById(modifyId(tempId)); // call delete by ID function
  }
  return;
}

// Delete the visitor information based on ID
// ID should be modified parameter
void deleteById(char *ID) {
  struct ticket *cur, *prev;
  cur = prev = first;

  if (first == NULL) { // empty list
    printf("The booking list is empty!\n");
    fprintf(fop, "The booking list is empty!\n");
    return;
  }

  if (strcmp(first->visitor.ID, ID) == 0) { // delete the first visitor information
    first = cur->nextPtr;
    cur->nextPtr = NULL;
    free(cur);
    printf("The visitor with ID: %s, information is deleted.\n", ID);
    fprintf(fop, "The visitor with ID: %s, information is deleted.\n", ID);
    cnt--;
    return;
  }

  int cnt1 = 0;
  for (; cur; cur = cur->nextPtr) { // delete the middle or last visitor information
    if (strcmp(cur->visitor.ID, ID) == 0) {
      if (cnt1 == 0) {
        printf("The visitor with ID: %s, information is deleted.\n", ID);
        fprintf(fop, "The visitor with ID: %s, information is deleted.\n", ID);
        cnt1++;
      }
      prev->nextPtr = cur->nextPtr;
      cur->nextPtr = NULL;
      free(cur);
      cnt--;
      return;
    }
    prev = cur;
  }

  if (cnt1 == 0) {
    printf("The visitor with ID: %s, information is not found.\n", ID); // Not found
    fprintf(fop, "The visitor with ID: %s, information is not found.\n", ID); // Not found
  }
  return;
}

// Display Total No of tickets sold
void display() {
  if (first == NULL) { // empty list
    printf("The booking list is empty!\n");
    fprintf(fop, "The booking list is empty!\n");
    return;
  }

  struct ticket *ptr;
  for (ptr = first; ptr; ptr = ptr->nextPtr) {
    printf("%s %s %s %s\n", ptr->visitor.SrNo, ptr->visitor.ticketNo, ptr->visitor.Name, ptr->visitor.ID);
    fprintf(fop, "%s %s %s %s\n", ptr->visitor.SrNo, ptr->visitor.ticketNo, ptr->visitor.Name, ptr->visitor.ID);
  }
  return;
}

//update the total people and list after insert and delete function
void update(){
  fprintf(fip, "Total visitors: %d\n", cnt);
  struct ticket *ptr;
  int tempSrNo = 1;
  for (int tempSrNo=1;tempSrNo<=serialNumber;tempSrNo++){
    for (struct ticket* ptr = first; ptr; ptr = ptr->nextPtr) {
        if (strcmp(ptr->visitor.SrNo, generateSerialNumber(tempSrNo))==0){
            fprintf(fip, "%s %s %s %s\n", ptr->visitor.SrNo, ptr->visitor.ticketNo, ptr->visitor.Name, ptr->visitor.ID);
            break;
        }
    }
  }

  return;
}
