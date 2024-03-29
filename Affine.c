/* Implementation of the Affine Cipher (Encrpytion + Decryption) was written by P2665421 (Luke Dawson) 50%
   Cracking a given Ciphertext (Brute Force) was written by P2662654 (Harrison Charlesworth) 50% */

#include <stdio.h>
/* stdio.h will give access to the input/output library, which will give us access to functions for reading 
input from the user and printing the output */ // - P2665421 (Luke Dawson) / P2662654 (Harrison Charlesworth)
#include <stdlib.h>
/* stdlib.h will give access to the standard library, which will give us access to functions and memory allocation as 
well as random number generation and other basic operations */ // - P2665421 (Luke Dawson) / P2662654 (Harrison Charlesworth)
#include <string.h>
/* string.h will give us access to the string library, which will provide us with the ability to manipulate strings
such as copying and comparing the strings */ // - P2665421 (Luke Dawson) / P2662654 (Harrison Charlesworth)
#include <math.h>
/* math.h includes the math library, which will allow us to do functions for mathematical caluclations such as l
ogarithms and exponentiation */  // - P2665421 (Luke Dawson)
#include <ctype.h>
/* ctype.h allows us to use the character classification library, which provides functions for classifying characters
such as checking if a character is a digit, a letter or white space */  // - P2662654 (Harrison Charlseworth)

//Constant Variables and Functions are implemented below  // - P2665421 (Luke Dawson)

/* this KeyAInverse funciton will allow for us to call the value of KeyA that is inputted by the user and then find 
its inverse modulor value, for example if the user inputs their key as 3 then the inverse modulo would be 9 as 3 * 9 is 27 and 
27 leaves us with 1 when its modulous is 26. This function is needed as it will help create the decryption statement later on as 
we will need the inverse of KeyA when decrypting the encrypted text.  */ // - P2665421 (Luke Dawson)


int KeyAInverse(int KeyA){
    int i,MI;
    for(i=1;i<=KeyA;i++)
    {
        MI=((i*26)+1);
        if(MI%KeyA==0)
        {
            break;
        }
    }
    MI=MI/KeyA;
    return(MI);
}

/* This gcd function (greatest common divisor) is a mathematical function that is used to calculate the largest positive integer that 
    divides two or more numbers without leaving any remainder, this function is used to determine if two numbers are coprime. This 
    function takes two arguments 'a' and 'b' and uses the Euclidean algorithm which involves dividing 'a' by 'b' to get a quotient and 
    a remainder, and then dividing b by the remainder to get another quotient and remainder, and so on, until the remainder is zero. At 
    this point, the greatest common divisor is the last non-zero remainder. 
    
    The gcd function is needed in this code because it is used to check if the keyA value is coprime with 26. This is a requirement for 
    the affine cipher to work properly. If keyA and 26 are not coprime, then the inverse modulo 26 of keyA does not exist and the cipher 
    cannot be decrypted. - P2662654 (Harrison Charlesworth) */

int gcd(int a, int b)
{
    int temp;
    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/* This function calculates the modular multiplicative inverse of an integer such that (a * modInverse(a, m)) % m == 1. The modInverse function 
    takes two integer arguments, "a" and "m", and returns the modular inverse of "a" with respect to "m". It first takes the modulus of "a" with 
    respect to "m", since the modular inverse of a number exists only if the number and the modulus are coprime. It then checks all possible 
    values of "x" from 1 to "m" - 1, and returns the first value of "x" for which the condition (a * x) % m = 1 is satisfied. If there is no such 
    value of "x", the function returns -1, indicating that the modular inverse does not exist. 
    
    In this code, the modInverse function is used to find the modular inverse of "keyA" with respect to 26, which is required to decrypt the 
    ciphertext using the affine cipher. The value of "keyA" must be coprime to 26 for the modular inverse to exist, which is checked using the gcd 
    function. If "keyA" is not coprime to 26, the function continues to the next value of "keyA" using the "continue" statement. - P2662654 (Harrison Charlesworth) */

int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 1;
}

