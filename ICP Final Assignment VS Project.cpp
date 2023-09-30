//MOHAMMAD FAWZAN ALIM
//TP064501
//ICP Assignment

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<string.h>
#include<ctype.h>

void updateInventory();
void searchInventory();
void inventoryTracking();
void readExistingModels();
void getModelCode();
void readExistingParts();
void readExistingSuppliers();
void addNewModel();
void addNewSupplier();
void addNewPart();
void deleteModel();
void deletePart();
void freeModelList();
void freeSupplierList();
void freePartList();
char* rtrim(char* str);
char* upperCase(char* str);
char* lowerCase(char* str);

struct model
{
	char code[25];
	char name[25];

	struct model* next;
}*modelStart, *modelCurr;

struct part
{
	char id[25];
	char modelCode[25];
	char modelName[25];
	char sectionCode[25];
	char sectionName[25];
	char code[25];
	char name[25];
	int qty;
	char supplierCode[25];
	char supplierName[25];
	
	struct part* next;
}*partStart, *partCurr;

struct supplier
{
	char code[25];
	char name[25];

	struct supplier* next;
}*supplierStart, * supplierCurr;

void main()
{
	int menuChoice = NULL;

	modelStart = NULL;
	modelCurr = NULL;

	supplierStart = NULL;
	supplierCurr = NULL;
	readExistingModels();		//Read all existing models from file to linked list
	readExistingSuppliers();	//Read all existing suppliers from file to linked list
	
	while(1)
	{
		system("cls");
		printf("WELCOME TO AUTOMOBILE PARTS INVENTORY MANAGEMENT SYSTEM\n\n");
		printf("HOME MENU: \n");
		printf("\t1. Update inventory\n");
		printf("\t2. Inventory tracking\n");
		printf("\t3. Search inventory\n");
		printf("\t4. Add a new model\n");
		printf("\t5. Add a new part\n");
		printf("\t6. Delete a model\n");
		printf("\t7. Delete a part\n");
		printf("\t0. Exit\n");

		//MENU choice input and validation
		printf("Enter your choice of operation: ");
		if (scanf_s("%d", &menuChoice) == 0)
		{
			printf("Invalid input. Input must be an integer. Try again.\n");
			printf("Press any key to return to HOME MENU...");
			_getch();
			while (getchar() != '\n');
			continue;
		}
		while (getchar() != '\n');
		
		//Call respective functions based on input
		if (menuChoice == 1)
		{
			system("cls");
			printf("UPDATE INVENTORY\n");

			updateInventory();
		}
		else if (menuChoice == 2)
		{
			system("cls");
			printf("INVENTORY TRACKING\n");

			inventoryTracking();
		}
		else if (menuChoice == 3)
		{
			system("cls");
			printf("SEARCH INVENTORY\n");

			searchInventory();
		}
		else if (menuChoice == 4)
		{
			system("cls");
			printf("ADD A NEW MODEL\n");

			addNewModel();
		}
		else if (menuChoice == 5)
		{
			system("cls");
			printf("ADD A NEW PART\n");

			addNewPart();
		}
		else if (menuChoice == 6)
		{
			system("cls");
			printf("DELETE A MODEL\n");

			deleteModel();
		}
		else if (menuChoice == 7)
		{
			system("cls");
			printf("DELETE A PART\n");

			deletePart();
		}
		else if (menuChoice == 0)
		{
			freeModelList();
			freeSupplierList();
			printf("Exiting program...\n");

			break;
		}
		else
		{
			printf("Invalid input. Try again.\n");
		}
		printf("Press any key to return to HOME MENU...");
		_getch();

	} 
}

void updateInventory()
{
	if (modelStart == NULL)
	{
		printf("No available models. Add a model first.\n");
		return;
	}

	getModelCode(); //Ask user for model choice input and modelCurr points to input model
	readExistingParts(); //Read all data from a file to linked list partStart

	if (modelCurr == NULL)
		return;

	if (partStart == NULL)
	{
		printf("No available parts for this model. Add a part first.\n");
		return;
	}

	//Print the header in console
	printf("Available Parts:\n");
	printf("\t%-20s", "PART ID");
	printf("\t%-20s", "MODEL NAME");
	printf("\t%-20s", "SECTION NAME");
	printf("\t%-20s", "PART CODE");
	printf("\t%-20s", "PART NAME");
	printf("\t%-20s", "QUANTITY");
	printf("\t%-20s\n", "SUPPLIER NAME");

	//Print rows of parts data
	partCurr = partStart;
	while (partCurr != NULL)
	{
		printf("\t%-20s", partCurr->id);
		printf("\t%-20s", partCurr->modelName);
		printf("\t%-20s", partCurr->sectionName);
		printf("\t%-20s", partCurr->code);
		printf("\t%-20s", partCurr->name);
		printf("\t%-20d", partCurr->qty);
		printf("\t%-20s\n", partCurr->supplierName);
		
		partCurr = partCurr->next;
	}
	
	//Part code input and validation
	int matchFound = 0;
	char partChoice[25];
	do
	{
		printf("Choose Part Code: ");

		gets_s(partChoice);
		strcpy_s(partChoice, upperCase(partChoice));

		partCurr = partStart;
		while (partCurr != NULL)
		{
			if (strcmp(partCurr->code, partChoice) == 0)
			{
				matchFound = 1;
				break;
			}
			partCurr = partCurr->next;
		}
		if (matchFound == 0)
			printf("Invalid input. Try again.\n");

	} while (matchFound == 0);

	//Add or remove quantity input and validation
	int operation = 0;
	printf("Operations:\n");
	printf("\t1. Add Quantity [Supplier to Warehouse]\n");
	printf("\t2. Subtract Quantity [Warehouse to Assembly]\n");

	while(1)
	{
		printf("Choose Operation: ");
		scanf_s("%d", &operation); while (getchar() != '\n');

		if (operation != 1 && operation != 2)
			printf("Invalid input. Try again.\n");
		else
			break;
	}

	//Part quantity input, validation and update in linked list
	int qty = 0;
	while (operation == 1) //Add quantity
	{
		printf("Enter quantity to add: ");
		scanf_s("%d", &qty); while (getchar() != '\n');
		
		if (qty < 1)
			printf("Invalid quantity. Try again.\n");
		else
		{
			partCurr->qty += qty;
			break;
		}
	}
	while (operation == 2) //Subtract quantity
	{
		if (partCurr->qty == 0)
		{
			printf("Sorry. Part out of stock.\n");
			return;
		}
		printf("Enter quantity to subtract: ");
		scanf_s("%d", &qty); while (getchar() != '\n');

		if (qty < 1 || qty > partCurr->qty)
			printf("Invalid quantity. Try again.\n");
		else
		{
			partCurr->qty -= qty;
			break;
		}
	}

	//Open File
	char filename[50];
	strcpy_s(filename, modelCurr->code);
	strcat_s(filename, ".txt");

	FILE* file;
	if (fopen_s(&file, filename, "w") != 0)
	{
		printf("ERROR. File not found.\n");
		return;
	}

	//Write Header to file
	fprintf(file, "%-20s", "PART ID");
	fprintf(file, "%-20s", "MODEL CODE");
	fprintf(file, "%-20s", "MODEL NAME");
	fprintf(file, "%-20s", "SECTION CODE");
	fprintf(file, "%-20s", "SECTION NAME");
	fprintf(file, "%-20s", "PART CODE");
	fprintf(file, "%-20s", "PART NAME");
	fprintf(file, "%-20s", "QUANTITY");
	fprintf(file, "%-20s", "SUPPLIER CODE");
	fprintf(file, "%-20s", "SUPPLIER NAME");

	//Write rows of parts data to file
	partCurr = partStart;
	while (partCurr != NULL)
	{
		fprintf(file, "\n");
		fprintf(file, "%-20s", partCurr->id);
		fprintf(file, "%-20s", partCurr->modelCode);
		fprintf(file, "%-20s", partCurr->modelName);
		fprintf(file, "%-20s", partCurr->sectionCode);
		fprintf(file, "%-20s", partCurr->sectionName);
		fprintf(file, "%-20s", partCurr->code);
		fprintf(file, "%-20s", partCurr->name);
		fprintf(file, "%-20d", partCurr->qty);
		fprintf(file, "%-20s", partCurr->supplierCode);
		fprintf(file, "%-20s", partCurr->supplierName);
		
		partCurr = partCurr->next;
	}
	fclose(file);

	printf("Inventory successfully updated.\n"); 
	freePartList(); //Free Part Linked List
}

