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

#Быстрая сортировка
def fast_sort(a) -> []:
    flag = True
    t = 0
    for c in range(0, len(a)):
        flag = True
        for i in range(0, len(a) - (c + 1)):
            if a[i] > a[i + 1]:
                flag = False
                t = a[i]
                a[i] = a[i + 1]
                a[i + 1] = t
        if flag == True:
            break
    return a

#Двухпутевое слияние
def merge_sort(a):
    mid = len(a) // 2
    if len(a) % 2 == 1:
        mid += 1
    left = a[0:mid]
    right = a[mid:len(a)]
    k = 0
    i = 0
    j = 0
    while (i < mid and mid + j < len(a)):
        if (left[i] <= right[j]):
            a[k] = left[i]
            i += 1
        else:
            a[k] = right[j]
            j += 1
            k += 1
        if i < mid:
            while k < len(a):
                a[k] = left[i]
                i += 1
                k += 1
        else:
            while k < len(a):
                a[k] = right[j]
                j = j + 1
                k = k + 1


def main():
    n = 5

    #Сортировка вставками
    a = []
    for c in range(0, n):
        a.append(random.randint(-32000, 32000))
    print(a)
    start_time = time.monotonic_ns()
    insert_sort(a)
    print((time.monotonic_ns() - start_time))
    print(a)

if __name__ == "__main__":
    main()
