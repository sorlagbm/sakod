import time

class Node:
    def __init__(self, sub="", children=None):
        self.sub = sub
        self.ch = children or []


class SuffixTree:
    def __init__(self, str):
        self.nodes = [Node()]
        for i in range(len(str)):
            self.addSuffix(str[i:])

    def addSuffix(self, suf):
        n = 0
        i = 0
        while i < len(suf):
            b = suf[i]
            x2 = 0
            while True:
                children = self.nodes[n].ch
                if x2 == len(children):
                    n2 = len(self.nodes)
                    self.nodes.append(Node(suf[i:], []))
                    self.nodes[n].ch.append(n2)
                    return
                n2 = children[x2]
                if self.nodes[n2].sub[0] == b:
                    break
                x2 = x2 + 1

            sub2 = self.nodes[n2].sub
            j = 0
            while j < len(sub2):
                if suf[i + j] != sub2[j]:
                    n3 = n2
                    n2 = len(self.nodes)
                    self.nodes.append(Node(sub2[:j], [n3]))
                    self.nodes[n3].sub = sub2[j:]
                    self.nodes[n].ch[x2] = n2
                    break
                j = j + 1
            i = i + j
            n = n2 

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

def tree_search(a, b):
    pass

def main() -> None:
    # Z-функция
    s = "string"
    print(zsearch(s, "tri"))

    c = SuffixTree("fsdasdf$")
    c.visualize()
    key = "das"
    d = 0
    for i in range(0, len(c.nodes)):
        if c.nodes[i].sub == key:
            d = i
    print(d)

if __name__ == '__main__':
    main()
