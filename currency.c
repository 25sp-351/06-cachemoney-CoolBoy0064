#include <stdio.h>
#include <string.h>

#include "memoize.h"

//The function that will take a number and output the equivalent currency amount in words
//outputs a -1 if the input was an error.
int get_currency_word(int currency, char result[]){

    if (currency == 0){
        char zero[] = "Zero dollars and Zero Cents";
        strcpy(result, zero);
        return 0;
    }
    if(currency < 0){
        char error[] = "ERROR bad input";
        strcpy(result, error);
        return -1;
    }

char *units[] = {
    "Zero ",        "One ",       "Two ",      "Three ",
    "Four ",    "Five ",      "Six ",      "Seven ",
    "Eight ",   "Nine ",      "Ten ",      "Eleven ",
    "Twelve ",  "Thirteen ",  "Fourteen ", "Fifteen ",
    "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen "
}; // an array of strings, ranging from one to nineteen, index 0 is set to an empty string so that each index corresponds exactly

char cents_word[] = "Cents";
char dollars_and_word[] = "Dollars and ";

char *tens[] = { 
    "",     "",     "Twenty ",  "Thirty ", "Forty ",
    "Fifty ", "Sixty ", "Seventy ", "Eighty ", "Ninety " 
}; // an array of strings, ranging from twenty to ninety, the first 2 indexes are empty so that each index corresponds exactly [2] = twenty

char *multiplier[] = 
{"", "Thousand ", "Million ", "Billion "};
char hundred[] = "Hundred "; // string because strcat'ing with a string literal seg faults :/


    int cents = currency % 100;
    int currency_dup = currency; // a duplicate integer of the currency number we were given.
    int digits = 1; //Track the number of digits the number has. 
    int divisor = 1;
    int current_position;
    char cent_string[150] = "";
    char dollar_string[150] = "";
    char dollar_string_group[3][50] = {"", "", ""};
    int group = 0; //keeps track of the current multiplier group.

    while (currency_dup > 9){
       currency_dup = currency_dup/10; 
       divisor = divisor * 10;
       digits++;

    }

    current_position = digits;

    if(cents >= 20){
        strcat(cent_string, tens[cents/10]);
        strcat(cent_string, units[cents % 10]);
    }
    else{
        strcat(cent_string, units[cents]);
    }
    strcat(cent_string, cents_word);
    currency_dup = currency - cents; 
    currency_dup = currency/100;

    if(currency_dup == 0){ // if we have zero dollars and some amount of cents
        strcat(dollar_string, units[0]);
        strcat(dollar_string, dollars_and_word);
        strcat(result, dollar_string);
        strcat(result, cent_string);
        return 0;
    }
    // Process the remaining dollars in group of 1000s
    while (currency_dup > 0) {
        if (currency_dup % 1000 != 0) {
            
            int value = currency_dup % 1000;
            char temp[150] = "";
            
            // Handle 3 digit number
            if (value >= 100) {
                strcat(temp, units[value/100]);
                strcat(temp, hundred);
                value %= 100;
            }

            // Handle 2 digit number
            if (value >= 20) {
                strcat(temp, tens[value/10]);
                value %= 10;
            }

            // Handle unit number
            if (value > 0) {
                strcat(temp, units[value]);
            }

            // Add the multiplier according to the group
            strcat(temp,multiplier[group]);
            
            // Add this group result to overall result
            strcat(dollar_string_group[group], temp);
        }
        currency_dup /= 1000;
        group++;
    }

    strcat(dollar_string, dollar_string_group[2]);
    strcat(dollar_string, dollar_string_group[1]);
    strcat(dollar_string, dollar_string_group[0]);
    strcat(dollar_string, dollars_and_word);
    strcat(result, dollar_string);
    strcat(result, cent_string);

    return 0;

}

int main() {
    initalize_memo();
    memoized_function = get_currency_word;
    int currency = 1500;
    char moneyToWords[150] = ""; //if my calculations are correct, this program should not be able to exceeed this character count within the integer limit
    char empty_string[] = " ";

    printf("Input the first number (ctrl z to end the program)\n");
    while(fscanf(stdin, "%d", &currency) != EOF){
        memoized_currency(currency, moneyToWords);
        printf("Currency number: %s \n", moneyToWords);
        strcpy(moneyToWords, empty_string);
        printf("Enter another number (ctrl z to end the program)\n");
    }
    return 0;
}