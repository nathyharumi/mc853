# TCP server - DDNS project
# Luís Fernando RA 173170
# Nathália Harumi RA 175188

import socket
import datetime
import sys

DEFAULT_PATH =  "/home/ec2015/ra175188/public_html/ddns.html" # html page path
HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 50007              # Arbitrary non-privileged port
BUFFER_SIZE = 15

# Set a HTML file path if available
if len(sys.argv) > 1:
    path = sys.argv[1]
else:
    path = DEFAULT_PATH

# Open TCP server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
print("Server waiting connection from any host, on port:",PORT)
while 1:
    conn, addr = s.accept() # conn is a new "connection socket"
    print ("connected to: ",addr)

    # Receive the dinamic IP from ESP8266
    data = str(conn.recv(BUFFER_SIZE), 'utf-8')

    if not data: break

    print("Received:",data)

    # Get the last updated time
    now = datetime.datetime.now()

    html_string = """\
<html>

    <head>
        <meta http-equiv="refresh" content="5" >
        <meta charset="UTF-8">
        <title>MC853</title>
    </head>

    <body>
        <p>""" + str(data) + """</p>
        <p>Updated: """ + str(now.isoformat(sep=' ')[:-7]) + """</p>
    </body>

</html>"""

    print(html_string)
    with open(path, "w") as html_file:
        html_file.write(html_string)
    conn.close()
