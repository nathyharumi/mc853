# Echo server program
import socket

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 50007              # Arbitrary non-privileged port
BUFFER_SIZE = 15


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
print("Server waiting connection from any host, on port:",PORT)

conn, addr = s.accept() # conn is a new "connection socket"
print ("connected to: ",addr)
while 1:
    data = conn.recv(BUFFER_SIZE)

    if not data: break

    print("Received:",data)

    html_string =
"""<html>

<head>
    <meta charset="UTF-8">
    <title>MC853</title>
</head>

<body>
    """ + data + """
 </body>

 </html>"""

    print(html_string)
    with open("~/public_html/index.html", "w") as html_file:
        html_file.write(html_string)

conn.close()
