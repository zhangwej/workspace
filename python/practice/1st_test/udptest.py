import socket
port=8081
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
#从指定的端口，从任何发送者，接收UDP数据
s.bind(('',port))
print('正在等待接入...')
while True:
    #接收一个数据
	data,addr=s.recvfrom(1024)
	print('Received:',data,'from',addr)
