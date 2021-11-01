import time
import sys
import random
 
#Сортировка вставками
def insertion_sort(a, n) -> []:
    if n > 0:
        insertion_sort(a, n - 1)
        x = a[n]
        j = n - 1
        while j >= 0 and a[j] > x:
            a[j + 1] = a[j]
            j = j - 1
        a[j + 1] = x


#Быстрая сортировка
def med(x, y, z):
    if y <= x and x <= z:
        return x
    elif z <= x and x <= y:
        return x
    elif z <= y and y <= x:
        return y
    elif x <= y and y <= z:
        return y
    elif y <= z and z <= x:
        return z
    elif x <= z and z <= y:
        return z

def quick_sort(array, key):
    less = []
    equal = []
    greater = []
    if len(array) > 1:
        elm = array[0]
        if key == "left":
            elm = array[0]
        elif key == "mid":
            elm = array[len(array)//2]
        elif key == "right":
            elm = array[len(array)-1]
        elif key == "median":
            elm = med(array[0], array[len(array)//2], array[len(array)-1])
        for x in array:
            if x < elm:
                less.append(x)
            elif x == elm:
                equal.append(x)
            elif x > elm:
               greater.append(x)
        return quick_sort(less, key)+equal+quick_sort(greater,key)
    else:
        return array

#Двухпутевое слияние
def merge_sort(a):
    if len(a) == 1 or len(a) == 0:
        return a
    l, r = a[:len(a) // 2], a[len(a) // 2:]
    merge_sort(l)
    merge_sort(r)
    n = m = k = 0
    c = [0] * (len(l) + len(r))
    while n < len(l) and m < len(r):
        if l[n] <= r[m]:
            c[k] = l[n]
            n += 1
        else:
            c[k] = r[m]
            m += 1
        k += 1
    while n < len(l):
        c[k] = l[n]
        n += 1
        k += 1
    while m < len(r):
        c[k] = r[m]
        m += 1
        k += 1
    for i in range(len(a)):
        a[i] = c[i]
    return a

def main():
    n = 10

    #Сортировка вставками
    a = []
    for c in range(0, n):
        a.append(random.randint(-32000, 32000))
    print(a)
    insertion_sort(a, len(a) - 1)
    print(a)

    #Быстрая сортировка

    d = []
    for c in range(0, n):
        d.append(random.randint(-32000, 32000))
    print(d)
    print(quick_sort(d, 'left'))

    #Двухпутевое слияние
    b = []
    for c in range(0, n):
        b.append(random.randint(-32000, 32000))
    print(b)
    merge_sort(b)
    print(b)

if __name__ == "__main__":
    main()
