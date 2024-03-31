# pylint: disable=C0114, C0115, C0116

import re


class Roman:
    MIN_VALUE = 1
    MAX_VALUE = 3999
    REGEX_VALIDATION_PATTERN = r"^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$"
    REGEX_EXTRACTION_PATTERN = r"M|CM|CD|D|C|XC|XL|L|X|IX|IV|V|I"

    DECIMAL_TO_ROMAN: dict[int, str] = {
        1000: "M",
        900: "CM",
        500: "D",
        400: "CD",
        100: "C",
        90: "XC",
        50: "L",
        40: "XL",
        10: "X",
        9: "IX",
        5: "V",
        4: "IV",
        1: "I",
    }

    ROMAN_TO_DECIMAL: dict[str, int] = {v: k for k, v in DECIMAL_TO_ROMAN.items()}

    def decimal_to_roman(self, number: int) -> str:
        result = ""
        for decimal, roman_numeral in self.DECIMAL_TO_ROMAN.items():
            reps, number = divmod(number, decimal)
            result += roman_numeral * reps
        return result

    def roman_to_decimal(self, roman_numeral: str) -> int:
        if not re.match(self.REGEX_VALIDATION_PATTERN, roman_numeral):
            raise ValueError
        numerals = re.findall(self.REGEX_EXTRACTION_PATTERN, roman_numeral)
        return sum(self.ROMAN_TO_DECIMAL[numeral] for numeral in numerals)

    def __init__(self, roman_numeral_or_int: str):
        try:
            self.value = int(roman_numeral_or_int)
        except ValueError:
            self.value = self.roman_to_decimal(roman_numeral_or_int)
        if not self.MIN_VALUE <= self.value <= self.MAX_VALUE:
            raise ValueError

    @property
    def roman_numeral(self):
        return self.decimal_to_roman(self.value)

    def __str__(self):
        return self.roman_numeral

    def __repr__(self):
        return f"{self.__class__.__name__}('{self.roman_numeral}')"

    def get_value(self) -> int:
        return self.value

    def __add__(self, other: "Roman") -> "Roman":
        if not isinstance(other, Roman):
            raise TypeError
        if (value := self.value + other.value) > self.MAX_VALUE:
            raise OverflowError
        return Roman(str(value))

    def __sub__(self, other: "Roman") -> "Roman":
        if not isinstance(other, Roman):
            raise TypeError
        if (value := self.value - other.value) < self.MIN_VALUE:
            raise OverflowError
        return Roman(str(value))
