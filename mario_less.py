def get_height():
    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                return height
        except ValueError:
            pass


def main():
    height = get_height()
    for row in range(1, height + 1):
        print(" " * (height - row) + "#" * row)


if __name__ == "__main__":
    main()