void searchInventory()
{
	if (modelStart == NULL)
	{
		printf("No available models. Add a model first.\n");
		return;
	}

	int matchFound = 0;

	//Keyword input
	char keyword[25];
	printf("Enter Search Keyword: ");
	gets_s(keyword);
	strcpy_s(keyword, upperCase(keyword));

	//Print header in console
	printf("\t%-20s", "PART ID");
	printf("\t%-20s", "MODEL NAME");
	printf("\t%-20s", "SECTION NAME");
	printf("\t%-20s", "PART CODE");
	printf("\t%-20s", "PART NAME");
	printf("\t%-20s", "QUANTITY");
	printf("\t%-20s\n", "SUPPLIER NAME");

	//Loop through the models
	modelCurr = modelStart;
	while (modelCurr != NULL)
	{
		readExistingParts(); //Read all data from the file to linked list partStart

		//Loop through the partStart linked list to find match
		int found = 0;
		partCurr = partStart;
		while (partCurr != NULL)
		{
			char modelName[25];
			char sectionName[25];
			char partName[25];
			char supplierName[25];

			strcpy_s(modelName, partCurr->modelName);
			strcpy_s(sectionName, partCurr->sectionName);
			strcpy_s(partName, partCurr->name);
			strcpy_s(supplierName, partCurr->supplierName);

			//Look for match
			if (strstr(partCurr->id, keyword))
				found = 1;
			else if (strstr(partCurr->modelCode, keyword))
				found = 1;
			else if (strstr(upperCase(modelName), keyword))
				found = 1;
			else if (strstr(partCurr->sectionCode, keyword))
				found = 1;
			else if (strstr(upperCase(sectionName), keyword))
				found = 1;
			else if (strstr(partCurr->code, keyword))
				found = 1;
			else if (strstr(upperCase(partName), keyword))
				found = 1;
			else if (strstr(partCurr->supplierCode, keyword))
				found = 1;
			else if (strstr(upperCase(supplierName), keyword))
				found = 1;
			
			//If found, print rows of parts data
			if (found)
			{
				printf("\t%-20s", partCurr->id);
				printf("\t%-20s", partCurr->modelName);
				printf("\t%-20s", partCurr->sectionName);
				printf("\t%-20s", partCurr->code);
				printf("\t%-20s", partCurr->name);
				printf("\t%-20d", partCurr->qty);
				printf("\t%-20s\n", partCurr->supplierName);
				matchFound++;
			}
			found = 0;
			partCurr = partCurr->next;
		}
		freePartList(); //Free part Linked list

		modelCurr = modelCurr->next; //Next model
	}
	printf("Match Found: %d\n", matchFound);
}

