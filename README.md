### Installing Server and Client

 1. Server 
  ```sh
gcc BD/sqlite3.c Logger/log.c Jerarquia/Comprador/comprador.c Jerarquia/Vendedor/vendedor.c Jerarquia/Ticket/ticket.c Jerarquia/Coche/coche.c BD/BD.c main.c -l ws2_32 -DLOG_USE_COLOR -o server
  ```
 2. Client
  ```sh
  g++ Coche.cpp Ticket.cpp Usuario.cpp Comprador.cpp Vendedor.cpp main.cpp -l ws2_32 -o client
  ```
