/*************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and
applying the concepts learned. I have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and debugged by my own efforts. I
further certify that I have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons.

Angelo Richter L. Dela Cruz, DLSU ID# 12148199
*************************************************************************************************/

#include <stdio.h>
#include <string.h>
#define MIN 1
#define MAX 20

typedef char string[51];

typedef char line[100];

struct symptom {
    int number;
    string name;
    string question;
    char answer;
};

struct impression {
    int number;
    string name;
    int numberOfSymptomsPresent;
    int symptomsPresent[MAX];
};

struct gender {
    char letter;
    string word;
    string pronoun;
};

struct personInformation {
    string name;
    string patientNumber;
    int age;
    struct gender gender;
};

int numberOfSymptoms;
int numberOfImpression;

struct symptom symptom[MAX];
struct impression impression[MAX];
struct personInformation personInformation;

/* emptyStruct empties the values initiated in structs
*/
void emptyStruct() {
    int i;
    int j;

    for (i = 0; i < MAX; i++) {
        strcpy(symptom[i].name,"");
        strcpy(symptom[i].question,"");
        symptom[i].answer = 'N';
    }

    for (i = 0; i < MAX; i++) {
        strcpy(impression[i].name,"");
        impression[i].numberOfSymptomsPresent = 0;
        for (j = 0; j < MAX; j++)
        {
            impression[i].symptomsPresent[j] = 0;
        }
    }
}

/* toLower copies the string in A and paste it on B and converts B into lowercase.
@param a - the string that the function will copy
@param b - the string where the function will input the converted A string into lowercase
Pre-condition: string a should only contain letters in the alphabet
*/

void toLower(string a, string b)
{
    int i;
    strcpy(b, a);
    int bLength = (int)strlen(b);


    for (i = 0; i < bLength; i++)
        if (b[i] >= 'A' && b[i] <= 'Z') {
            b[i] += 32;
        }
}

/* toUpper converts the character into uppercase
@param a - the character that will be converted into uppercase
@param b[] - the address where the function inputs the converted A string into lowercase
Pre-condition: a should only contain letters in the alphabet
*/
char toUpper(char a) {

    if (a >= 'a' && a <= 'z') {
        a = a - 'a' + 'A';
    }

    return a;
}

/* fgetsNewlineKill deletes the "/n" in a string
@param a - the string that will be converted into uppercase
@param B[] - the address where the function inputs the converted A string into lowercase
@return 1 if there is at least 1 modification and returns 0 if no modifications
Pre-condition: a should only contain letters in the alphabet
*/
void fgetsNewlineKill(char a[])
{
    size_t sl = strlen(a);

    if(sl > 0 && a[sl - 1] == '\n')
    {
        a[sl - 1] = '\0';
    }
}

/* myAtoi converts the string into an integer
@param a - the string that will be converted into uppercase
@return the integer from the string
Pre-condition: a should only contain numbers
*/
int myAtoi(string a) {
    int res = 0;

    for (int i = 0; a[i] != '\0'; ++i)
        res = res * 10 + a[i] - '0';

    return res;
}

/* ifStringValid checks if the word is found in the impression
@param temp - the string that the user input
@return i if the string was found but return -1 if the string was not found
*/
int ifStringValid(string temp)
{
    int i;
    string tempTwo;
    string tempThree;

    for(i = 0; i < numberOfImpression; i++) {
        toLower(impression[i].name, tempTwo);
        toLower(temp, tempThree);
        if (strcmp(tempTwo, tempThree) == 0) {
            return i;
        }
    }
    return -1;
}

/* ifImpressionPresent checks if the symptoms were present in the impression
@param i - the index of the impression
@return 1 if the impression is present, returns 0 if the impression is not present
*/
int ifImpressionPresent (int i) {
    int j;
    int counter = 0;
    for (j = 0; j < impression[i].numberOfSymptomsPresent; j++)
    {
        if (symptom[impression[i].symptomsPresent[j] - 1].answer == 'Y')
            counter++;
    }

    if (counter == impression[i].numberOfSymptomsPresent)
        return 1;
    else
        return 0;
}