void inventoryTracking()
{
	if (modelStart == NULL)
	{
		printf("No available models. Add a model first.\n");
		return;
	}

	int totalMatchFound = 0;

	printf("Print Options: \n");
	printf("\t1. Print all parts from all model\n");
	printf("\t2. Print all parts from a model\n");
	printf("\t3. Print all parts from a section of a model\n");
	printf("\t4. Print all parts from a supplier\n");
	printf("\t5. Print all parts with low quantity from a model\n");

	//Choice of operation input and validation
	int optionChoice = 0;

	while (1)
	{
		printf("Enter choice of operation: ");
		scanf_s("%d", &optionChoice); while (getchar() != '\n');

		if (optionChoice < 1 && optionChoice > 5)
			printf("Invalid input. Try again.\n");
		else
			break;
	}

	if (optionChoice == 1)
	{
		if (modelStart == NULL)
		{
			printf("No available models. Add a model first.\n");
			return;
		}

			//Print header row in console
			printf("\t%-20s", "PART ID");
			printf("\t%-20s", "MODEL NAME");
			printf("\t%-20s", "SECTION NAME");
			printf("\t%-20s", "PART CODE");
			printf("\t%-20s", "PART NAME");
			printf("\t%-20s", "QUANTITY");
			printf("\t%-20s\n", "SUPPLIER NAME");

			//Loop through models
			modelCurr = modelStart;
			while (modelCurr != NULL)
			{
				readExistingParts(); //Read all parts data into partStart linked list

				//Print rows of parts data IF supplier code matches
				partCurr = partStart;
				while (partCurr != NULL)
				{
					printf("\t%-20s", partCurr->id);
					printf("\t%-20s", partCurr->modelName);
					printf("\t%-20s", partCurr->sectionName);
					printf("\t%-20s", partCurr->code);
					printf("\t%-20s", partCurr->name);
					printf("\t%-20d", partCurr->qty);
					printf("\t%-20s\n", partCurr->supplierName);
					totalMatchFound++;

					partCurr = partCurr->next;
				}
				freePartList(); //Free part linked list

				modelCurr = modelCurr->next; //Next model
			}
	}
	else if (optionChoice == 2)
	{
		getModelCode(); //Ask user for model choice input and modelCurr points to input model
		readExistingParts(); //Read all data from a file to linked list partStart

		//Print Header row in console
		printf("\t%-20s", "PART ID");
		printf("\t%-20s", "MODEL NAME");
		printf("\t%-20s", "SECTION NAME");
		printf("\t%-20s", "PART CODE");
		printf("\t%-20s", "PART NAME");
		printf("\t%-20s", "QUANTITY");
		printf("\t%-20s\n", "SUPPLIER NAME");
		
		//Print rows of parts data
		partCurr = partStart;
		while (partCurr != NULL)
		{
			printf("\t%-20s", partCurr->id);
			printf("\t%-20s", partCurr->modelName);
			printf("\t%-20s", partCurr->sectionName);
			printf("\t%-20s", partCurr->code);
			printf("\t%-20s", partCurr->name);
			printf("\t%-20d", partCurr->qty);
			printf("\t%-20s\n", partCurr->supplierName);
			partCurr = partCurr->next;
			totalMatchFound++;
		}

		freePartList(); //Free part linked list
		
	}
	else if (optionChoice == 3)
	{
		getModelCode(); //Ask user for model choice input and modelCurr points to input model
		readExistingParts(); //Read all data from a file to linked list partStart

		//Section choice input and validation
		char sectionChoice[25];
		printf("Available sections: \n");
		printf("\tBD. Body\n");
		printf("\tCS. Chassis\n");
		printf("\tEN. Engine\n");
		printf("\tTR. Transmission System\n");
		printf("\tOT. Others\n");
		
		while (1)
		{
			printf("Choose Section Code: ");
			gets_s(sectionChoice);
			
			if (strcmp(upperCase(sectionChoice), "BD") == 0)
				break;
			if (strcmp(upperCase(sectionChoice), "CS") == 0)
				break;
			if (strcmp(upperCase(sectionChoice), "EN") == 0)
				break;
			if (strcmp(upperCase(sectionChoice), "TR") == 0)
				break;
			if (strcmp(upperCase(sectionChoice), "OT") == 0)
				break;

			printf("Invalid input. Try again.\n");
		}

		//Print header row to console
		printf("\t%-20s", "PART ID");
		printf("\t%-20s", "MODEL NAME");
		printf("\t%-20s", "SECTION NAME");
		printf("\t%-20s", "PART CODE");
		printf("\t%-20s", "PART NAME");
		printf("\t%-20s", "QUANTITY");
		printf("\t%-20s\n", "SUPPLIER NAME");

		//Print rows of parts data IF section code matches
		partCurr = partStart;
		while (partCurr != NULL)
		{
			if (strcmp(partCurr->sectionCode, upperCase(sectionChoice)) == 0)
			{
				printf("\t%-20s", partCurr->id);
				printf("\t%-20s", partCurr->modelName);
				printf("\t%-20s", partCurr->sectionName);
				printf("\t%-20s", partCurr->code);
				printf("\t%-20s", partCurr->name);
				printf("\t%-20d", partCurr->qty);
				printf("\t%-20s\n", partCurr->supplierName);
				totalMatchFound++;
			}
			partCurr = partCurr->next;
		}

		freePartList(); //Free part linked list
	}
	else if (optionChoice == 4)
	{
		if (modelStart == NULL)
		{
			printf("No available models. Add a model first.\n");
			return;
		}

		if (supplierStart == NULL)
		{
			printf("No available suppliers. Add a part from a supplier first.\n");
			return;
		}

		//Show available suppliers using supplier linked list
		printf("Existing Suppliers: \n");
		supplierCurr = supplierStart;
		while (supplierCurr != NULL)
		{
			printf("\t%s. %s\n", supplierCurr->code, supplierCurr->name);
			supplierCurr = supplierCurr->next;
		}

		//Supplier choice input and validation
		int matchFound = 0;
		char choiceSupplier[25];
		do
		{
			printf("Choose supplier code: ");
			gets_s(choiceSupplier);
			strcpy_s(choiceSupplier, upperCase(choiceSupplier));
			supplierCurr = supplierStart;
			while (supplierCurr != NULL)
			{
				if (strcmp(supplierCurr->code, choiceSupplier) == 0)
				{
					matchFound = 1;
					break;
				}
				supplierCurr = supplierCurr->next;
			}
			if (matchFound == 0)
				printf("Invalid input. Try again.\n");
		} while (matchFound == 0);
		
		//Print header row in console
		printf("\t%-20s", "PART ID");
		printf("\t%-20s", "MODEL NAME");
		printf("\t%-20s", "SECTION NAME");
		printf("\t%-20s", "PART CODE");
		printf("\t%-20s", "PART NAME");
		printf("\t%-20s", "QUANTITY");
		printf("\t%-20s\n", "SUPPLIER NAME");

		//Loop through models
		modelCurr = modelStart;
		while (modelCurr != NULL)
		{
			readExistingParts(); //Read all parts data into partStart linked list

			//Print rows of parts data IF supplier code matches
			partCurr = partStart;
			while (partCurr != NULL)
			{
				if (strcmp(partCurr->supplierCode, choiceSupplier) == 0)
				{
					printf("\t%-20s", partCurr->id);
					printf("\t%-20s", partCurr->modelName);
					printf("\t%-20s", partCurr->sectionName);
					printf("\t%-20s", partCurr->code);
					printf("\t%-20s", partCurr->name);
					printf("\t%-20d", partCurr->qty);
					printf("\t%-20s\n", partCurr->supplierName);
					totalMatchFound++;
				}

				partCurr = partCurr->next;
			}
			freePartList(); //Free part linked list

			modelCurr = modelCurr->next; //Next model
		}
		
	}
	else if (optionChoice == 5)
	{
		getModelCode(); //Ask user for model choice input and modelCurr points to input model
		readExistingParts(); //Read all data from a file to linked list partStart
		
		//Low quantity threshhold input and validation
		int qty = 0;
		while (1)
		{
			printf("Enter Low Quantity threshhold: ");
			scanf_s("%d", &qty); while (getchar() != '\n');
			if (qty <= 0)
				printf("Invalid input. Try again.\n");
			else
				break;
		}
		
		//Print header in console
		printf("\t%-20s", "PART ID");
		printf("\t%-20s", "MODEL NAME");
		printf("\t%-20s", "SECTION NAME");
		printf("\t%-20s", "PART CODE");
		printf("\t%-20s", "PART NAME");
		printf("\t%-20s", "QUANTITY");
		printf("\t%-20s\n", "SUPPLIER NAME");

		//Print rows of parts data IF quantity < low quantity threshhold
		partCurr = partStart;
		while (partCurr != NULL)
		{
			if(partCurr->qty < qty)
			{
				printf("\t%-20s", partCurr->id);
				printf("\t%-20s", partCurr->modelName);
				printf("\t%-20s", partCurr->sectionName);
				printf("\t%-20s", partCurr->code);
				printf("\t%-20s", partCurr->name);
				printf("\t%-20d", partCurr->qty);
				printf("\t%-20s\n", partCurr->supplierName);
				
				totalMatchFound++;
			}
			partCurr = partCurr->next;
		}

		freePartList(); //Free part linked list
		
	}
	printf("Match Found: %d\n", totalMatchFound);
}

