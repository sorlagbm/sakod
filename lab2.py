import time

# Поиск подстроки с помощью Z-функции
def zfunction(s : str) -> []:
    n = len(s)
    zf = [0] * n
    left = right = 0
    for i in range(1, n):
        zf[i] = max(0, min(right - i, zf[i - left]))
        while i + zf[i] < n and s[zf[i]] == s[i + zf[i]]:
            zf[i] += 1
        if i + zf[i] > right:
            left = i
            right = i + zf[i]
    return zf

def zsearch(text : str, pattern : str) -> int:
    n = len(text)
    m = len(pattern)
    zf = zfunction(pattern + '#' + text)
    for i in range(m + 1, n + 1):
        if zf[i] == m:
            return i

def main() -> None:
    # Z-функция
    s = "string"
    print(zsearch(s, "str"))

if __name__ == '__main__':
    main()
