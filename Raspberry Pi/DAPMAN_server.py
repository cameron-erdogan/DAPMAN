from gpiozero import LED
from simple_socket import *

class DAPMANServerListener(SimpleServerDelegate):

        door = LED(17)

        def message_received(self, raw_message):
                s = "raw message: " + str(raw_message)
                self.parse_message(raw_message)
                print(s)

        def parse_message(self, raw_message):
                message = raw_message.replace("[/TCP]", "")
                message = message.replace("\x00", "")

                if message == "unlock":
                        self.door.on()
                elif message == "lock":
                        self.door.off()

server_listener = DAPMANServerListener()
my_server = SimpleServer("192.168.1.138")
my_server.delegate = server_listener
my_server.start_listening()