void readExistingModels()
{
	if (modelStart == NULL)
	{
		//Open File for reading
		FILE* file;
		if (fopen_s(&file, "carModels.txt", "r") != 0)
			return;

		fseek(file, 42, SEEK_SET); //Skip header row. 20 chars for code, 20 chars for name, 2 for newline char

		//Read the file until end of file. Each loop reads one row to one node of linked list
		//feof returns TRUE when the program tries to read a char after end of file
		//fgetc was used for that purpose
		while (fgetc(file) && !feof(file))
		{
			fseek(file, -1, SEEK_CUR); //Undo the action of fgetc inside while condition

			//Allocate memory for each model
			if (modelStart == NULL) //First node of linked list
				modelStart = modelCurr = (struct model*)malloc(sizeof(struct model));
			else					//Other nodes of linked list
			{
				modelCurr->next = (struct model*)malloc(sizeof(struct model));
				modelCurr = modelCurr->next;
			}

			//Read from file to linked list
			fgets(modelCurr->code, 21, file);
			fgets(modelCurr->name, 24, file);

			//Trim the empty spaces
			rtrim(modelCurr->code);
			rtrim(modelCurr->name);

			modelCurr->next = NULL; //Setting the 'next' to NULL is very important to indicate end of list
		}
		fclose(file);
	}
	return;
}

void addNewModel()
{
	//Allocate memory for new model
	if (modelStart == NULL)	//For the first node
		modelStart = modelCurr = (struct model*)malloc(sizeof(struct model));
	else					//For other nodes
	{
		modelCurr = modelStart;
		while (modelCurr->next != NULL)
			modelCurr = modelCurr->next;
		modelCurr->next = (struct model*)malloc(sizeof(struct model));
		modelCurr = modelCurr->next;
	}
	modelCurr->next = NULL; //Setting the 'next' to NULL is very important to indicate end of list

	//Model Code input and validation
	//Validations: Not empty, length >= 2, length <= 5, Unique, alpha
	char modelCode[25];
	int modelCodeValid = 1;
	do
	{
		modelCodeValid = 1;
		printf("Enter model code: ");
		gets_s(modelCode);
		strcpy_s(modelCode, upperCase(rtrim(modelCode)));
		if (strcmp(modelCode, "") == 0)
		{
			printf("Please provide a model code. Try again\n");
			modelCodeValid = 0;
			continue;
		}
		if (strlen(modelCode) > 5)
		{
			printf("Model code cannot be more than 5 characters long. Try again\n");
			modelCodeValid = 0;
			continue;
		}
		if (strlen(modelCode) < 2)
		{
			printf("Model code must be at least 2 characters long. Try again\n");
			modelCodeValid = 0;
			continue;
		}
		for (int i = strlen(modelCode) - 1; i >=  0 && modelCodeValid == 1; i--)
		{
			if (isalpha(modelCode[i]) == 0)
			{
				printf("Model code can only contain letters. Try again\n");
				modelCodeValid = 0;
				break;
			}
		}
		//Looking for duplicate
		modelCurr = modelStart;
		while (modelCurr->next != NULL && modelCodeValid == 1)
		{
			if (strcmp(modelCurr->code, modelCode) == 0)
			{
				printf("Invalid Input. Model code already exists. It must be unique. Try again\n");
				modelCodeValid = 0;
				break;
			}
			modelCurr = modelCurr->next;
		}
	} while (modelCodeValid == 0);
	strcpy_s(modelCurr->code, modelCode);

	//Model name input and validation
	//Validation: Not empty, must contain at least one letter
	int modelNameValid = 1;
	do
	{
		modelNameValid = 1;
		printf("Enter model name: ");
		gets_s(modelCurr->name);
		strcpy_s(modelCurr->name, rtrim(modelCurr->name));

		if (strcmp(modelCurr->name, "") == 0)
		{
			printf("Please provide a model name. Try again\n");
			modelNameValid = 0;
			continue;
		}
		for (int i = strlen(modelCurr->name) - 1; i >= 0; i--)
		{
			if (isalpha(modelCurr->name[i]) != 0)
			{
				modelNameValid = 1;
				break;
			}
			modelNameValid = 0;
		}
		if (modelNameValid == 0)
			printf("Invalid input. Try again\n");

	} while (modelNameValid == 0);

	//Create filename
	char filename[50];
	strcpy_s(filename, modelCurr->code);
	strcat_s(filename, ".txt");
	
	//Sort the last node 
	struct model* modelTemp = modelCurr, * modelPrev = NULL;

	modelCurr = modelStart;
	while (modelCurr != NULL)
	{
		if (strcmp(modelTemp->code, modelCurr->code) < 0) //If proper place of the last node is found
		{
			//Swap nodes
			modelTemp->next = modelCurr;
			if (modelCurr != modelStart)
				modelPrev->next = modelTemp;
			else
				modelStart = modelTemp;

			//Make the new last node 'next' to NULL
			modelCurr = modelStart;
			while (modelCurr != NULL)
			{
				if (modelCurr->next == modelTemp && modelCurr != modelPrev)
				{
					modelCurr->next = NULL;
					break;
				}
				modelCurr = modelCurr->next;
			}
			break;
		}
		modelPrev = modelCurr;
		modelCurr = modelCurr->next;
	}
	
	//Open carmodels.txt file
	FILE* file;
	if (fopen_s(&file, "carModels.txt", "w") != 0)
		return;

	//Write header into file
	fprintf(file, "%-20s", "CODE");
	fprintf(file, "%-20s", "NAME");

	//Write rows of model data into file
	modelCurr = modelStart;
	while (modelCurr != NULL)
	{
		fprintf(file, "%s", "\n");

		fprintf(file, "%-20s", modelCurr->code);
		fprintf(file, "%-20s", modelCurr->name);
		modelCurr = modelCurr->next; //Next model
	}
	fclose(file);

	//Create model file
	if (fopen_s(&file, filename, "w") == 0)
	{
		//Print header into file
		fprintf(file, "%-20s", "PART ID");
		fprintf(file, "%-20s", "MODEL CODE");
		fprintf(file, "%-20s", "MODEL NAME");
		fprintf(file, "%-20s", "SECTION CODE");
		fprintf(file, "%-20s", "SECTION NAME");
		fprintf(file, "%-20s", "PART CODE");
		fprintf(file, "%-20s", "PART NAME");
		fprintf(file, "%-20s", "QUANTITY");
		fprintf(file, "%-20s", "SUPPLIER CODE");
		fprintf(file, "%-20s", "SUPPLIER NAME");
		fclose(file);

		printf("%s created successfully.\n", filename);
	}
	return;
}

void getModelCode()
{
	if (modelStart == NULL)
		return;

	//Loop through model linked list and show all models
	printf("Available Models: \n");
	modelCurr = modelStart;
	while (modelCurr != NULL)
	{
		printf("\t%s. %s\n", modelCurr->code, modelCurr->name);
		modelCurr = modelCurr->next;
	}

	//Model code choice input and validation
	int matchFound = 0;
	char choice[25];
	do
	{
		printf("Choose Model Code: ");
		gets_s(choice);
		strcpy_s(choice, upperCase(choice));

		modelCurr = modelStart;
		while (modelCurr != NULL)
		{
			if (strcmp(modelCurr->code, choice) == 0)
			{
				matchFound = 1;
				break;
			}
			modelCurr = modelCurr->next;
		}
		if (matchFound == 0)
			printf("Invalid input. Try again.\n");

	} while (matchFound == 0);
}

