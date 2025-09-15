#include "contact.h"

int main()
{
 int choice;
 AddressBook A1;
 AddressBook *ptr=&A1;
 initialize(ptr);
 do{
	 
	 printf("Enter the choice\n");
	 printf("Add contacts\n");
	printf("Search contacts\n");
	printf("Edit contacts\n");
	printf("Delete contacts\n");
	printf("ListAll contacts\n");
	printf("Add contact\n");
	printf("Exit\n");
	scanf("%d", &choice);
	switch(choice)
	{
		case 1:
			createContact(ptr);
			//printf("Selected Add__contact\n");
			break;


		case 2:
			searchContact(ptr);
			break;

		case 3:
			if(searchContact(ptr)!=1)
			editContact(ptr);
			break;
		case 4:
			searchContact(ptr);
			deleteContact(ptr);
			break;	

		case 5:
			listContacts(ptr);
			break;
	}
   }while(choice!=7);
	return 0;
} 