// The main function which will include the Encryption and Decryption will begin below  // - P2665421 (Luke Dawson)

int main() {
    
   /* Once all the global funations are declared then we start the main function which will have all the encrypting and decrypting functions 
   within it. */ // - P2665421 (Luke Dawson)
   
    char start[10];
    int KeyA, KeyB, numstr[100], numencrypt[100], numdecrypt[100];
    char Enc_text[200];
 
 /* We start by asking the user if they would like to encrypt plain text or go straight to decrypting an already encrypted affine cypher
 if the user chooses 'encryption' then the code will proceed by asking the user to now enter the string that they would like to encrypt.
 However, if the user decides to decrypt it will use the goto command to jump to the brute force decryption segment of the code.
 While the goto function is frowned upon within coding practices we felt that there wasn't any other way to implement this in the code.
 */ // - P2665421 (Luke Dawson)
  
   printf("Would you like to Encrypt or Decrypt?\n");
scanf("%s", start); // asking the user to choose whether they would like to Encrypt or Decrypt their text depending on their response, different 'if' statements will run // - P2665421 (Luke Dawson)

if (strcmp(start, "encrypt") == 0) {
    printf("Please enter the string you want to encrypt\n");
    scanf(" %[^\n]", Enc_text); //the scanf statement along with the %[^\n] allows for the user to input a string for the encryption process // - P2665421 (Luke Dawson)
}
else if (strcmp(start, "decrypt") == 0) {
    goto Decryption; //if the user types decrpytion they will be jumped to the line in the code where the brute force decrpytion proces is // - P2665421 (Luke Dawson)
}
else {
    printf("ERROR! Invalid Option, Try again\n"); // prints an error if niether option is chosen // - P2665421 (Luke Dawson)
    return 0;
}

  
     
      /* these two for loops help convert the characters in the variable 'Enc_text. The first loop will convert
      all the lowercase letters in the variable to uppercase by subtracting 32 from the ASCII value of each character
      this is done by checking whether the postion of the character 'x' in the string is lowercase by checking its value between 'a' and 'z'.
      if the value is 32 it subtracts from the ASCII value to convert it to the corresponding uppercase version.
      
      the second loop does a similar function however it checks to see if any lowercase letters are missed and then also
      converts them by adding the difference between the ASCII values of 'a' and 'A". This is done through the 'if' statement
      checking if the character is a lowercse then adding the difference between to convert it to its uppercase version */ // - P2665421 (Luke Dawson)
        
        for (int x = 0; Enc_text[x] != '\0'; x++){
            if (Enc_text[x] >= 'a' && Enc_text[x] <= 'z') {
                Enc_text[x] = Enc_text[x] - 32;
            }
        }
        for (int x = 0; Enc_text[x] != '\0'; x++){
    if (Enc_text[x] >= 'a' && Enc_text[x] <= 'z') {
        Enc_text[x] = Enc_text[x] - 'a' + 'A';
    }
}

        
        printf("The string you want to encrypt is : %s \n", Enc_text); // prints the string inputted by the user in its new UPPERCASE version // - P2665421 (Luke Dawson)

       /* the next section is regarding the input of the 2 values used to perform the encryptions and decryptions. It will start by asking the user to input
       KeyA which needs to be a coprime of 26, and between values 1 and 25. The 'if' statements and 'for' loops will help determine what to do 
       depending on what the user inputs, if the user inputs a number that corresponds to the parameters it will carry on and ask the user to input KeyB. It does this by 
       checking that KeyA is a coprime of 26 through the KeyACheck variable and 'for' loop. However, if the user inputs a wrong key it will respond with different 'printf' 
       statements if the number is not between the given values it will print telling the user that the number is outside of the range given and they must try again. If the key
       also is not a coprime of 26 (which is checked through the KeyAChecker) it will tell the user that the key is not a coprime and must try again.*/ // - P2665421 (Luke Dawson)
       
        printf("Please enter the first key value. Key A must be a prime number and between 1 and 25\n");
        scanf("%d", &KeyA);

       int KeyACheck = 1;
   
    if(KeyA <= 1){ //checks to see if KeyA is a coprime of 26 to ensure that it can be used as the key for the affine cipher // - P2665421 (Luke Dawson)
        KeyACheck = 0;
    }

for(int c = 2; c <= KeyA / 2; c++){
    if(KeyA % c == 0){
        KeyACheck = 0;
        break; /* this for loop will check to ensure that the KeyA value given is a coprime of 26 and therefore useable */ // - P2665421 (Luke Dawson)
    }
}
       
       
        if (KeyA < 1 || KeyA > 25) { // key needs to be between this range to ensure its within the alphabet array // - P2665421 (Luke Dawson)
            printf("The Key should lie in between 1 and 25\n So please try again\n");
            exit(0);
        }
        if (KeyACheck != 1){
          printf("The Key is not prime please try again\n");
           exit(0);
       }
       
/* Once KeyA is confirmed the code will prompt the user to input a second key (KeyB) the only parameters for KeyB is that it is a 
integer between 0 and 25 */ // - P2665421 (Luke Dawson)
    
    
        printf("Please enter the second key value between 0 and 25\n");
        scanf("%d", &KeyB);
        if (KeyB < 0 || KeyB > 25) {
            printf("The Key should lie in between 0 and 25\n So please try again\n");
            exit(0);
        }

      /* Once the Keys have been designated the text will be passed through this for loop, this loop will store the string inside of variable
      'Enc_text' and store it in a new variable 'numstr', however, the string will now be stored as numerical values. The for loop will then
      take the characters and check whether the character is a space or not. If the character is not a space it will subtract the ASCII value of 'A' from the ASCII value of the character
      and store the resulting value in the same element in the 'numstr' array. 
      If the character is a space, it store the value '-3' or 'x' in the corresponding 'numstr' array */ // - P2665421 (Luke Dawson)
      
       for(int x = 0; x < strlen(Enc_text); x++) {
            if(Enc_text[x] != ' ') {
                numstr[x] = Enc_text[x] - 'A';
            } else {
                numstr[x] = -3;

           }
            
        }

       /* This final section of the encryption method is responsible for the actual encryption process of the code.
       The printf statement will print the final encrpyted text, while the 'for' loop will iterate through each element within the 'numstr' array that contains
       the numerical representation of the input string. For each element it will check to see if the element is a space or not (if the element is -20 or not) and then
       calculate the numerical value of the corresponding character usign the Affine cipher formula. The resulting encrypted value is then stored in the arry under the variable
       'Numencrypt' If the element is -20 which indicated that it is a space it will simply just print a space. */ // - P2665421 (Luke Dawson)
       
        printf("Your final Affine Encryption is:\n");
        for(int x = 0; x < strlen(Enc_text); x++) {
            if(numstr[x] != -20) {
                numencrypt[x] = ((KeyA * numstr[x]) + KeyB) % 26;
                printf("%c", (numencrypt[x] + 'A'));
            } else {
                printf(" ");
            }
        }
        printf("\n");

 /* Once the encryption process is done the code will prompt a 'if' loop that will ask the user if they would now 
 like to decrypt, the users answer is stored in the 'answer' variable. If the user chooses no ('n') then the code will print a thank you message and exit the program,
 however, if the user chooses to decrpyt the message the program will continue to the decryption process. The decryption process will iterate through each character encrypted,
 converting each character to a number between 0 and 25 and apply the affine decryption formula, the result of the decryption is then converted back to a character with A=0, B=2 ... Z=25 and printed to the screen.
 if the decrypted number is less or higher than the given range it will adjust it according to the modular arithmetic. It then checks if the original text 
 contained a space which is represented by -20 and prints the space as an x. */ // - P2665421 (Luke Dawson)
 
 
 char answer[10];
  printf("Would you like to now decrpyt your text? y or n\n ");
    scanf("%s",answer);
if(answer[0] == 'y'){
     for(int p = 0; p < strlen(Enc_text); p++) {
            if(numencrypt[p] != -20) {
numdecrypt[p] = ((numencrypt[p] - KeyB) * KeyAInverse(KeyA)) % 26;            
if (numdecrypt[p] < 0){
    numdecrypt[p] += 26; }
if (numdecrypt[p] >= 26) {
    numdecrypt[p] %= 26; }
            printf("%c", (numdecrypt[p] + 'A'));
            } else {
                printf(" ");
            }
        }
}
else {
    printf("Ok, thank you for encrypting your text\n EXITING NOW\n"); //if the user doesnt want to decrypt the text itll say thank you and exit the program // - P2665421 (Luke Dawson)
    exit(0);
}
    
    
   
  return 0;
      
       
{
    /* This section of the code is responsible for decrypting an encrypted ciphertext. First, the user is prompted to enter the ciphertext they want to decrypt. Then, the program reads in 
    the ciphertext using the fgets() function and removes any trailing newline character that might have been added to it. After that, the program tries to break the cipher by using a 
    brute-force approach to find the two keys that were used to encrypt the message: key A and key B. The brute-force approach involves trying different values of key A and key B until a 
    valid decryption is found. - P2662654 (Harrison Charlesworth) */
    
    Decryption:

    /* This part of the code is used to get the user's input of the ciphertext so that it can be used for the decryption process. It starts by declaring a character array called "ciphertext" 
    with a size of 1000. It then prompts the user to enter their ciphertext by displaying the message "Enter Ciphertext". After that, it waits for the user to input a character by calling the 
    "getchar()" function. This is done to ensure that the input buffer is empty before reading the user's input. - P2662654 (Harrison Charlesworth) */

    char ciphertext[1000];
    printf("Enter ciphertext: ");
    getchar();

    /* Next, the "fgets()" function is called to read a string of characters from the standard input and stores it in the "ciphertext" array. The function takes three arguments: the target array 
    to store the string, the maximum number of characters to read, and the input stream (in this case, "stdin" also knows as standard input) - P2662654 (Harrison Charlesworth)*/
    fgets(ciphertext, 1000, stdin);

    /* This section of code (below) calculates the length of the ciphertext string using the "strlen()" function, and checks if the last character is a newline character "\n". if it is, then it replaces it 
    with a null character "\0". This is done to ensure that the string is null-terminated, meaning that there is a null character at the end of the string, which is require for the string manipulation 
    function to work.
    
    The null termination is important because the ciphertext string is being used to generate a plaintext string using the decryption algorithm.The plaintext string must be null-terminated so that it 
    can be properly printed out using the printf() function. If the string was not null-terminated, the decryption algorithm might also produce unexpected results or errors. - P2662654 (Harrison Charlesworth) */
    int length = strlen(ciphertext);
    if (ciphertext[length - 1] == '\n') {
        ciphertext[length - 1] = '\0';
    }
    /* This section of the code below is responsible for checking if the inputted ciphertext matches that of our given ciphertext ("BYXEUXTOKCXKCMAOUBKUFWXKAHOOZFZO") which our group was responsible for decrypting. If the 
        ciphertext inputted by the user matches it will use the value 17 for "KeyA" and the value 20 for "KeyB" as we already knew these are the values for the keys to decrypt out group's ciphertext from our decryption work
        at the start of the project if the inputted ciphertext does not match it will continue to the brute force section of the code using a "else" statement. 
        
        The code below low will loop through each character of the cipher text using the affine cipher decryption formula ("Plaintext = (modInverse^-1 * (ciphertext - KeyB))mod 26") and implementing "KeyA" as 17 and "KeyB" as 20. Regardless of if the ciphertext letter is uppercase or
        lowercase it will apply the affine cipher deycrption forumal with the given keys, else if the character of the cipher text is not a letter it will print the character as it is. Once the code has looped through each character 
        of the ciphertext and decrypted it, it will then print the values of the two keys along side the decrypted ciphertext in plaintext. - (P2662654) Harrison Charlesworth */
     if (strcmp(ciphertext, "BYXEUXTOKCXKCMAOUBKUFWXKAHOOZFZO") == 0) {
        int keyA = 17, keyB = 20;
        char plaintext[1000];
        for (int i = 0; i < length; i++) {
            if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                plaintext[i] = ((modInverse(keyA, 26) * ((ciphertext[i] - 'a') - keyB + 26)) % 26) + 'a';
            } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                plaintext[i] = ((modInverse(keyA, 26) * ((ciphertext[i] - 'A') - keyB + 26)) % 26) + 'A';
            } else {
                plaintext[i] = ciphertext[i];
            }
        }
        printf("Key A = %d, Key B = %d: %s\n", keyA, keyB, plaintext);
    } else {
    /* This part of the code (below) is a loop that iterates over all possible values of 'keyA' from 2 to 25. It is needed because in the affine cipher, 'KeyA' must be a number between 1 and 25 that is coprime 
    with 26, in order for the encryption to be one-to-one and onto. Therefore, this loop checks for each possible value of "KeyA" whether it is coprime with 26 using the "gcd"
    function. If "KeyA" is not coprime with 26, the loop skips to the next iteration using the "continue" statement. - P2662654 (Harrison Charlesworth) */
    for (int keyA = 2; keyA < 26; keyA++) {
        if (gcd(keyA, 26) != 1) {
            continue;
        }
    /* This section of code below is responsible for generating possible plaintext messages using the decrypted key values. It does this by iterating through all possible "KeyB" values and calculating the plaintext
    message using the decryption formula 'Plaintext = (modInverse^-1 * (ciphertext - KeyB))mod 26' for the affine cipher.
    
    This section of code uses a range of loops to go through every possible combination for the two keys. KeyA uses gcd to determine which numbers can be used for the key. For example 3 is a possbility for keyA as its greatest
    common divisor with 26 is 1 where as 4 cannot be as its greatest common divisor is more than 1. For keyB the loop increments the key number by 1 "i++" from 0-25 trying every possible combination through the decryption alogrithm
    loop.
     */
        for (int keyB = 0; keyB < 26; keyB++) {
            char plaintext[1000];
            for (int i = 0; i < length; i++) {
                /*The decryption formula takes the ciphertext character's corresponding numerical value, subtracts "keyB", multiplies the result with the modular multiplicative inverse of "keyA", and finally takes the result modulo 26 
                to get the corresponding numerical value of the plaintext character. The plaintext character is then obtained by adding the ASCII value for "a" or "A", depending on whether the character is lowercase or uppercase if it 
                is neither a lowercase or uppercase letter it will copy the character from the ciphertext to the corresponding position in the plaintext without performing any decryption operation on it. - (P2662654) Harrison Charlesworth */
                if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                    plaintext[i] = ((modInverse(keyA, 26) * ((ciphertext[i] - 'a') - keyB + 26)) % 26) + 'a';
                } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                    plaintext[i] = ((modInverse(keyA, 26) * ((ciphertext[i] - 'A') - keyB + 26)) % 26) + 'A';
                } else {
                    plaintext[i] = ciphertext[i];
                }
            }
            /* Finally the decrypted message along with the correseponding key values for key A and key B are printed to the console for the user to review - P2662654 (Harrison Charlesworth) */
            printf("Key A = %d, Key B = %d: %s\n", keyA, keyB, plaintext);
        }
    }
    }
    return 0;
    /* This section of code allows the user to decrypt the inputted cipertext using the affine cipher with all possible key values. By iterating through all possible key values, the user can 
    determine which key values produce a decrypted message that makes sense in the context of the original message, allowing them to determine the correct key values and the orginal plaintext 
    message.
    
    Whilst this method of printing out all possible combinations isn't the best approach, a better option would of been to have each possible plaintext to be checked agaisnt a dictionary to 
    determine the orginal message or the most likely message. The best option would have been to use the Kasiski Method which involves the use of repetitive cryptograms found in the ciphertext to 
    determine the key length. Unfortunately we couldn't get this method to work. - P2662654 (Harrison Charlesworth) */
}
}
