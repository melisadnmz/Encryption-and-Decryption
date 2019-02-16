//Melisa Dönmez 150116030

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

typedef struct Dictionary{
	char word[50];
	struct Dictionary *next;
	
}dictionary;

int solveEquation(int a,int b, int y);

//Calculate order in alphabet of decrypt letter 
int calculateMode(int a, int b, int x){
    int y = (a * x + b) % 26;
    return y;
}

//Create alphabet array for lower case letter
char encryptyOrDecryptLetter(int y){

    char arr[27];
    int i;

    for(i=0; i<26; i++)
    {
        arr[i] = 'a'+i;
    }

    return arr[y];

}
//Create alphabet array for uppper case letter
char encryptyOrDecryptLetter2(int y){

    char arr[27];
    int i;

    for(i=0; i<26; i++)
    {
        arr[i] = 'A'+i;
    }

    return arr[y];
}



int main(void) {
	dictionary *current, *head,*head2,*current2;
	head = current = NULL;
	head2 = current2 = NULL;
	
    
    FILE *file,*file2;
    char ch;
    int num;
    int a,b;
    srand ( time(NULL) );
    a = ((rand() % 11) + 1) * 2 + 1;
    if (a == 13){
        a = 25;
    }
    b = rand() % (25 + 1 - 0) + 0;
   
    printf("Random value a = %d  and b = %d ", a,b);

    file = fopen("C:\\Users\\Melis\\Desktop\\input1.txt", "r");
    file2 = fopen("C:\\Users\\Melis\\Desktop\\encryptInput1.txt", "w");


    if (file == NULL) {
        printf("Could not open file1\n");
        exit(1);
    }

    if (file2 == NULL) {
        printf("Could not open file\n");
        exit(1);
    }

//Read txt file and Encrypt text   
    int y;
    char Letter;
	 while( (ch = fgetc(file)) != EOF ) {

//Check letter upper or lower case
        if (ch >= 'A' && ch <= 'Z'){
            num = ch - 'A';
            y = calculateMode(a,b,num);
            //Find encrypt letter
            Letter = encryptyOrDecryptLetter2(y);
            putc(Letter, file2);

        }
        else if (ch >= 'a' && ch <= 'z') {
            num = ch - 'a';
            y = calculateMode(a, b, num);
            //Find encrypt letter
            Letter = encryptyOrDecryptLetter(y);
            putc(Letter, file2);
        }
        else{
            putc(ch, file2);
        }


    }
    // close file
    fclose(file);

    // close file
    fclose(file2);

  //Find the total number of words in unencrypted text
    FILE *file5;
    file5 = fopen("C:\\Users\\Melis\\Desktop\\input1.txt", "r");
    int numberTotal = 0;
    char word[100];
    if (file5 == NULL) {
        printf("Could not open file5\n");
        exit(1);
    }
    while(fscanf(file5, "%s", word) != EOF)
    {
       numberTotal++;

    }
    
    fclose(file5);
    
    FILE *file4;
    file4 = fopen("C:\\Users\\Melis\\Desktop\\dictionary.txt", "r");
    char word2[100];
    
    
	if (file4 == NULL) {
    printf("Could not open file4\n");
    exit(1);
    }
    
    else{
	while(fscanf(file4, "%s", word2) != EOF){
    	dictionary *node = malloc(sizeof(dictionary));
    	dictionary *node2 = malloc(sizeof(dictionary));
        strcpy(node->word,word2);//note : strdup is not standard function
        node->next =NULL;

        if(head == NULL){
            current = head = node;
        } else {
            current = current->next = node;
        }
        if(strcmp(word2,"like")>0){
        dictionary *node2 = malloc(sizeof(dictionary));
        strcpy(node2->word,word2);//note : strdup is not standard function
        node2->next =NULL;

        if(head2 == NULL){
            current2 = head2 = node2;
        } else {
            current2 = current2->next = node2;
        }
        	
		}
    }
}
    fclose(file4);

    
    
	
	//Try to solve encrypted with using brute force method
    FILE *file3;
	int a2,b2,y2,x2;
    char ch2,Letter2;
    a2 = 1;
    int numberSame = 0;

    char word3[100];
    while(a2 < 26) {
       for (b2 = 0; b2 < 26; b2++) {
       	dictionary *temp;
            temp = head;
            int k = 0;

            file3 = fopen("C:\\Users\\Melis\\Desktop\\encryptInput1.txt", "r");
            if (file3 == NULL) {
                printf("Could not open file3\n");
                exit(1);
            }

            while ((ch2 = fgetc(file3)) != EOF && k <= 100) {
            	

                if (ch2 >= 'A' && ch2 <= 'Z') {
                    y2 = ch2 - 'A';
                    x2 = solveEquation(a2, b2, y2);
                    Letter2 = encryptyOrDecryptLetter2(x2);
					
					int len = strlen(word3);
                    word3[len] = Letter2;
                    word3[len+1] = '\0';

                } else if (ch2 >= 'a' && ch2 <= 'z') {
                    y2 = ch2 - 'a';
                    x2 = solveEquation(a2, b2, y2);
                    Letter2 = encryptyOrDecryptLetter(x2);


                        int len = strlen(word3);
                        word3[len] = Letter2;
                        word3[len+1] = '\0';

                } else {
                	//compare dictionary with decoded word
                    if(ch2 == ' '){
                    	k++;
                    	if(strcmp(word3,"like")>0){
                    		temp = head2;
						}
                    	while(temp != NULL){
        
                            if(strcasecmp(temp->word, word3) == 0)
                            {
                                numberSame++;
                                break;
                            }
                            temp = temp->next;
                        }
						strcpy(word3,"");
                        temp = head;
                       }
					}
        }
    
            fclose(file3);
             if((double)numberSame/k > (double)60/100){
             	
              printf("\na and b found a = %d b = %d", a2,b2);
             exit(0);
			}
            
            numberSame = 0;
            k = 0;
			}

        a2 = a2 + 2;
        if (a2 == 13) {
            a2 = 15;
        }
		}
		return 0;
}


int solveEquation(int a,int b,int y) {

    int z,x;
    for(z = 0; z < 26; z++){
        if((a*z)%26 == 1){
            x = (z*(y-b))%26;

        }
        if(x < 0){
            x = x + 26;
        }
    }
return x;
}
