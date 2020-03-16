import time
from random import randint

f = open("date.txt")


def nrcif(n):
    nr = 0
    while n:
        nr += 1
        n /= 10
    return nr


# SORTARILE:


def bubblesort(lista):
    lg = len(lista)
    for i in range(lg):
        for j in range(lg):
            if lista[i] < lista[j]:
                lista[i], lista[j] = lista[j], lista[i]
    sortat = lista.copy()
    return sortat


def countsort(lista):
    nmax = max(lista)
    # ap = [0] * nmax
    ap = [0 for i in range(nmax + 1)]
    for i in lista:
        ap[i] += 1
    sortat = []
    for k in range(nmax + 1):
        while ap[k]:
            sortat.append(k)
            ap[k] -= 1
    return sortat


def merge_lists(lst, ldr):
    i = j = 0

    rez = []
    while i < len(lst) and j < len(ldr):
        if lst[i] <= ldr[j]:
            rez.append(lst[i])
            i += 1
        else:
            rez.append(ldr[j])
            j += 1

    rez.extend(lst[i:])
    rez.extend(ldr[j:])

    return rez


def merge_sort(lista):
    if len(lista) <= 1:
        return lista
    else:
        mij = len(lista) // 2
        lstg = merge_sort(lista[:mij])
        ldr = merge_sort(lista[mij:])
        return merge_lists(lstg, ldr)


def countingSort(lista, exp1):
    n = len(lista)
    out = [0] * n
    count = [0] * 10
    for i in range(0, n):
        index = lista[i] // exp1
        count[index % 10] += 1
    for i in range(1, 10):
        count[i] += count[i - 1]
    i = n - 1
    while i >= 0:
        index = arr[i] // exp1
        out[count[index % 10] - 1] = lista[i]
        count[index % 10] -= 1
        i -= 1
    for i in range(0, len(arr)):
        lista[i] = out[i]


def radixSort(lista):
    max1 = max(arr)
    exp = 1
    while max1 // exp > 0:
        countingSort(lista, exp)
        exp *= 10


def partition(lista, lower, greater):
    i = (lower - 1)
    pivot = lista[greater]
    for j in range(lower, greater):
        if lista[j] <= pivot:
            i = i + 1
            lista[i], lista[j] = lista[j], lista[i]
    lista[i + 1], lista[greater] = lista[greater], lista[i + 1]
    return i + 1


def quickSort(lista, lower, greater):
    if lower < greater:
        pvt = partition(lista, lower, greater)
        quickSort(lista, lower, pvt - 1)
        quickSort(lista, pvt + 1, greater)


# DECLARARI VARIABILE


# Fisierul contine pe prima linie t = numarul de teste
# pe a doua linie n = cate numere avem in testul respectiv
# pe a treia linie maxim = care este numarul cel mai mare din testul acela
lst = []
t = int(f.readline())
for i in range(t):
    n = int(f.readline())
    maxim = int(f.readline())
    for k in range(n):
        value = randint(1, maxim)
        lst.append(int(value))

    lsta = lst.copy()
    lstb = lst.copy()
    lstc = lst.copy()

    # COMPARAREA SORTARILOR:

    start_time = time.time()
    lstc.sort()
    end_time = time.time()
    print("Sortarea limbajului dureaza", end_time - start_time)
    print()

    if max(lst) <= 1000:
        start_time = time.time()
        sortat_count = countsort(lst)
        end_time = time.time()
        #   print(sortat_count)
        print("CountSort dureaza", end_time - start_time)
        print("Sortare valida" if lstc == sortat_count else "Sortare invalida")
    else:
        print("Recomandare:Dati numere mai mici decat 1.000 pentru a folosi CountSort")
    print()

    start_time = time.time()
    sortat_merge = merge_sort(lst)
    end_time = time.time()
    # print(sortat_merge)
    print("MergeSort dureaza", end_time - start_time)
    print("Sortare valida" if lstc == sortat_merge else "Sortare invalida")
    print()

    if len(lst) <= 3000:
        start_time = time.time()
        sortat_bubble = bubblesort(lst)
        end_time = time.time()
        # print(sortat_bubble)
        print("BubbleSort dureaza", end_time - start_time)
        print("Sortare valida" if lstc == sortat_bubble else "Sortare invalida")
    else:
        print("Recomandare: Dati mai putin de 3.000 de numere pentru BubbleSort")
    print()

    if nrcif(max(lst)) <= 5:
        start_time = time.time()
        radixSort(lsta)
        # print(lsta)
        end_time = time.time()
        print("RadixSort dureaza", end_time - start_time)
        print("Sortare valida" if lstc == lsta else "Sortare invalida")
    else:
        print("Recomandare: Dati numere mai mici decat 10.000 pentru a folosi RadixSort")
    print()

    if len(lst) <= 100000:
        start_time = time.time()
        quickSort(lstb, 0, len(lstb) - 1)
        end_time = time.time()
        print("QuickSort dureaza ", end_time - start_time)
        print("Sortare valida" if lstc == lstb else "Sortare invalida")
    else:
        print("Recomandare: Dati mai putin de 100.000 de numere pentru QuickSort")

    print("-----------------------------------------------------------------------------------------------")
f.close()
