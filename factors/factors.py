#!/usr/bin/env python

import sys

def factorize_numbers(file_path):
    with open(file_path, 'r') as file:
        for line in file:
            # Remove newline characters and convert the string to an integer
            number = int(line.strip())

            # Factorize the number
            factors = factorize(number)

            # Print the factorization result
            print(f"{number}={factors}")

def factorize(n):
    factors = []
    divisor = 2

    while divisor <= n:
        if n % divisor == 0:
            factors.append(divisor)
            n = n // divisor
        else:
            divisor += 1

    return '*'.join(map(str, factors))

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: factors <file>")
        sys.exit(1)

    file_path = sys.argv[1]

    try:
        factorize_numbers(file_path)
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
        sys.exit(1)
    except Exception as e:
        print(f"An error occurred: {e}")
        sys.exit(1)
