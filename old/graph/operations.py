import socket

def bs_send_payload(payload,node):
    s=socket.socket()
    s.connect(("127.0.0.1",node))
    s.send(payload)
    ret = s.recv(1000)
    print("Data from node %d: %s" % (node,ret))
    return ret

def sn_send_payload(data,dest):
    s=socket.socket()
    s.connect(("127.0.0.1",node))
