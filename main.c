#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "map.h"
#include "list.h"

typedef struct pokemon pokemon;
const char *get_csv_field (char * tmp, int i);
pokemon *crear_pokemon (char * nombre, char *tipo, char*tipo2, int hp, int atk, int def, int atkesp, int defesp, int vel);

long long stringHash(const void * key) {
    long long hash = 5381;
    const char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }
    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;
    return strcmp(A, B) == 0;
}

struct pokemon{
    char*nombre;
    char *tipo;
    char *tipo2;
    int hp,atk,def,atkesp,defesp,vel;
};

int main () {

    int op;

    Map * pkmn = createMap(stringHash, stringEqual);


    do{
        printf("ELIJA UNA OPCION: \n");
        printf("       1.- Armar Equipos\n");
        printf("       2.- Mis Equipos\n");
        printf("       3.- Pokedex\n");
        printf("       4.- Ayuda\n");
        printf("       5.- Salir\n");
        printf("Indique la opcion: ");
        scanf("%d", &op);
        fflush( stdin );
        printf("\n");

        if(op==1){
            FILE*fp;
            fp=fopen("CSV/Pokemon.csv","r");
            if(fp==NULL){
                printf("No se pudo cargar el archivo. \n");
                exit(1);
            }
            else{
                printf("Los Pokemon se cargaron correctamente!! \n");
            }

                char linea[1024];

                while (fgets (linea, 1023, fp) != NULL){
                    char *nombre = get_csv_field(linea, 1);
                    char *tipo = get_csv_field(linea, 2);
                    char *tipo2 = get_csv_field(linea, 3);
                    int hp = atoi(get_csv_field(linea, 4));
                    int atk = atoi(get_csv_field(linea, 5));
                    int def = atoi(get_csv_field(linea, 6));
                    int atkesp = atoi(get_csv_field(linea, 7));
                    int defesp = atoi(get_csv_field(linea, 8));
                    int vel = atoi(get_csv_field(linea, 9));
                    pokemon *c = crear_pokemon (nombre, tipo, tipo2, hp, atk, def, atkesp, defesp, vel);
                    insertMap(pkmn, c->nombre, c);
                }
                fclose(fp);

                list *equipo;
                equipo=list_create();
                int tam_list=0;

                while(tam_list<7){

                    char nombres [20];
                    printf("Escriba el nombre del pokemon que desea:");
                    scanf("%s", nombres);
                    pokemon *u = searchMap(pkmn,nombres);
                    list_push_back(equipo,u);
                    tam_list++;
                    int flag;
                    printf("Desea saber más información del pokemon escojido:\n");
                    printf("1.-SI");
                    printf("2.-NO");
                    if(flag==1){
                        printf("Los datos del pokemon son: \nnombre:%s   tipo:%s  tipo 2:%s \nstats:  \nhp:%d    atk:%d    def:%d   atkesp:%d  defesp:%d  vel:%d \n", u->nombre, u->tipo, u->tipo2, u->hp, u->atk, u->def, u->atkesp , u->defesp, u->vel);
                    }
                    printf("\n");
                }
        }
        printf("\n");


        if(op==2){

        }

        printf("\n");


        if(op==3){                 //Imprime datos de un pokemon especificado por el usuario
            char nombre[20];
            char pokedex[50];
            char dex[] = "Pokedex/";
            printf("Introduzca el nombre del Pokemon que desea \n");
            scanf("%s", &nombre);
            FILE * archivo;
            strcpy(pokedex,dex);
            strcat(pokedex,nombre);
            strcat(pokedex,".txt");             //Agrega la carpeta y el formato .txt al nombre del pokemon



            archivo=fopen(pokedex,"r");
            if( archivo==NULL )
                printf("Error al abrir el fichero\n");

            else
            {
                printf("\n");

                while( !feof(archivo) )
                    printf("%c",getc(archivo));    //Imprime
            }

            fclose(archivo);

        }

        printf("\n");


        if(op==4){                   //Abre el archivo Ayuda y lo imprime
            FILE*archivo;
            archivo=fopen("Ayuda.txt","r");
            if( archivo==NULL )
                printf("Error al abrir el fichero\n");

            else
            {
                printf("\n");

                while( !feof(archivo) )
                    printf("%c",getc(archivo));
            }

            fclose(archivo);
            }

        printf("\n");


    }while(op!=5);

    return 0;
}



pokemon *crear_pokemon (char * nombre, char *tipo, char*tipo2, int hp, int atk, int def, int atkesp, int defesp, int vel){
    pokemon *c = malloc(sizeof(pokemon));
    c->nombre = nombre;
    c->tipo = tipo;
    c->tipo2 = tipo2;
    c->hp = hp;
    c->atk = atk;
    c->def = def;
    c->atkesp = atkesp;
    c->defesp = defesp;
    c->vel = vel;
    return c;
}

const char *get_csv_field (char * tmp, int i){
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) if (!--i) return tok;
    return NULL;
}




