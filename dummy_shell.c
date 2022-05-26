#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include "leercadena.h"
#include <string.h>

#define MAX 100

int main(int argc, char *argv[])
{
    char **vector_cadenas;
    char cadena[MAX];
    char **listaBg;
    char **procesosBg;
    char *procesos[100];
    int posicionVector = 1;
    while (1)
    {
        pid_t pid, pidBG;
        printf("> ");
        leer_de_teclado(MAX, cadena);
        vector_cadenas = de_cadena_a_vector(cadena);

        if (strcmp("salir", vector_cadenas[0]) == 0)
        {

            printf("Gracias por usar mi dummy shell ;-) \n ");
            sleep(3);
            char *const args[] = {"clear", NULL};
            execvp(args[0], args);
            break;
        }

        if (strcmp("tareas", vector_cadenas[0]) == 0)
        {

            printf("---------------------------------- \n ");
            printf("Procesos en segundo plano \n");

            for (int i = 0; i < posicionVector; i++)
            {
                printf("%s, [%d] \n", procesos[posicionVector], posicionVector);
            }

            posicionVector++;

            printf("---------------------------------- \n ");
        }

        pid = fork();
        assert(pid >= 0);
        if (pid == 0)
        {

            if (tieneAmper(vector_cadenas))
            {

                listaBg = vectorSinAmper(vector_cadenas);

                procesos[1] = "hola";
                procesos[2] = "santi";

                pidBG = fork();
                if (pidBG == 0)
                {

                    execvp(listaBg[0], listaBg);
                }
                else if (pidBG > 0)
                {
                    exit(0);
                }
            }
            else
            {

                execvp(vector_cadenas[0], vector_cadenas);
            }

            for (int i = 0; i <= strlen(*vector_cadenas); i++)
            {

                if (strcmp(vector_cadenas[i], "detener") == 0)
                {

                    if (vector_cadenas[1] != NULL)
                    {
                        printf("El proceso ha sido matado brutalmente... \n ");
                        char *const kill[] = {"kill", vector_cadenas[1], NULL};
                        execvp(kill[0], kill);
                    }
                    else
                    {
                        printf("Rectifica el pid del proceso a detener, con el comando ps puedes saber los pids de todos los procesos actuales \n ");
                    }
                }
            }

            execvp(vector_cadenas[0], vector_cadenas);
        }
        else
        {

            wait(NULL);
        }
    }

    return 0;
}