#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include <ctype.h>

#define HARD 2
#define EASY 1
#define INVALID 0


// defining  structure & its functions.
typedef struct node
{
    char word[20];
    struct node *next;

}node;

node *init_list()
{
    node* head = malloc(sizeof(node));
    head -> next = NULL;
    strcpy(head ->word, "start");

    return head;
}

node *push_front(node *head, char word[20])
{
    node *p = malloc(sizeof(node));

    p->next = head;
    strcpy(p->word, word);
    head = p;

    return head;
}

node *push_back(node *head, char word[20])
{
    node *p;

    if (head == NULL)
        return push_front(head, word);


    for(p=head; p->next != NULL; p=p->next);
    p->next = malloc(sizeof(node));
    p->next->next = NULL;
    strcpy(p->next->word, word);


    return head;
}

node *delete_list(node *head)
{
    if (head == NULL)
    {
        printf("there is nothing to free!");
    }


    node *tmp = head;
    while (tmp != NULL)
    {
        tmp = tmp->next;
        free(head);
        head=tmp;
    }
    tmp = NULL;
    return head;
}




void get_random_word(node *head, char *words, int word_len)
{
    int counter = 0;
    node *p = head;
    while (p != NULL)
    {
        if(strlen(p->word) == word_len)
            {counter++;}

      p = p->next;
    }

    srand(time(NULL));
    int selected = rand() % counter +1 ;

    int another_counter = 0;

    node *q = head;
    while (q != NULL)
    {
      if(strlen(q->word) == word_len)
        {
            another_counter++;
            if (another_counter == selected)
                {strcpy(words, q->word);}
        }
        q = q->next;
    }
}


void play_game(char *choice)
 {
    printf("The selected word to play is: %s\n", choice);   /* Temporary for testing purposes */
    return;
 }


void update_word(char word[20], char letter, char *current_guessed_word)/*update the word with all occurrences of the entered character */
{
    int len = strlen(word);
    for (int i=0; i<len; i++)
     {
       if (word[i] == letter)
         {
            current_guessed_word[i] = letter;
         }
     }
}


int is_in_word(char word[], char letter) //function to check if the passed letter is in the word
{
    int counter = 0;
    int len = strlen(word);

    for (int i=0; i<len; i++)
    {
        if (word[i] == letter)
        {
            counter++;
        }
    }

    if (counter > 0) {return 1;}
    else return 0;
}


void print(char string[])//function to print the string
{
    int length = strlen(string);

    for (int i=0; i<length; i++)
      {
        printf("%c ", string[i]); // to print the string with spaces -> t e s t
      }
}


void generate_dashes(int length, char str[])// function to generate dashes as much as the letters in the word.
{
    for (int i=0; i<length; i++)
      {
        str[i] = '_'; // fill the string with dashes
      }

    for (int i=0; i<length; i++)
      {
        printf("%c ", str[i]);
      }
}


int choose_difficulty()// function returns number of misses allowed per one game, and ask the user for difficulty "easy" or "hard".
{
    int difficulty;
    printf("please choose the difficulty -> Type (1) for Easy ... (2) for Hard: ");
    fflush(stdin);
    scanf("%d", &difficulty);

    if (difficulty == 1)
      {
        printf("\nYou have 10 misses, Try not to lose!\n\n");
        return EASY;
      }

    else if (difficulty == 2)
      {
        printf("\nYou have 5 misses, Try not to lose!\n\n");
        return HARD;
      }

    else //detect if the user inserted an invalid input, then let the user choose again.
      {
        printf("\ninvalid input! please choose again\n\n");
        choose_difficulty();
      }
}


int already_guessed (char letter, char array[])// This function is to check if a given letter is in the string or not, it returns 1 if the letter existed, 0 if the letter is not in the word.
{
    int len = strlen(array);
    int counter = 0;

    for (int i =0; i<len; i++)
     {
        if (letter == array[i])
         { counter++;}
     }

    if (counter > 0)
        { return 1; }

    else
        { return 0; }
}


int get_word_length() //to check if the user entered a valid number
{
    int len;
    printf("\nEnter the length of the word: ");
    scanf("%d", &len);

    if ((len >= 3 && len <= 16))
    {
        return len;
    }

    else
    {
        printf("Invalid input! please enter a number between 3 - 16!\n");
        fflush(stdin);
        get_word_length();
    }
}