/* printSymptom prints the symptoms on the impression
@param i - the index of the impression
*/
void printSymptom(int i) {
    int j;

    for (j = 0; j < impression[i].numberOfSymptomsPresent; j++) {
        printf("%s \n", symptom[impression[i].symptomsPresent[j] - 1].name);
    }
}

/* displayAndModifySymptom display and modify the symptoms in the impression
@param i - the index of the impression
*/
void displayAndModifySymptom(int i) {
    int j;

    printf("Below is a list of symptoms.\n");
    for(j = 0; j < numberOfSymptoms; j++)
    {
        printf("%d. %s \n", j + 1, symptom[j].name);
    }
    printf("\n");

    do {
        printf("How many of the symptoms above are present in a %s case? ", impression[i].name);
        scanf("%d", &impression[i].numberOfSymptomsPresent);

    } while (impression[i].numberOfSymptomsPresent > numberOfSymptoms);
    getchar();

    printf("Enter the corresponding number of each symptom: \n");

    for(j = 0; j < impression[i].numberOfSymptomsPresent; j++)
    {
        scanf("%d", &impression[i].symptomsPresent[j]);
        getchar();
        if (impression[i].symptomsPresent[j] > numberOfSymptoms || impression[i].symptomsPresent[j] <= 0) {
            do {
                printf("Wrong input! Please try again. \n");
                scanf("%d", &impression[i].symptomsPresent[j]);
                getchar();
            } while (impression[i].symptomsPresent[j] > numberOfSymptoms || impression[i].symptomsPresent[j] <= 0);
        }


    }

    printf("\n");
}

/* promptMenuOne presents the main menu on the interface
@return the letter that the user input
*/
char promptMenuOne() {
    char choice;
    do {
        printf("MENU #1 User Type \n");
        printf("\n");
        printf("D for Doctor \n");
        printf("P for Patient \n");
        printf("E for Exit \n");
        printf("\n");
        printf("Enter your choice: ");
        scanf("%c", &choice);
        getchar();
        if (!(choice == 'D' || choice == 'd' || choice == 'P' || choice == 'p' || choice == 'E' || choice == 'e'))
        {
            printf("Wrong input! Please try again.\n");
            printf("\n");
        }
    } while (!(choice == 'D' || choice == 'd' || choice == 'P' || choice == 'p' || choice == 'E' || choice == 'e'));

    return choice;
}

/* promptMenuTwo presents the menu for the doctor on the interface
@return the letter that the user input
*/
char promptMenuTwo() {
    char choice;
    do {
        printf("MENU #2 Doctor \n");
        printf("\n");
        printf("C to Create a new list of symptoms and impressions \n");
        printf("U to Use the existing list of symptoms and impressions \n");
        printf("D to Display Symptoms \n");
        printf("M to Modify Symptoms \n");
        printf("E to Exit \n");
        printf("\n");
        printf("Enter your choice: ");
        scanf("%c", &choice);
        getchar();
        if (!(choice == 'C' || choice == 'c' || choice == 'U' || choice == 'u' || choice == 'D' || choice == 'd' ||
              choice == 'M' || choice == 'm' || choice == 'E' || choice == 'e')) {
            printf("Wrong input! Please try again.\n");
            printf("\n");
        }
    } while (!(choice == 'C' || choice == 'c' || choice == 'U' || choice == 'u' || choice == 'D' || choice == 'd' ||
               choice == 'M' || choice == 'm' || choice == 'E' || choice == 'e'));

    return choice;
}

