import random
import math

def insertion_sort(a, n) -> []:
    if n > 0:
        insertion_sort(a, n - 1)
        x = a[n]
        j = n - 1
        while j >= 0 and a[j] > x:
            a[j + 1] = a[j]
            j = j - 1
        a[j + 1] = x

def main() -> None:
    # Неупорядоченный массив
        # Линейный поиск
    a = []
    for i in range(0, 10):
        a.append(random.randint(-32000, 32000))
    print(a)
    key = int(input())
    c = 0
    for i in range(0,len(a)):
        if a[i] == key:
            c = i
            break
    print(c)
    d = 0
        # Быстрый линейный поиск
    a.append(key)
    for i in range(0, len(a) - 1):
        if a[i] == a[len(a) - 1]:
            d = i
            break
    print(d)
    # Неупорядоченный массив
    b = []
    for i in range(0, 10):
        b.append(random.randint(-32000, 32000))
    insertion_sort(b, len(b) - 1)
    print(b)

    key = int(input())
    b.append(key)
    for i in range(0, len(b) - 1):
        if b[i] > key:
            break
        else:
            if b[i] == key:
                c = i
                break
    print(c)
    b.pop(len(b)-1)

    mid = len(b) // 2
    low = 0
    high = len(b) - 1
    while b[mid] != key and low <= high:
        if key > b[mid]:
            low = mid + 1
        else:
            high = mid - 1
        mid = (low + high) // 2

    if low > high:
        print("No value")
    else:
        print(mid)

    c = [b[d:d+int(math.sqrt(len(b)))] for d in range(0, len(b), int(math.sqrt(len(b))))]
    print(c)
    d, e = 0, 0
    for i in range(0, len(c)):
        if key <= c[i][len(c[i]) - 1]:
            for j in range(0, len(c[i])):
                if c[i][j] == key:
                    d, e = j, i
                    break
    print(e, d)

if __name__ == "__main__":
    main()
