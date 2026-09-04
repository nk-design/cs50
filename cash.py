def get_change():
    while True:
        try:
            dollars = float(input("Change owed: "))
            if dollars >= 0:
                return round(dollars * 100)
        except ValueError:
            pass


def main():
    cents = get_change()
    coins = 0
    for value in (25, 10, 5, 1):
        coins += cents // value
        cents %= value
    print(coins)


if __name__ == "__main__":
    main()