/* createSymptom initializes a symptom based on the user input
*/
void createSymptom() {
    do {
        printf("How many symptoms do you want to consider?");
        scanf("%d", &numberOfSymptoms);
        getchar();
        printf("\n");
    } while (numberOfSymptoms < MIN || numberOfSymptoms > MAX);

    int i;

    for (i = 0; i < numberOfSymptoms; i++) {
        symptom[i].number = i+1;
        printf("Symptom # %d: \n", symptom[i].number);

        printf("What is the symptom? ");
        scanf("%[^\n]", symptom[i].name);
        getchar();

        printf("How do you want to ask the symptom? \n");
        scanf("%[^\n]", symptom[i].question);
        getchar();

        printf("\n");
    }

    do {
        printf("How many impressions do you want to enter?");
        scanf("%d", &numberOfImpression);
        getchar();
        printf("\n");
    } while (numberOfImpression < MIN || numberOfImpression > MAX);

    for (i = 0; i < numberOfImpression; i++) {
        impression[i].number = i+1;
        printf("Impression # %d: \n", impression[i].number);

        printf("What is the illness? ");
        scanf("%[^\n]", impression[i].name);
        getchar();

        displayAndModifySymptom(i);
    }
}

/* useExistingFileSymptoms use an existing file to initialize the symptoms
@return 1 if the file is found
*/
int useExistingFileSymptoms() {

    int checker = 0;

    FILE *fp;
    fp = fopen("Symptoms.txt", "r");

    int i;
    line temp;
    char *token;

    if (fp != NULL) {
        //This inputs the quantity of symptoms.
        fgets(temp, sizeof(temp), fp);
        fgetsNewlineKill(temp);
        numberOfSymptoms = myAtoi(temp);


        for (i = 0; i < numberOfSymptoms; i++) {
            //This inputs the symptom's number.
            fgets(temp, sizeof(temp), fp);
            fgetsNewlineKill(temp);
            symptom[i].number  = myAtoi(temp);

            //This inputs the symptom's name.
            fgets(symptom[i].name, sizeof(symptom[i].name), fp);
            fgetsNewlineKill(symptom[i].name);

            //This inputs the symptom's question.
            fgets(temp, sizeof(temp), fp);
            fgetsNewlineKill(temp);
            token = strtok(temp, "?");
            strcpy(symptom[i].question, token);
            strcat(symptom[i].question, "?");

            checker = 1;
        }
    }
    fclose(fp);

    return checker;
}

/* useExistingFileImpression use an existing file to initialize the impressions
@return 1 if the file is found
*/
int useExistingFileImpression() {
    FILE *fp;
    fp = fopen("Impressions.txt", "r");

    int i;
    int j;
    line temp;
    char *token;
    int checker = 0;

    if (fp != NULL) {
        //This inputs the quantity of impression.
        fgets(temp, sizeof(temp), fp);
        fgetsNewlineKill(temp);
        numberOfImpression = myAtoi(temp);

        for (i = 0; i < numberOfImpression; i++) {
            //This inputs the impression's number.
            fgets(temp, sizeof(temp), fp);
            fgetsNewlineKill(temp);
            impression[i].number = myAtoi(temp);

            //This inputs the impression's name.
            fgets(impression[i].name, sizeof(impression[i].name), fp);
            fgetsNewlineKill(impression[i].name);

            //This inputs the symptoms present in the impression.
            fgets(temp, sizeof(temp), fp);
            fgetsNewlineKill(temp);
            token = strtok(temp, " ");
            j = 0;
            while (token != NULL) {
                impression[i].symptomsPresent[j] = myAtoi(token);
                j++;
                token = strtok(NULL, " ");
            }

            //This inputs the number of symptoms present in the impression.
            impression[i].numberOfSymptomsPresent = j;
        }

        checker++;
    }
    fclose(fp);

    return checker;
}

