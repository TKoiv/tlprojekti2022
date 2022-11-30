import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('172.20.241.9',20000))
s.sendall(b'73\n')

lista = []

while True:
    data = s.recv(1024)
    if len(data) == 0:
        break
    lista.append(data.decode('utf-8'))



with open('file_tcp.csv', 'w') as f:
    for i in lista:
        print(i, end= ' ')
        f.write(i)

s.close()



