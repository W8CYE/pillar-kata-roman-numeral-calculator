#include <stdlib.h>
#include <string.h>
#include <regex.h>        
#include "roman.h"

#define ARRAY_LENGTH(x) ((int)(sizeof(x) / sizeof(*(x))))

#define MIN_ROMAN_NUMERAL_VALUE (1U)
#define MAX_ROMAN_NUMERAL_VALUE (3999U)

static unsigned get_value_of_roman_letter(int roman_letter)
{
    switch (roman_letter) {
    case 'I': return    1U; break;
    case 'V': return    5U; break;
    case 'X': return   10U; break;
    case 'L': return   50U; break;
    case 'C': return  100U; break;
    case 'D': return  500U; break;
    case 'M': return 1000U; break;
    default:  return    0U; break;
    }
}

static unsigned get_value_of_roman_numeral(char *roman_numeral)
{
    static char *roman_numeral_pattern = (
        "^"
        "\\(M\\|MM\\|MMM\\)\\?"
        "\\(C\\|CC\\|CCC\\|CD\\|D\\|DC\\|DCC\\|DCCC\\|CM\\)\\?"
        "\\(X\\|XX\\|XXX\\|XL\\|L\\|LX\\|LXX\\|LXXX\\|XC\\)\\?"
        "\\(I\\|II\\|III\\|IV\\|V\\|VI\\|VII\\|VIII\\|IX\\)\\?"
        "$"
    );
    regex_t roman_numeral_regex;
    int no_match;

    unsigned x;
    unsigned next_x;
    unsigned sum;

    if (regcomp(&roman_numeral_regex, roman_numeral_pattern, 0))
        exit(EXIT_FAILURE);
    no_match = regexec(&roman_numeral_regex, roman_numeral, 0, NULL, 0);
    regfree(&roman_numeral_regex);
    if (no_match)
        return 0U; // roman_numeral is not a valid Roman numeral

    sum = 0U;
    for ( ; *roman_numeral != '\0'; roman_numeral++) {
        x = get_value_of_roman_letter(roman_numeral[0]);
        next_x = get_value_of_roman_letter(roman_numeral[1]);

        if (x >= next_x)
            sum += x;
        else
            sum -= x;
    }

    return sum;
}

static roman_numeral *print_roman(roman_numeral *buf, unsigned x)
{
    static char *roman_units[] = {
        "",
        "I",
        "II",
        "III",
        "IV",
        "V",
        "VI",
        "VII",
        "VIII",
        "IX",
    };
    static char *roman_tens[] = {
        "",
        "X",
        "XX",
        "XXX",
        "XL",
        "L",
        "LX",
        "LXX",
        "LXXX",
        "XC",
    };
    static char *roman_hundreds[] = {
        "",
        "C",
        "CC",
        "CCC",
        "CD",
        "D",
        "DC",
        "DCC",
        "DCCC",
        "CM",
    };
    static char *roman_thousands[] = {
        "",
        "M",
        "MM",
        "MMM",
    };
    static char **roman_digits_lists[] = {
        roman_units,
        roman_tens,
        roman_hundreds,
        roman_thousands,
    };

    char *s = (char *)buf;
    unsigned digits[ARRAY_LENGTH(roman_digits_lists)]; /*
        least significant digit first */
    int i;

    if (x < MIN_ROMAN_NUMERAL_VALUE || x > MAX_ROMAN_NUMERAL_VALUE)
        return NULL;

    for (i = 0; i < ARRAY_LENGTH(digits); i++) {
        digits[i] = x % 10U;
        x /= 10U;
    }

    s[0] = '\0';
    for (i = ARRAY_LENGTH(roman_digits_lists); --i >= 0; )
        strcat(s, roman_digits_lists[i][digits[i]]);

    return (roman_numeral *)s;
}

roman_numeral *add_roman_numerals(
    roman_numeral *sum, char *addend1, char *addend2)
{
    unsigned a, b;

    a = get_value_of_roman_numeral(addend1);
    if (a == 0)
        return NULL;
    b = get_value_of_roman_numeral(addend2);
    if (b == 0)
        return NULL;
    return print_roman(sum, a + b);
}

roman_numeral *subtract_roman_numerals(
    roman_numeral *difference, char *minuend, char *subtrahend)
{
    unsigned a, b;

    a = get_value_of_roman_numeral(minuend);
    if (a == 0)
        return NULL;
    b = get_value_of_roman_numeral(subtrahend);
    if (b == 0)
        return NULL;
    return print_roman(difference, a - b);
}