/* displaySymptom prints the symptoms
@return -1 if the impression was not found, return 1 if the impression was found
*/
int displaySymptom() {
    string temp;
    int i;

    printf("What is the Impression? ");
    scanf("%[^\n]", temp);
    getchar();

    i = ifStringValid(temp);

    if (i == -1) {
        printf("There is no such Impression. ");
    }
    else {
        printf("Symptoms of %s are: \n", temp);
        printSymptom(i);
    }

    printf("\n");

    return i;
}

/* modifySymptom modify and print the new symptoms
*/
void modifySymptom() {
    int i = displaySymptom();
    if (i != -1) {
        displayAndModifySymptom(i);
        printf("Here are the NEW SYMPTOMS of %s: \n", impression[i].name);
        printSymptom(i);
    }
}

/* patient prompts the user for name, patient number, age, gender, and symptoms
*/
void patient() {

    printf("What is your name? ");
    scanf("%[^\n]", personInformation.name);
    getchar();

    printf("What is your patient number? ");
    scanf("%s", personInformation.patientNumber);

    printf("Enter your age: ");
    scanf("%d", &personInformation.age);
    getchar();

    printf("Gender (M/F): ");
    scanf("%c", &personInformation.gender.letter);
    getchar();
    personInformation.gender.letter = toUpper(personInformation.gender.letter);
    if (!(personInformation.gender.letter == 'M' || personInformation.gender.letter == 'F')) {
        do {
            printf("Wrong input! please try again. \n");
            printf("Gender (M/F):");
            scanf("%c", &personInformation.gender.letter);
            getchar();
            personInformation.gender.letter = toUpper(personInformation.gender.letter);
        } while(!(personInformation.gender.letter == 'M' || personInformation.gender.letter == 'F'));
    }

    if(personInformation.gender.letter == 'M')
    {
        strcpy(personInformation.gender.word, "male");
        strcpy(personInformation.gender.pronoun, "He");
    }
    else if(personInformation.gender.letter == 'F')
    {
        strcpy(personInformation.gender.word, "female");
        strcpy(personInformation.gender.pronoun, "She");
    }

    int i;

    for (i = 0; i < numberOfSymptoms; i++)
    {
        printf("%s", symptom[i].question);
        printf(" (Y/N)");
        scanf("%c", &symptom[i].answer);
        getchar();
        symptom[i].answer = toUpper(symptom[i].answer);

        if (!(symptom[i].answer == 'Y' || symptom[i].answer == 'N')) {
            do {
                printf("Wrong input! please try again. \n");
                printf("%s", symptom[i].question);
                printf(" (Y/N)");
                scanf("%c", &symptom[i].answer);
                getchar();
                symptom[i].answer = toUpper(symptom[i].answer);
            } while(!(symptom[i].answer == 'Y' || symptom[i].answer == 'N'));
        }
    }

    printf("\n \t");

    printf("History of Present Illness \n");
    printf("%s, patient # %s is a %d-year old %s. %s has ", personInformation.name, personInformation.patientNumber,
           personInformation.age, personInformation.gender.word, personInformation.gender.pronoun);

    int yes = 0;

    for (i = 0; i < numberOfSymptoms; i++){
        if(symptom[i].answer == 'Y')
            yes++;
    }

    string temp;

    for (i = 0; i < numberOfSymptoms; i++) {
        if(symptom[i].answer == 'Y') {
            toLower(symptom[i].name, temp);
            printf("%s", temp);
            yes--;
        }

        if (yes > 1)
            printf(", ");
        else if (yes == 1)
            printf(" and ");
    }
    printf(". ");

    int counter = 0;

    for(i = 0; i < numberOfImpression; i++) {
        if (ifImpressionPresent(i) == 1) {
            counter++;
        }
    }

    if (counter > 1) {
        printf("Impressions are ");
    }
    else if (counter == 1) {
        printf("Impression is ");
    }
    else if (counter == 0) {
        printf("There are no impressions");
    }

    for (i = 0; i < numberOfImpression; i++) {
        if (ifImpressionPresent(i) == 1) {
            counter--;
            printf("%s", impression[i].name);

            if (counter > 1)
            {
                printf(", ");
            }
            else if (counter == 1)
            {
                printf(" and ");
            }
        }
    }

    printf(". \n");
}