void readExistingParts()
{
	if (modelStart == NULL)
		return;
	
	//Create filename
	FILE* file;
	char filename[50];
	strcpy_s(filename, modelCurr->code);
	strcat_s(filename, ".txt");
	
	//Open file
	if (fopen_s(&file, filename, "r") != 0)
	{
		printf("\nERROR. FILE NOT FOUND!.\n");
		return;
	}


	fseek(file, 202, SEEK_SET); //Skip header row. 200 chars for 10 columns, 2 chars for newline char

	//Read the file until end of file. Each loop reads one row to one node of linked list
	//feof returns TRUE when the program tries to read a char after end of file
	//fgetc was used for that purpose
	while (fgetc(file) && !feof(file))
	{
		fseek(file, -1, SEEK_CUR); //Undo the action of fgetc inside while condition

		//Allocate memory for each part
		if (partStart == NULL) //First node of linked list
			partStart = partCurr = (struct part*)malloc(sizeof(struct part));
		else				   //Other nodes of linked list
		{
			partCurr->next = (struct part*)malloc(sizeof(struct part));
			partCurr = partCurr->next;
		}
		
		//Read from file to linked list
		fgets(partCurr->id, 21, file);
		fgets(partCurr->modelCode, 21, file);
		fgets(partCurr->modelName, 21, file);
		fgets(partCurr->sectionCode, 21, file);
		fgets(partCurr->sectionName, 21, file);
		fgets(partCurr->code, 21, file);
		fgets(partCurr->name, 21, file);
		char qty_str[25];
		fgets(qty_str, 21, file); 
		fgets(partCurr->supplierCode, 21, file);
		fgets(partCurr->supplierName, 25, file);

		//Trim the empty spaces
		rtrim(partCurr->id);
		rtrim(partCurr->modelCode);
		rtrim(partCurr->modelName);
		rtrim(partCurr->sectionCode);
		rtrim(partCurr->sectionName);
		rtrim(partCurr->code);
		rtrim(partCurr->name);
		rtrim(qty_str);
		rtrim(partCurr->supplierCode);
		rtrim(partCurr->supplierName);

		partCurr->qty = atoi(qty_str); //Convert string to int for quantity

		partCurr->next = NULL; //Setting the 'next' to NULL is very important to indicate end of list
	}
	fclose(file);
	return;
}

