import random
import time
import sys

# Сортировка вставками
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

def quick_sort(array, key) -> []:
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
        elm = med(array[0], array[len(array)//2],
    array[len(array)-1])
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

def get_bit(num, bit_ind) -> int:
    newnum = num>>bit_ind
    if(newnum % 2 == 1):
        return 1
    else:
        return 0

def radix_sort(arr, start, end, bit_ind) -> []:
    if bit_ind == 0:
        return
    if start >=end:
        return
    i=start
    j=end
    while(i < j):
        while get_bit(arr[i], bit_ind) == 0 and i<j:
            i+=1
        while get_bit(arr[j], bit_ind) == 1 and i<j:
            j-=1
        if i < j:
            arr[i], arr[j] = arr[j], arr[i]
    if get_bit(arr[i], bit_ind) == 1:
        i-=1
    radix_sort(arr, start, i, bit_ind-1)
    radix_sort(arr, i+1, end, bit_ind-1)

def main():
    n = 5

    # Сортировка вставками
    a = []
    for c in range(0, n):
        a.append(random.randint(-32000, 32000))
    print(a)
    start_time = time.monotonic_ns()
    insert_sort(a)
    stop_time = time.monotonic_ns()
    print(a)
    print((stop_time - start_time))

    #Быстрая сортировка
    b = []
    for c in range(0, n):
        b.append(random.randint(-32000, 32000))
    print(b)
    start_time = time.monotonic_ns()
    insert_sort(b)
    stop_time = time.monotonic_ns()
    print(b)
    print((stop_time - start_time))

    #Двухпутевое слияние
    d = []
    for c in range(0, n):
        d.append(random.randint(-32000, 32000))
    print(d)
    start_time = time.monotonic_ns()
    insert_sort(d)
    stop_time = time.monotonic_ns()
    print(d)
    print((stop_time - start_time))

if __name__ == "__main__":
    main()
