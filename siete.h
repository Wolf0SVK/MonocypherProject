/********************************************************************************
 * Program:    Sietova komunikacia pre zabezpeceny prenos suborov
 * Subor:      siete.h
 * Autor:      Jozef Kovalcin
 * Verzia:     1.0.0
 * Datum:      2024
 * 
 * Popis: 
 *     Hlavickovy subor definujuci sietove funkcie pre zabezpeceny prenos suborov.
 *     Obsahuje deklaracie funkcii pre:
 *     - Inicializaciu a ukoncenie sietoveho spojenia
 *     - Spravu socketov pre server a klienta
 *     - Prenos dat medzi klientom a serverom
 * 
 * Zavislosti:
 *     - Standardne C kniznice
 *     - constants.h (definicie konstant pre program)
 *******************************************************************************/

#ifndef SIETE_H
#define SIETE_H

#include <stdint.h> // Kniznica pre datove typy (uint8_t, uint32_t)

#ifdef _WIN32
#include <winsock2.h>     // Windows: Zakladna sietova kniznica
#else
#include <unistd.h>       // Linux: Kniznica pre systemove volania (close, read, write)
#include <sys/random.h>   // Linux: Generovanie kryptograficky bezpecnych nahodnych cisel
#include <netinet/in.h>   // Linux: Sietove funkcie (adresy, porty, sockety)
#endif

#include "constants.h"    // Definicie konstant pre program

// Zakladne sietove funkcie
// Funkcie pre spravu socketov a inicializaciu siete
void cleanup_socket(int sock);           // Uvolni jeden socket
void cleanup_sockets(int new_socket, int server_fd);  // Uvolni dva sockety
void initialize_network(void);          // Inicializacia Winsock pre Windows
void shutdown_socket(int sock);          // Bezpecne ukoncenie socketu
void wait(void);                        // Cakacia funkcia pre synchronizaciu
void set_timeout_options(int sock);      // Nastavenie timeoutu pre socket
void cleanup_network(void);             // Ukoncenie Winsock pre Windows

// Serverove funkcie
// Funkcie potrebne pre vytvorenie a spravu serverovej casti
int setup_server(void);                 // Vytvori a nakonfiguruje server socket
int accept_client_connection(int server_fd, struct sockaddr_in *client_addr);  // Prijme spojenie od klienta
int send_ready_signal(int socket);      // Posle signal pripravenosti klientovi
int receive_salt(int socket, uint8_t *salt);  // Prijme kryptograficku sol
int send_key_acknowledgment(int socket);  // Posle potvrdenie o prijati kluca

// Klientske funkcie
// Funkcie potrebne pre vytvorenie a spravu klientskej casti
int connect_to_server(const char *address);  // Pripoji sa k serveru
int wait_for_ready(int socket);          // Caka na signal pripravenosti
int send_salt_to_server(int socket, const uint8_t *salt);  // Posle sol serveru
int wait_for_key_acknowledgment(int socket);  // Caka na potvrdenie kluca

// Funkcie pre prenos suborov
// Zdielane funkcie pre prenos zasifrovanych dat
int send_file_name(int socket, const char *file_name);      // Posle nazov suboru
int receive_file_name(int socket, char *file_name, size_t max_len);  // Prijme nazov suboru
int send_chunk_size(int socket, uint32_t size);            // Posle velkost bloku dat
int receive_chunk_size(int socket, uint32_t *size);        // Prijme velkost bloku dat
int send_encrypted_chunk(int socket, const uint8_t *nonce, const uint8_t *tag,  // Posle zasifrovany blok
                        const uint8_t *data, size_t data_len);
int receive_encrypted_chunk(int socket, uint8_t *nonce, uint8_t *tag,   // Prijme zasifrovany blok
                          uint8_t *data, size_t data_len);
int send_transfer_ack(int socket);       // Posle potvrdenie o prenose
int wait_for_transfer_ack(int socket);   // Caka na potvrdenie o prenose

#endif // SIETE_H