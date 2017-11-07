from collections import Counter

class Roman:
    VALUE_OF_ROMAN_NUMERAL = {
        'I': 1,
        'V': 5,
        'X': 10,
        'L': 50,
        'C': 100,
        'D': 500,
        'M': 1000,
    }
    MAX_N_OF_LETTER = {
        'I': 3,
        'V': 1,
        'X': 3,
        'L': 1,
        'C': 3,
        'D': 1,
        # No maximum was specified for 'M'.
    }
    MAXIMUM = 3999
    def __init__(self, roman_numeral):
        letter_counts = Counter(list(roman_numeral))
        if any(
                n > self.MAX_N_OF_LETTER.get(letter, n)
                for letter, n in letter_counts.items()):
            raise ValueError
            
        self.value = sum(
            self.VALUE_OF_ROMAN_NUMERAL[letter]
            for letter in roman_numeral)

        if self.value > self.MAXIMUM:
            raise ValueError
