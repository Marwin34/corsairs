# Corsairs

*Note: this project is really old, it was made when i was learning programming in C++.*

-----

### Description

Corsairs is a 2D multiplayer game where u can control your own ship to conquer ocean. You can choose from three different ships, travel between two islands and fight with opponents for their goods which u can sell later in the port.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=r78oSGNFjnA
" target="_blank"><img src="http://img.youtube.com/vi/r78oSGNFjnA/0.jpg"
alt="corsairs video" width="240" height="180" border="0" /></a>

-----

### Technology used

This game was wrote in C++ with SFML. It uses UDP datagrams for communication between clients and server. Server is processing actions from clients and then send them updates. Client creates listening socket on your network adapter ip address and on port 50000, it also loads server ip from file *ip.txt* and send data using this address and port 50001. Server creates listening socket on your network adapter ip address and port 50001, when server receives data from client it process it and then send it using client ip address and port 50000.

-----

#### Prject structure

Project consists of 2 folders, one for server and one for client.

```` txt
.
├── server                          #(server folder)
    ├── resources                   #(server's resources)
        ├── database.txt            #(database file)
├── client                          #(client folder)
    ├── resources                   #(client's resources)
        ├── font                    #(fonts)
        ├── img                     #(images)
        ├── ip.txt                  #(ip initialization file)
````

##### Acknowledgments

![alt text](https://www.sfml-dev.org/download/goodies/sfml-logo-small.png "SFML logo")

SFML library: [SFML main site](https://www.sfml-dev.org/index.php).
