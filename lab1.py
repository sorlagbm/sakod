import random
import time
import sys

#Сортировка вставками
def insert_sort(a) -> []:
    temp = 0
    item = 0
    for c in range(1, len(a)):
        temp = a[c]
        item = c - 1
        while item >= 0 and a[item] > temp:
            a[item + 1] = a[item]
            a[item] = temp
            item -= 1
    return a
    
def main():
    n = 5

    #Сортировка вставками
    a = []
    for c in range(0, n):
        a.append(random.randint(-32000, 32000))
    print(a)
    start_time = time.monotonic_ns()
    insert_sort(a)
    stop_time = time.monotonic_ns()
    print(a)
    print((stop_time - start_time))

if __name__ == "__main__":
    main()