void addNewPart()
{	
	getModelCode(); //Ask user for model choice input and modelCurr points to input model
	readExistingParts(); //Read all data from a file to linked list partStart
	
	if (modelStart == NULL)
	{
		printf("No available model. Please add a model first.\n");
		return;
	}

	if (modelCurr == NULL)
		return;
	
	//Allocate memory for the new part
	if (partStart == NULL) //For the first node
		partCurr = partStart = (struct part*)malloc(sizeof(struct part));
	else                   //Other nodes
	{
		while (partCurr->next != NULL)
			partCurr = partCurr->next;
		partCurr->next = (struct part*)malloc(sizeof(struct part));
		partCurr = partCurr->next;
	}
	partCurr->next = NULL; //Setting the 'next' to NULL is very important to indicate end of list

	//Copy model info of the new part
	strcpy_s(partCurr->modelCode, modelCurr->code); 
	strcpy_s(partCurr->modelName, modelCurr->name);

	//Show available sections
	printf("Available Section Code: \n");
	printf("\tBD. Body Work\n");
	printf("\tCS. Chassis\n");
	printf("\tEN. Engine\n");
	printf("\tTR. Transmission System\n");
	printf("\tOT. Others\n");

	//Section Code input and validation
	while(1)
	{
		printf("Choose Section Code: ");

		gets_s(partCurr->sectionCode);
		strcpy_s(partCurr->sectionCode, upperCase(rtrim(partCurr->sectionCode)));
		if (strcmp(partCurr->sectionCode, "BD") == 0)
		{
			strcpy_s(partCurr->sectionName, "Body Work");
			break;
		}
		if (strcmp(partCurr->sectionCode, "CS") == 0)
		{
			strcpy_s(partCurr->sectionName, "Chassis");
			break;
		}
		if (strcmp(partCurr->sectionCode, "EN") == 0)
		{
			strcpy_s(partCurr->sectionName, "Engine");
			break;
		}
		if (strcmp(partCurr->sectionCode, "TR") == 0)
		{
			strcpy_s(partCurr->sectionName, "Transmission System");
			break;
		}
		if (strcmp(partCurr->sectionCode, "OT") == 0)
		{
			strcpy_s(partCurr->sectionName, "Others");
			break;
		}
		
		printf("Invalid input. Try again.\n");
	}

	//Part code input and validation
	//Validations: Not empty, length >= 2, length <= 5, Unique, only alpha
	char partCode[25];
	int partCodeValid = 1;
	do
	{
		partCodeValid = 1;
		partCurr = partStart;
		printf("Enter part code: ");
		gets_s(partCode);
		strcpy_s(partCode, upperCase(partCode));

		if (strcmp(partCode, "") == 0)
		{
			printf("Please provide a part code. Try again\n");
			partCodeValid = 0;
			continue;
		}
		if (strlen(partCode) > 5)
		{
			printf("Part code cannot be more than 5 characters long. Try again\n");
			partCodeValid = 0;
			continue;
		}
		else if (strlen(partCode) < 2)
		{
			printf("Part code must be at least 2 characters long. Try again\n");
			partCodeValid = 0;
			continue;
		}
		for (int i = strlen(partCode) - 1; i >= 0 && partCodeValid == 1; i--)
		{
			if (isalpha(partCode[i]) == 0)
			{
				printf("Part code can only contain letters. Try again\n");
				partCodeValid = 0;
				break;
			}
		}
		//Looking for duplicate
		while (partCurr->next != NULL && partCodeValid == 1)
		{
			if (strcmp(partCurr->code, partCode) == 0)
			{
				printf("Invalid Input. Part code already exists. It must be unique. Try again\n");
				partCodeValid = 0;
				break;
			}

			partCurr = partCurr->next;
		}
	} while (partCodeValid == 0);
	strcpy_s(partCurr->code, partCode);
	
	//Generate ID using model code, section code, part code
	//Format: modelCode-sectionCode-partCode
	strcpy_s(partCurr->id, modelCurr->code);
	strcat_s(partCurr->id, "-");
	strcat_s(partCurr->id, partCurr->sectionCode);
	strcat_s(partCurr->id, "-");
	strcat_s(partCurr->id, partCurr->code);
	
	//part name input and validation
	//Validations: not empty, must contain at least one letter
	int partNameValid = 1;
	do
	{
		partNameValid = 1;
		printf("Enter Part Name: ");
		gets_s(partCurr->name);
		strcpy_s(partCurr->name, rtrim(partCurr->name));
		
		if (strcmp(partCurr->name, "") == 0)
		{
			printf("Please provide a part name. Try again\n");
			partNameValid = 0;
			continue;
		}
		
		for (int i = strlen(partCurr->name) - 1; i >= 0; i--)
		{
			if (isalpha(partCurr->name[i]) != 0)
			{
				partNameValid = 1;
				break;
			}
			partNameValid = 0;
		}
		if(partNameValid == 0)
			printf("Invalid input. Try again\n");
	} while (partNameValid == 0);

	//Part quantity input and validation
	while (1)
	{
		printf("Enter Part Quantity: ");
		scanf_s("%d", &partCurr->qty); while (getchar() != '\n');

		if (partCurr->qty < 1)
			printf("Invalid quantity. Try again.\n");
		else
			break;
	}
	
	//Supplier details
	char supplierExist, choiceSupplier[25];
	if (supplierStart == NULL)
		supplierExist = 'N';
	else
	{
		//Show all existing suppliers
		printf("Existing Suppliers:\n");

		supplierCurr = supplierStart;
		while (supplierCurr != NULL)
		{
			printf("\t%s. %s\n", supplierCurr->code, supplierCurr->name);
			supplierCurr = supplierCurr->next;
		}
		
		//Ask if supplier new or already exist
		while(1)
		{
			printf("Does your supplier already exist? [Y/N]: ");
			scanf_s("%c", &supplierExist); while (getchar() != '\n');
			if (supplierExist == 'y' || supplierExist == 'Y' || supplierExist == 'n' || supplierExist == 'N')
				break;
			printf("Invalid input. try again\n");
		}
	}

	//Option 1: Add a new supplier
	if (supplierExist == 'N' || supplierExist == 'n')
	{
		//Add new supplier and supplierCurr points to added supplier
		addNewSupplier();

		//Copy supplier details of the new part
		strcpy_s(partCurr->supplierCode, supplierCurr->code);
		strcpy_s(partCurr->supplierName, supplierCurr->name);
		
	}
	//Option 2: Choose existing supplier
	else if (supplierExist == 'Y' || supplierExist == 'y')
	{
		//Supplier code choice input and validation
		int matchFound = 0;
		do
		{
			printf("Choose supplier code: ");
			gets_s(choiceSupplier);
			strcpy_s(choiceSupplier, upperCase(choiceSupplier));
			supplierCurr = supplierStart;
			while (supplierCurr != NULL)
			{
				if (strcmp(supplierCurr->code, choiceSupplier) == 0)
				{
					matchFound = 1;
					strcpy_s(partCurr->supplierCode, supplierCurr->code);
					strcpy_s(partCurr->supplierName, supplierCurr->name);
					break;
				}
				supplierCurr = supplierCurr->next;
			}
			if (matchFound == 0)
				printf("Invalid input. Try again.\n");
		} while (matchFound == 0);
	}

	//Sort the last node of the part linked list
	struct part* partTemp = partCurr, * partPrev = NULL;

	partCurr = partStart;
	while (partCurr != NULL)
	{
		if (strcmp(partTemp->id, partCurr->id) < 0) //If proper place of the last node is found
		{
			//Swap nodes
			partTemp->next = partCurr;
			if (partCurr != partStart)
				partPrev->next = partTemp;
			else
				partStart = partTemp;

			//Make the new last node 'next' to NULL
			partCurr = partStart;
			while (partCurr != NULL)
			{
				if (partCurr->next == partTemp && partCurr != partPrev)
				{
					partCurr->next = NULL;
					break;
				}
				partCurr = partCurr->next;
			}
			break;
		}
		partPrev = partCurr;
		partCurr = partCurr->next;
	}
	
	//Create filename for model
	char filename[50];
	strcpy_s(filename, modelCurr->code);
	strcat_s(filename, ".txt");

	//Open model file to write the updated, sorted part list
	FILE* file;
	if (fopen_s(&file, filename, "w") != 0)
	{
		printf("ERROR!");
		return;
	}

	//Write header into file
	fprintf(file, "%-20s", "PART ID");
	fprintf(file, "%-20s", "MODEL CODE");
	fprintf(file, "%-20s", "MODEL NAME");
	fprintf(file, "%-20s", "SECTION CODE");
	fprintf(file, "%-20s", "SECTION NAME");
	fprintf(file, "%-20s", "PART CODE");
	fprintf(file, "%-20s", "PART NAME");
	fprintf(file, "%-20s", "QUANTITY");
	fprintf(file, "%-20s", "SUPPLIER CODE");
	fprintf(file, "%-20s", "SUPPLIER NAME");

	//Write rows of parts data
	partCurr = partStart;
	while (partCurr != NULL)
	{
		fprintf(file, "\n");
		fprintf(file, "%-20s", partCurr->id);
		fprintf(file, "%-20s", partCurr->modelCode);
		fprintf(file, "%-20s", partCurr->modelName);
		fprintf(file, "%-20s", partCurr->sectionCode);
		fprintf(file, "%-20s", partCurr->sectionName);
		fprintf(file, "%-20s", partCurr->code);
		fprintf(file, "%-20s", partCurr->name);
		fprintf(file, "%-20d", partCurr->qty);
		fprintf(file, "%-20s", partCurr->supplierCode);
		fprintf(file, "%-20s", partCurr->supplierName);

		partCurr = partCurr->next;
	}
	fclose(file);

	printf("\n%s added successfully.\n", partTemp->name);
	freePartList(); //Free part linked list
	return;
}

void readExistingSuppliers()
{
	if (supplierStart == NULL)
	{
		//Open supplier file to read
		FILE* file;
		if (fopen_s(&file, "suppliers.txt", "r") != 0)
			return;

		fseek(file, 42, SEEK_SET);  //Skip header row. 20 chars for code, 20 chars for name, 2 chars for newline char
		
		//Read the file untile end of file. Each loop reads one row to one node of linked list
		//feof returns TRUE when the program tries to read a char after end of file
		//fgetc was used for that purpose
		while (fgetc(file) && !feof(file))
		{
			fseek(file, -1, SEEK_CUR); //Undo the action of fgetc inside while condition

			//Allocate memory for each supplier
			if (supplierStart == NULL) //First node of linked list
				supplierStart = supplierCurr = (struct supplier*)malloc(sizeof(struct supplier));
			else						//Other nodes of linked list
			{
				supplierCurr->next = (struct supplier*)malloc(sizeof(struct supplier));
				supplierCurr = supplierCurr->next;
			}
			
			//Read from file to linked list
			fgets(supplierCurr->code, 21, file);
			fgets(supplierCurr->name, 50, file);

			//Trim the empty spaces
			rtrim(supplierCurr->code);
			rtrim(supplierCurr->name);

			supplierCurr->next = NULL; //Setting the 'next' to NULL is very important to indicate end of list
		}
		fclose(file);
	}
	return;
}

