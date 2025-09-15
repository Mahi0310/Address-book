#include "contact.h"

void listContacts(AddressBook *addressBook) 
{
   printf("Contacts details\n");
   for(int i=0; i<addressBook->contactCount; i++)
   {
	printf("%s\t%s\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
   }	
}

void initialize(AddressBook *addressBook) 
{
  addressBook->contactCount=0;
  populatecontact(addressBook);  
}

int createContact(AddressBook *addressBook) 
{	//Check if the address book is full
	if(addressBook->contactCount >= MAX_CONTACTS){
		printf("Address book is full.\n");
		return 0;
	}
Contact newContact;
int isDuplicate=0, validphone=1, validEmail=1;
//Get the name from the user
printf("Enter the Contact name: ");
scanf(" %[^\n]", newContact.name);
//Check if the name is already existed
for(int i=0; i<addressBook->contactCount; i++){
	if(strcmp(addressBook->contacts[i].name, newContact.name)==0){
		printf(" '%s' already exists. Enter new name...\n", newContact.name);
		return 1;
		}
	}
//Get the phone number from the user	
printf("Enter the 10 Digits phone number: ");
scanf(" %s", newContact.phone);
//Validate the length of the phone number
if(strlen(newContact.phone)!=10){
   validphone=0;
   //check all the character are digits
}else{

	for(int i=0; newContact.phone[i]!='\0'; i++)
	{
		if(newContact.phone[i]< '0' || newContact.phone[i]> '9'){
			validphone=0;
			break;
		}
	}
	//Check if the number is already existed
	for(int i=0; i<addressBook->contactCount; i++)
	{
	   if(strcmp(addressBook->contacts[i].phone, newContact.phone) ==0)
	   {
	       printf(" '%s' already exists. Enter a new number...\n", newContact.phone);
    		return 1;
	   }		
	}
	}
//If the phonenumber is not valid, ask the user
if(!validphone){
	printf("Invalid phone number. Please enter a valid 10-digit number.\n");
	return 0;
}
//Get the email from the user
printf("Enter the email id: ");
scanf("%s", newContact.email);
//Validate the format of email Id
if(strchr(newContact.email,'@')==NULL || strchr(newContact.email, '.')==NULL){
	validEmail=0;
}
//check if the email is already existed in addressbook
for(int i=0;i<addressBook->contactCount; i++){
	if(strcmp(addressBook->contacts[i].email, newContact.email)==0){
		printf(" '%s' already exists. Enter new email...\n", newContact.email);
		return 1;
	}
}
// if its not valid ask the user to enter right email
	if(!validEmail){
		printf("Please Enter a valid Email.\n");
		return 0;
	}

addressBook->contacts[addressBook->contactCount++]=newContact;
printf("\nContact saved successfully..");
return 1;
}

int searchContact(AddressBook *addressBook) 
{
	int option,i,found=0;
	char query[50];
	//Display menu options for searching
	printf("\n\n1.Enter contact name\n2.Enter phone number\n3.Enter Email i'd\n\n");
	printf("Enter the choice: ");
	if(scanf("%d", &option)!=1){
		printf("Invalid input. Please enter a valid.\n");
		return 1;
	}
	
	//Validate user input
	if(option < 1|| option >3){
		printf("Invalide choice, please enter a valid option.\n");
		return 1;
	}
	//Get search query from user
	printf("\nEnter the search query: ");
	scanf(" %[^\n]", query);
	// Display table header
	printf("slno.\tName\t\t\tPhone number\t\t\tEmail i'd\n");
	//Iterate through contacts and search based on the selected option
	for(i=0; i<addressBook->contactCount; ++i){
		if((option ==1 && strcasecmp(query, addressBook->contacts[i].name)==0) ||
		   (option ==2 && strncmp(query, addressBook->contacts[i].phone, strlen(query))==0) ||
         	   (option ==3 && strcasecmp(query, addressBook->contacts[i].email)==0)){
     		   // print matching contact details
		   printf("%d. \t%-20s\t%-20s\t%-20s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
		   found =1;
		}
	}

			//If no match was found
			if(!found){
				printf("No contacts found...Enter valid query\n");
				return 1;
			}
	return 0;
}

void editContact(AddressBook *addressBook) 
{
	int slno,i,flag=0,choice;
	char str[50];
	//ask user to enter the serial number of the contact to be edited
	printf("\n\nEnter the serial number of the contact : \n");
	if(scanf("%d", &slno) !=1){
		printf("Invalid input, please enter valid.\n");
		while(getchar() !='\n' ); //clear input buffer
		return;
	}
	//Validate if the entered serial number exists in the contact list
	if(slno < 1 || slno > addressBook->contactCount){
		printf("Enter only the displayed contacts\n");
		return;
	}
	
	slno=slno-1;
	//Display menu options for editing contact details
	printf("1.Edit contact name\n2.Edit phone number\n3.Edit Email i'd\n");
	printf("Enter the choice: ");
	if(scanf("%d", &choice)!=1){
		printf("Invalid input. Please enter valid number\n");
		while(getchar() !='\n'); //clear input buffer
		return;
	}
	//perfor editing based on the user choice
		switch(choice){
		case 1:
			printf("Enter the new name: ");
			scanf(" %[^\n]",str);
			strcpy(addressBook->contacts[slno].name, str);
			printf("Updated successfully...\n");
			break;
	       case 2:
			printf("Entet the New phone number: ");
			scanf("%s",str);
			//Validate phone number length
			if(strlen(str)==10){
				for(int i=0; str[i]!='\0'; i++){
					if(str[i]<'\0' || str[i]> '9'){
						flag=1;
						break;
					}
				}
			}
			else{
				flag=1;
			}
			if(flag==1){
				printf("You entered '%ld' digits. Please enter a valid number.\n", strlen(str));
				break;
			}
			strcpy(addressBook->contacts[slno].phone, str);
			printf("Updates successfully...\n");
			break;
	     case 3:
			//Edit email address
			printf("Enter the new Email: ");
			scanf("%s", str);
			//validate email format
			if(strchr(str,'@')==NULL || strstr(str, ".com") == NULL){
				flag=1;
			}
			if(flag==1){
				printf("\n. .Please enter a valid email..\n");
				break;
			}
			strcpy(addressBook->contacts[slno].email, str);
    		            printf("Updated successfully...\n");
			    break;
	   default:
		printf("Enter the correct choice..\n");
		break;		
	}			    

}

void deleteContact(AddressBook *addressBook) 
{
	int index;
	//ask user to enter the serial number of the contact to delete
	printf("Enter the serial number: ");
	scanf("%d", &index);
	index=index-1; //Adust index to match zero-based array indexing
	// Validate the entered serial number
	if(index>=0 && index<addressBook->contactCount){
		//Shift contacts forward to overwrite the deleted contact
		for(int j=index; j<addressBook->contactCount-1; j++){
			addressBook->contacts[j]=addressBook->contacts[j+1];
		}
		//Reduce the contact count after deletion
		addressBook->contactCount--;
		printf("Successfully deleted...\n");
	}
	else{
		//Display the error message if the serial number is invalid
		printf("You entered exceeded serial number...\n");
	}
}