void run_game(node *head)
{
        int word_length = get_word_length();


        char word[20];

        get_random_word(head, word, word_length); // calling the function to generate a random word.

        play_game(word); // Function to display the word to the screen "" ONLY FOR TESTING THE PROGRAM ""

        char *current_guessed_letters = (char *)malloc((word_length+1) * sizeof(char));//memory allocated array to store the word after guessing and replace the dashes with the word letters.
        current_guessed_letters[word_length] = '\0';// because indexing starts from 0 the last index of the the array will be the word length number.


        int difficulty = choose_difficulty(); //prints the difficulties available to the screen and lets the user choose


        int size;
        if (difficulty == HARD)
        {
            size = 5; // this is the size of the missed letters array, to store 5 letters if the player chose hard
        }

        if (difficulty == EASY)
        {
            size = 10; // this is the size of the missed letters array, to store 10 letters if the player chose easy
        }


        int number_of_misses = 0;
        char *missed_letters = (char *)malloc( size * sizeof(char) );// memory allocated array to store the missed letters
        missed_letters[0] = '\0';

        printf("\nPlease enter one letter at a time!\n");

        generate_dashes(word_length, current_guessed_letters);// generate dashes as many letters in the word

        char guessed_letter;
        printf("\n\n-Guess a letter: ");
        scanf(" %c", &guessed_letter);

        guessed_letter = tolower(guessed_letter);

        while ( guessed_letter != '~')
        {

            if (is_in_word(word, guessed_letter)) // if the letter guessed was in the word, the program prints the dashes and replace the dash with the correct guessed letter
               {
                    update_word(word, guessed_letter, current_guessed_letters);
                    print(current_guessed_letters);
               }

            else //if the letter was not in the word

              {
                 if (already_guessed(guessed_letter, missed_letters)) //check if the user already missed that letter.

                    {
                        printf("\nYou already missed letter (%c)! take another guess..\n", guessed_letter);

                        print(current_guessed_letters);
                        printf("  misses: ");
                        print(missed_letters);
                    }

                 else //if the user incorrectly guessed -> 1. number of misses is incremented 2. print the missed letter to the screen.
                     {
                        missed_letters[number_of_misses] = guessed_letter;
                        missed_letters[number_of_misses+1] = '\0';
                        number_of_misses++;

                        printf("\n-Number of misses: %d\n\n", number_of_misses);
                        print(current_guessed_letters);
                        printf("   missed letters: ");
                        print(missed_letters);

                        if ( (difficulty == EASY && number_of_misses == 10) || (difficulty == HARD && number_of_misses == 5) ) // if the user chose "easy" and had 10 misses then they lose, if "hard" and 5 misses they lose too.
                           {
                               printf("\n\nHard Luck!\n");
                               printf("you lost .. \n");
                               printf("the secret word is: %s\n\n", word);
                               break;
                           }
                     }
               }

            // check if the word is completed or not by comparing the generated word and the current guessing status of the user
            // if strcmp returns (0) then the word is completed and the user wins, else the program will continue the loop.
            if (strcmp (word, current_guessed_letters) == 0)
               {
                 printf("\n\nYou successfully guessed all the letters!\n\nYou Win!!\n");
                 printf("\nYou are right secret word is: %s\n\n", word);
                 break;
               }


              printf("\n\n-Guess: ");
              scanf(" %c", &guessed_letter);
              guessed_letter = tolower(guessed_letter);

            if (already_guessed (guessed_letter, current_guessed_letters))
                { printf("\nYou already guessed letter (%c)! take another guess..\n", guessed_letter); }

        }
        // after finishing the game, release the string and the missed letters arrays to be able to use them again.
        free(current_guessed_letters);
        free(missed_letters);
        //free(guessed_letter);
}

node *create_list()
{
    FILE* f = fopen( "words.txt", "r" );

    if (f == NULL)
        printf("an erorr occured");

    char word[20];
    node *head = init_list();

    while (fscanf(f, "%s", word) != EOF)
    {
        head = push_back(head, word);
    }

    fclose(f);


    return head;
}



int main()
{
    node *head = create_list();

    int resume;
    do
    {
        run_game(head);
        printf("Do you want to play again? Enter 1 to continue .. 0 to exit: ");
        scanf(" %d", &resume);
    } while (resume == 1);


    delete_list(head);
}