void addNewSupplier()
{
	//Allocate memory for new supplier
	if (supplierStart == NULL) //First node
		supplierCurr = supplierStart = (struct supplier*)malloc(sizeof(struct supplier));
	else                       //Other nodes
	{
		supplierCurr = supplierStart;
		while (supplierCurr->next != NULL)
			supplierCurr = supplierCurr->next;
		supplierCurr->next = (struct supplier*)malloc(sizeof(struct supplier));
		supplierCurr = supplierCurr->next;
	}
	supplierCurr->next = NULL; //Setting the 'next' to NULL is very important to indicate end of list

	//Supplier code input and validation
	//Validations: Not empty, length >= 2, length <= 5, Unique, only alpha
	int supplierCodeValid = 1;
	char supplierCode[25];
	do
	{
		supplierCodeValid = 1;

		printf("Enter supplier code: ");
		gets_s(supplierCode);
		strcpy_s(supplierCode, upperCase(supplierCode));
		if (strcmp(supplierCode, "") == 0)
		{
			printf("Please provide a supplier code. Try again\n");
			supplierCodeValid = 0;
			continue;
		}
		if (strlen(supplierCode) > 5)
		{
			printf("Supplier code cannot be more than 5 characters long. Try again\n");
			supplierCodeValid = 0;
			continue;
		}
		if (strlen(supplierCode) < 2)
		{
			printf("Supplier code must be at least 2 characters long. Try again\n");
			supplierCodeValid = 0;
			continue;
		}
		for (int i = strlen(supplierCode) - 1; i >= 0 && supplierCodeValid == 1; i--)
		{
			if (isalpha(supplierCode[i]) == 0)
			{
				printf("Supplier code can only contain letters. Try again\n");
				supplierCodeValid = 0;
				break;
			}
		}
		//Looking for duplicate
		supplierCurr = supplierStart;
		while (supplierCurr->next != NULL && supplierCodeValid == 1)
		{
			if (strcmp(supplierCurr->code, supplierCode) == 0)
			{
				printf("Invalid Input. Supplier code already exists. It must be unique. Try again\n");
				supplierCodeValid = 0;
				break;
			}

			supplierCurr = supplierCurr->next;
		}
	} while (supplierCodeValid == 0);
	strcpy_s(supplierCurr->code, supplierCode);

	//Supplier name input and validation
	//Validations: not empty, must contain at least one letter
	int supplierNameValid = 1;
	do
	{
		supplierNameValid = 1;
		printf("Enter Supplier Name: ");
		gets_s(supplierCurr->name);
		strcpy_s(supplierCurr->name, rtrim(supplierCurr->name));

		if (strcmp(supplierCurr->name, "") == 0)
		{
			printf("Please provide a supplier name. Try again\n");
			supplierNameValid = 0;
			continue;
		}
		for (int i = strlen(supplierCurr->name) - 1; i >= 0; i--)
		{
			if (isalpha(supplierCurr->name[i]) != 0)
			{
				supplierNameValid = 1;
				break;
			}
			supplierNameValid = 0;
		}
		if (supplierNameValid == 0)
			printf("Invalid input. Try again\n");
	} while (supplierNameValid == 0);

	//Sort last node of the supplier linked list
	struct supplier* supplierTemp = supplierCurr, * supplierPrev = NULL;
	supplierCurr = supplierStart;
	while (supplierCurr != NULL)
	{
		if (strcmp(supplierTemp->code, supplierCurr->code) < 0) //If proper place of the last node is found
		{
			//Swap nodes
			supplierTemp->next = supplierCurr;
			if (supplierCurr != supplierStart)
				supplierPrev->next = supplierTemp;
			else
				supplierStart = supplierTemp;

			//Make the new last node 'next' to NULL
			supplierCurr = supplierStart;
			while (supplierCurr != NULL)
			{
				if (supplierCurr->next == supplierTemp && supplierCurr != supplierPrev)
				{
					supplierCurr->next = NULL;
					break;
				}
				supplierCurr = supplierCurr->next;
			}
			break;
		}
		supplierPrev = supplierCurr;
		supplierCurr = supplierCurr->next;
	}

	//Open supplier file to write updated, sorted supplier linked list
	FILE* file;
	if (fopen_s(&file, "suppliers.txt", "w") != 0)
	{
		printf("ERROR!");
		return;
	}

	//Write header into file
	fprintf(file, "%-20s", "SUPPLIER CODE");
	fprintf(file, "%-20s", "SUPPLIER NAME");

	//Write rows of supplier data into file
	supplierCurr = supplierStart;
	while (supplierCurr != NULL)
	{
		fprintf(file, "\n%-20s", supplierCurr->code);
		fprintf(file, "%-20s", supplierCurr->name);
		supplierCurr = supplierCurr->next;
	}
	fclose(file);

	supplierCurr = supplierTemp;
}

void deleteModel()
{
	if (modelStart == NULL)
	{
		printf("No available models. Add a model first.\n");
		return;
	}

	getModelCode(); //Ask user for model choice input and modelCurr points to input model

	//Delete confirmation input
	printf("All the data related to %s (%s) will be deleted.\n", modelCurr->name, modelCurr->code);
	printf("Are you sure you want to continue? [Y/N]: ");
	
	char confirmDelete = NULL;
	scanf_s("%c", &confirmDelete);

	//Delete the model
	if (confirmDelete == 'y' || confirmDelete == 'Y')
	{
		//Create filename using model code
		char filename[50];
		strcpy_s(filename, modelCurr->code);
		strcat_s(filename, ".txt");

		//delete node from linked list
		if (strcmp(modelStart->code, modelCurr->code) == 0) //If selected node is first node
		{
			modelStart = modelStart->next;
			free(modelCurr);
			modelCurr = modelStart;
		}
		else
		{
			struct model* modelPrev = modelStart;
			while (strcmp(modelPrev->next->code, modelCurr->code) != 0)
				modelPrev = modelPrev->next;
			modelPrev->next = modelCurr->next;
			free(modelCurr);
			modelCurr = modelStart;
		}
		
		//Open file to write updated model linked list into file
		FILE* file;
		if (fopen_s(&file, "carModels.txt", "w") != 0)
			return;

		//Write header into file
		fprintf(file, "%-20s", "CODE");
		fprintf(file, "%-20s", "NAME");

		//Write rows of model data into file
		while (modelCurr != NULL)
		{
			fprintf(file, "\n");
			fprintf(file, "%-20s", modelCurr->code);
			fprintf(file, "%-20s", modelCurr->name);
			modelCurr = modelCurr->next;
		}
		fclose(file);
		
		//Delete model file
		if (remove(filename) == 0)
			printf("%s has been deleted successfully.\n", filename);
	}
	else
		printf("Delete process cancelled.\n");
	
}

