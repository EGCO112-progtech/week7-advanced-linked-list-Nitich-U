
// self-referential structure
struct Node {
   int data; // each listNode contains a character
   char name[50];
   struct Node *nextPtr; // pointer to next node
   struct Node *pPtr;
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes

int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int value ,const char *name);
void printList( LLPtr currentPtr );
void instructions( void );
void freeList(LLPtr *sPtr);


// display program instructions to user
void instructions( void )
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int value ,const char *name ) {
   LLPtr newPtr; 
   LLPtr previousPtr; 
   LLPtr currentPtr;  

   newPtr = (LLPtr)malloc(sizeof(LLnode)); // create node

   if (newPtr != NULL) { 
       newPtr->data = value;
       strcpy(newPtr->name, name); 
       newPtr->nextPtr = NULL;  
       newPtr->pPtr = NULL;  
       previousPtr = NULL;
       currentPtr = *sPtr;

      
       while (currentPtr != NULL && value > currentPtr->data) {
           previousPtr = currentPtr; 
           currentPtr = currentPtr->nextPtr; 
       }

       
       if (previousPtr == NULL) {
           newPtr->nextPtr = *sPtr;
           if (*sPtr != NULL) {
               (*sPtr)->pPtr = newPtr;  
           }
           *sPtr = newPtr;
       } // end if
       else {  // inset new node between previousPtr and currentPtr
           previousPtr->nextPtr = newPtr;
           newPtr->pPtr = previousPtr;
           
           newPtr->nextPtr = currentPtr;
           if (currentPtr != NULL) {
               currentPtr->pPtr = newPtr; 
           }
       }
   } 
   else {
       printf("%d not inserted. No memory available.\n", value);
   }
}


// delete a list element
int deletes(LLPtr *sPtr, int value) {
   LLPtr previousPtr; 
   LLPtr currentPtr; 
   LLPtr tempPtr; 


   if (*sPtr != NULL && value == (*sPtr)->data) {
       tempPtr = *sPtr; 
       *sPtr = (*sPtr)->nextPtr; 
       if (*sPtr != NULL) {
           (*sPtr)->pPtr = NULL;  
       }
       free(tempPtr);
       return value;
   } 
   else {
       previousPtr = *sPtr;
       currentPtr = (*sPtr)->nextPtr;

       
       while (currentPtr != NULL && currentPtr->data != value) {
           previousPtr = currentPtr; 
           currentPtr = currentPtr->nextPtr;
       }

       if (currentPtr != NULL) {
           tempPtr = currentPtr;
           previousPtr->nextPtr = currentPtr->nextPtr;

           if (currentPtr->nextPtr != NULL) {
               currentPtr->nextPtr->pPtr = previousPtr;
           }

           free(tempPtr);
           return value;
       }
   }

   return '\0';
}

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr )
{
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else {
      puts( "The list is:" );

      // while not the end of the list
      while ( currentPtr->nextPtr!= NULL ) {
         printf( "%d %s -->", currentPtr->data , currentPtr->name);
         currentPtr = currentPtr->nextPtr;
      } // end while

      printf( "%d %s -->NULL\n",currentPtr->data , currentPtr->name);
       

     
       
   } // end else
}
void printListReverse( LLPtr currentPtr )
   {
      if ( isEmpty( currentPtr ) ) {
         puts( "List is empty.\n" );
      } 
      else {
         
         while ( currentPtr->nextPtr != NULL ) {
            currentPtr = currentPtr->nextPtr;
         }
   
         puts( "The reversed list is:" );
   
         
         while ( currentPtr != NULL ) {
            printf( "%d %s-->", currentPtr->data , currentPtr->name);
            currentPtr = currentPtr->pPtr; 
         }
   
         puts( "NULL" );
      }
   }

void freeList(LLPtr *sPtr) {
       LLPtr tempPtr;
       while (*sPtr != NULL) {
           tempPtr = *sPtr;
           *sPtr = (*sPtr)->nextPtr;
           printf("delete %d \n",tempPtr->data);
           free(tempPtr);
       }
}