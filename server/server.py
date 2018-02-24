from SimpleWebSocketServer import SimpleWebSocketServer, WebSocket

connections = []
def broadcast(message):
    for conn in connections:
        conn.sendMessage(message)

class SimpleEcho(WebSocket):
    def handleMessage(self):
        # echo message back to client
        print(self.data)
        broadcast(self.data)

    def handleConnected(self):
        print(self.address, 'connected')
        connections.append(self)
        if not self in connections:
            connections.append(self)

    def handleClose(self):
        print(self.address, 'closed')
        if self in connections:
            connections.remove(self)


ip = '192.168.43.206'
useHomeWifi = True
if useHomeWifi:
    ip = '192.168.2.112'
server = SimpleWebSocketServer(ip, 8000, SimpleEcho)
server.serveforever()
