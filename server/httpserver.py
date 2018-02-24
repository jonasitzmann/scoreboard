import http.server
import socketserver

PORT = 8001
ip = '192.168.43.206'
useHomeWifi = True
if useHomeWifi:
        ip = '192.168.2.112'
Handler = http.server.SimpleHTTPRequestHandler
httpd = socketserver.TCPServer((ip, PORT), Handler)
print("serving at port", PORT)
httpd.serve_forever()