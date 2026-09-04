def luhn_valid(number):
    digits = [int(d) for d in str(number)][::-1]
    total = 0
    for i, d in enumerate(digits):
        if i % 2 == 1:
            d *= 2
            if d > 9:
                d -= 9
        total += d
    return total % 10 == 0


def card_type(number):
    s = str(number)
    n = len(s)

    if not luhn_valid(number):
        return "INVALID"
    if n == 15 and s[:2] in ("34", "37"):
        return "AMEX"
    if n == 16 and 51 <= int(s[:2]) <= 55:
        return "MASTERCARD"
    if n in (13, 16) and s[0] == "4":
        return "VISA"
    return "INVALID"


def main():
    number = input("Number: ").strip()
    print(card_type(number))


if __name__ == "__main__":
    main()
