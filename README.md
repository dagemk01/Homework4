#Documentation
###CLients
All the clients work in the same way.

The client recieves a message, then reads it and prints tp the console.
Then the client sends the same message to the next address.

Client 1 starts at port 50001 and sends to 50002.
this is the same for all the other clients but increamenting one.

Client 6, which is the last client, then sends to port 50001 which contiues the loop.

To start this chain just telnet to any of the ports and the clients will keep echoing through the different clients.

the code is fully functional.
