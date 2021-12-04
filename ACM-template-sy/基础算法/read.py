# python 应用
#strip() 去掉左右两端的空白符，返回 str
#slipt() 把字符串按空白符拆开，返回 [str]
#map 把 list 里面的值映射到指定类型，返回 [type]
# 有多组输入数据，但没有具体的告诉你有多少组，只是让你对应每组输入，应该怎样输出。
while True:
    try:
        a, b = map(int,input().strip().split())
        print (a+b)
    #  print ('\n') 每组输出后面加多加换行
    except EOFError:
        break
# 输入一个整数，告诉我们接下来有多少组数据，然后在输入每组数据的具体值。
case = int(input().strip())
for i in range(case):
    a, b = map(int,input().strip().split())
    print (a+b)
# 有多组输入数据，没有具体的告诉你有多少组,但是题目却告诉你遇见什么结束
while True:
    a, b = map(int, input().strip().split())
    if a == 0 and b == 0:
        break
    print (a + b)
# 输入有多组，并却题目告诉你每组输入遇见什么结束，与第三种不同之处在于，每组输入都有相应的细化。
case = int(input())
for i in range(case):
    a, b = map(int, input().strip().split())
    if a == 0 and b == 0:
        break
    print (a + b)
# 这次的输入实现输入一个整数，告诉我们有多少行，在输入每一行。对于每一行的输入，有划分为第一个数和其他的数，第一个数代表那一组数据一共有多少输入。
case=int(input())
for i in range(case):
    data = list(map(int, input().split()))
    sum = 0
    for j in data:
        sum += j
    print (sum)
# 有多种输入数据，对于每组输入数据的第一个数代表该组数据接下来要输入数据量
while True:
    try:
        data = list(map(int, input().split()))
        n, array = data[0], data[1:]    
        sum = 0
        for i in range(n):
            sum += array[i]
        print(sum)
    except EOFError:
        raise
# 这种类型的输出注意的就是换行，这类题目说在输出样例中，每组样例之间有什么什么，所以我们在对应输出的同时要判断一下是否是最后一组输出，如果不是，就 将题目所说的东西输出（一般是换行或空格），如果是，就直接结束。
while True:
    data = input()
    if data.isspace() == True:
        break
    else:
        data = list(map(int, input().split()))
        n, array = data[0], data[1:] 
        sum = 0
        for i in range(n):
            sum += array[i]
        print (sum)