void deletePart()
{
	if (modelStart == NULL)
	{
		printf("No available models. Add a model first.\n");
		return;
	}
	getModelCode(); //Ask user for model choice input and modelCurr points to input model
	readExistingParts(); //Read all data from a file to linked list partStart

	if (modelCurr == NULL)
		return;

	if (partStart == NULL)
	{
		printf("No available parts for this model. Add a part first.\n");
		return;
	}
	
	printf("Available Parts:\n");

	//Print header rows to console
	printf("\t%-20s", "PART ID");
	printf("\t%-20s", "MODEL NAME");
	printf("\t%-20s", "SECTION NAME");
	printf("\t%-20s", "PART CODE");
	printf("\t%-20s", "PART NAME");
	printf("\t%-20s", "QUANTITY");
	printf("\t%-20s\n", "SUPPLIER NAME");

	//Print rows of parts data 
	partCurr = partStart;
	while (partCurr != NULL)
	{
		printf("\t%-20s", partCurr->id);
		printf("\t%-20s", partCurr->modelName);
		printf("\t%-20s", partCurr->sectionName);
		printf("\t%-20s", partCurr->code);
		printf("\t%-20s", partCurr->name);
		printf("\t%-20d", partCurr->qty);
		printf("\t%-20s\n", partCurr->supplierName);
		partCurr = partCurr->next;
	}

	//Part code choice input and validation
	int matchFound = 0;
	char choicePart[25];
	do
	{
		printf("Choose Part Code: ");

		gets_s(choicePart);
		strcpy_s(choicePart, upperCase(choicePart));

		partCurr = partStart;
		while (partCurr != NULL)
		{
			if (strcmp(partCurr->code, choicePart) == 0)
			{
				matchFound = 1;
				break;
			}
			partCurr = partCurr->next;
		}
		if (matchFound == 0)
			printf("Invalid input. Try again.\n");

	} while (matchFound == 0);
	
	//Delete confirmation input
	printf("All the data related to %s (%s) of %s (%s) will be deleted.\n", partCurr->name, partCurr->code, modelCurr->name, modelCurr->code);
	printf("Are you sure you want to continue? [Y/N]: ");
	char confirmDelete = NULL;
	scanf_s("%c", &confirmDelete);

	//Delete part
	if (confirmDelete == 'Y' || confirmDelete == 'y')
	{
		//Delete the node
		if (strcmp(partStart->code, partCurr->code) == 0) // selected part is the first member of linked list
		{
			partStart = partStart->next;
			free(partCurr);
			partCurr = partStart;
		}
		else
		{
			struct part* partPrev = partStart;
			while (strcmp(partPrev->next->code, partCurr->code) != 0)
				partPrev = partPrev->next;
			partPrev->next = partCurr->next;
			free(partCurr);
			partCurr = partStart;
		}

		//Create filename
		char filename[50];
		strcpy_s(filename, modelCurr->code);
		strcat_s(filename, ".txt");

		//Open file to write updated part linked list into file
		FILE* file;
		if (fopen_s(&file, filename, "w") != 0)
		{
			printf("ERROR. File not found.\n");
			return;
		}

		//Write header into file
		fprintf(file, "%-20s", "PART ID");
		fprintf(file, "%-20s", "MODEL CODE");
		fprintf(file, "%-20s", "MODEL NAME");
		fprintf(file, "%-20s", "SECTION CODE");
		fprintf(file, "%-20s", "SECTION NAME");
		fprintf(file, "%-20s", "PART CODE");
		fprintf(file, "%-20s", "PART NAME");
		fprintf(file, "%-20s", "QUANTITY");
		fprintf(file, "%-20s", "SUPPLIER CODE");
		fprintf(file, "%-20s", "SUPPLIER NAME");

		//Write rows of parts data into file
		partCurr = partStart;
		while (partCurr != NULL)
		{
			fprintf(file, "\n");
			fprintf(file, "%-20s", partCurr->id);
			fprintf(file, "%-20s", partCurr->modelCode);
			fprintf(file, "%-20s", partCurr->modelName);
			fprintf(file, "%-20s", partCurr->sectionCode);
			fprintf(file, "%-20s", partCurr->sectionName);
			fprintf(file, "%-20s", partCurr->code);
			fprintf(file, "%-20s", partCurr->name);
			fprintf(file, "%-20d", partCurr->qty);
			fprintf(file, "%-20s", partCurr->supplierCode);
			fprintf(file, "%-20s", partCurr->supplierName);

			partCurr = partCurr->next;
		}
		fclose(file);
		printf("Delete Process Successful\n");
	}
	else
		printf("Delete Process Cancelled.\n");

	freePartList(); //Free parts linked list 
}

char* rtrim(char* str) 
{
	//Loop through the string character by character from end to beginning
	for (int i = strlen(str) - 1; i >= 0; i--)
	{
		if (str[i] != ' ' && str[i] != '\n')	//If end of empty spaces or new line char found
		{
			str[i + 1] = '\0'; //End the string by putting null char
			break;
		}
	}
	return str;
}

void freeModelList()
{
	if (modelStart == NULL) //IF the list is empty already
		modelCurr = NULL;

	else if (modelStart->next == NULL) //If there there is only one node
	{
		free(modelStart);
		modelStart = modelCurr = NULL;
	}
	else //If list has two or more nodes
	{
		//Delete nodes from beginning to end
		while (modelStart != NULL)
		{
			modelCurr = modelStart;
			modelStart = modelStart->next;
			free(modelCurr);
		}
		modelCurr = modelStart = NULL;
	}
}

void freeSupplierList()
{
	if (supplierStart == NULL) //IF the list is empty already
		supplierCurr = NULL;
	else if (supplierStart->next == NULL) //If there there is only one node
	{
		free(supplierStart);
		supplierStart = supplierCurr = NULL;
	}
	else //If list has two or more nodes
	{
		//Delete nodes from beginning to end
		while (supplierStart != NULL)
		{
			supplierCurr = supplierStart;
			supplierStart = supplierStart->next;
			free(supplierCurr);
		}
		supplierCurr = supplierStart = NULL;
	}
}

void freePartList()
{
	if (partStart == NULL) //IF the list is empty already
		partCurr = NULL;
	else if (partStart->next == NULL) //If there there is only one node
	{
		free(partStart);
		partStart = partCurr = NULL;
	}
	else //If list has two or more nodes
	{
		//Delete nodes from beginning to end
		while(partStart != NULL)
		{
			partCurr = partStart;
			partStart = partStart->next;
			free(partCurr);
		}
		partCurr = partStart = NULL;
	}
}

char* upperCase(char* str)
{
	//Loop through characters of the string from end to beginning
	for (int i = strlen(str) - 1; i >= 0; i--)
		str[i] = toupper(str[i]);

	return str;
}

char* lowerCase(char* str)
{
	//Loop through characters of the string from end to beginning
	for (int i = strlen(str) - 1; i >= 0; i--)
		str[i] = tolower(str[i]);

	return str;
}