/* createFileSymptom creates a file with the initialized symptoms
*/
void createFileSymptom() {
    FILE *fp;
    fp = fopen("Impressions.txt", "w");
    int i;
    int j;

    fprintf(fp , "%d\n", numberOfImpression);

    for (i = 0; i < numberOfImpression; i++) {
        fprintf(fp , "%d\n", impression[i].number);
        fprintf(fp , "%s\n", impression[i].name);
        for (j = 0; j < impression[i].numberOfSymptomsPresent; j++) {
            fprintf(fp , "%d", impression[i].symptomsPresent[j]);
            if (j < impression[i].numberOfSymptomsPresent - 1) {
                fprintf(fp , " ");
            }
        }
        fprintf(fp , "\n");
    }

    fclose(fp);
}

/* createFileImpression creates a file with the initialized impressions
*/
void createFileImpression() {
    FILE *fp;
    fp = fopen("Symptoms.txt", "w");
    int i;

    fprintf(fp , "%d\n", numberOfSymptoms);

    for (i = 0; i < numberOfSymptoms; i++) {
        fprintf(fp , "%d\n", symptom[i].number);
        fprintf(fp , "%s\n", symptom[i].name);
        fprintf(fp , "%s", symptom[i].question);
        fprintf(fp , " (Y/N)\n");
    }

    fclose(fp);
}

/* createFileHistory creates a file with the history of the patient
*/
void createFileHistory() {
    string filename;
    strcpy(filename, personInformation.patientNumber);
    strcat(filename, ".txt");

    FILE *fp;
    fp = fopen(filename, "w");
    int i;

    fprintf(fp, "History of Present Illness \n");
    fprintf(fp, "%s, patient # %s is a %d-year old %s. %s has ", personInformation.name, personInformation.patientNumber,
            personInformation.age, personInformation.gender.word, personInformation.gender.pronoun);
    int yes = 0;

    for (i = 0; i < numberOfSymptoms; i++){
        if(symptom[i].answer == 'Y')
            yes++;
    }

    string temp;

    for (i = 0; i < numberOfSymptoms; i++) {
        if(symptom[i].answer == 'Y') {
            toLower(symptom[i].name, temp);
            fprintf(fp, "%s", temp);
            yes--;
        }

        if (yes > 1)
            fprintf(fp, ", ");
        else if (yes == 1)
            fprintf(fp, " and ");
    }
    fprintf(fp, ". ");

    int counter = 0;

    for(i = 0; i < numberOfImpression; i++) {
        if (ifImpressionPresent(i) == 1) {
            counter++;
        }
    }

    if (counter > 1) {
        fprintf(fp, "Impressions are ");
    }
    else if (counter == 1) {
        fprintf(fp, "Impression is ");
    }
    else if (counter == 0) {
        fprintf(fp, "There are no impressions");
    }

    for (i = 0; i < numberOfImpression; i++) {
        if (ifImpressionPresent(i) == 1) {
            counter--;
            fprintf(fp, "%s", impression[i].name);

            if (counter > 1)
            {
                fprintf(fp, ", ");
            }
            else if (counter == 1)
            {
                fprintf(fp, " and ");
            }
        }
    }
    fprintf(fp, ".");
    fclose(fp);
}

int main() {
    char choiceOne;
    int checker = 0;
    int checkFileSymptoms = 0;
    int checkFileImpression = 0;

    do {
        choiceOne = promptMenuOne();
        printf("\n");

        if (choiceOne == 'D' || choiceOne == 'd')
        {
            char choiceTwo;;
            do {
                choiceTwo = promptMenuTwo();
                if (choiceTwo == 'C' || choiceTwo == 'c')
                {
                    emptyStruct();
                    createSymptom();
                    printf("Symptoms and impressions are initialized. \n");
                    checkFileSymptoms = 1;
                    checkFileImpression = 1;
                    checker = 1;
                }
                else if (choiceTwo == 'D' || choiceTwo == 'd') {
                    if (checker == 0) {
                        printf("There are no symptoms and impressions. Please initialize first the symptoms and impressions. \n");
                        printf("\n");
                    }
                    else {
                        char displayAnswer;
                        do {
                            displaySymptom();
                            printf("Do you want to try again? (Y/N)");
                            scanf("%c", &displayAnswer);
                            getchar();
                            printf("\n");
                            if (!(displayAnswer == 'N' || displayAnswer == 'n' || displayAnswer == 'Y' ||
                                  displayAnswer == 'y')) {
                                do {
                                    printf("Wrong input. \n");
                                    printf("Do you want to try again? (Y/N)");
                                    scanf("%c", &displayAnswer);
                                    getchar();
                                    printf("\n");
                                } while (!(displayAnswer == 'N' || displayAnswer == 'n' || displayAnswer == 'Y' ||
                                           displayAnswer == 'y'));
                            }
                        } while (!(displayAnswer == 'N' || displayAnswer == 'n'));
                    }
                }
                else if (choiceTwo == 'M' || choiceTwo == 'm') {
                    if (checker == 0) {
                        printf("There are no symptoms and impressions. Please initialize first the symptoms and impressions. \n");
                        printf("\n");
                    }
                    else {
                        char modifyAnswer;
                        do {
                            modifySymptom();
                            printf("Do you want to try again? (Y/N)");
                            scanf("%c", &modifyAnswer);
                            getchar();
                            printf("\n");
                            if (!(modifyAnswer == 'N' || modifyAnswer == 'n' || modifyAnswer == 'Y' ||
                                  modifyAnswer == 'y')) {
                                do {
                                    printf("Wrong input. \n");
                                    printf("Do you want to try again? (Y/N)");
                                    scanf("%c", &modifyAnswer);
                                    getchar();
                                    printf("\n");
                                } while (!(modifyAnswer == 'N' || modifyAnswer == 'n' || modifyAnswer == 'Y' ||
                                           modifyAnswer == 'y'));
                            }
                        } while (!(modifyAnswer == 'N' || modifyAnswer == 'n'));
                    }
                }
                else if (choiceTwo == 'U' || choiceTwo == 'u') {
                    emptyStruct();
                    checkFileSymptoms = useExistingFileSymptoms();
                    checkFileImpression = useExistingFileImpression();

                    if (checkFileSymptoms == 0 && checkFileImpression == 0) {
                        printf("There are no files for symptoms and impressions.\n");
                    }
                    else if (checkFileSymptoms == 0) {
                        printf("There are no files for symptoms.\n");
                    }
                    else if (checkFileImpression == 0) {
                        printf("There are no files for impression.\n");
                    }
                    else {
                        printf("The files for symptoms and impressions are initialized. \n");
                        checker = 1;
                    }
                    printf("\n");

                }
                else if (choiceTwo == 'E' || choiceTwo == 'e') {
                    printf("\n");
                }
            } while (!(choiceTwo == 'U' || choiceTwo == 'u' || choiceTwo == 'E' || choiceTwo == 'e'));
        }
        if (choiceOne == 'P' || choiceOne == 'p')
        {
            if (checker == 1) {
                patient();
                createFileHistory();
            }
            else {
                printf("The symptoms and impressions are not yet initialized. \n");
            }
            printf("\n");

        }
        if (choiceOne == 'E' || choiceOne == 'e')
        {
            if (checkFileSymptoms == 1) {
                createFileImpression();
            }
            if (checkFileImpression == 1) {
                createFileSymptom();
            }
        }
    } while (!(choiceOne == 'E' || choiceOne == 'e'));

    return 0;
}
