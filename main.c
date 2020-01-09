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

    system("color 04");  //color rojito uwu

    Map * pkmn = createMap(stringHash, stringEqual);
    list *pkmnn = list_create_empty ();
    Map *tipopkmn = createMap(stringHash, stringEqual);

    int flag=0;
    int menu_opcion;
    do{
        printf("Main Menu\n");
        printf("1. Crear equipo.\n");
        printf("2. Mis Equipos.\n");
        printf("3. Pokedex.\n");
        printf("4. Ayuda.\n");
        printf("5. Salir.\n");
        printf(" Porfavor Seleccione una opcion del menu: ");
        scanf("%d",&menu_opcion);
        printf("\n");



        switch(menu_opcion){

            case 1: {
                FILE*archivo;
                archivo=fopen("CSV/Pokemon.csv","r");
                if(archivo==NULL){
                    printf("No se pudo cargar el archivo. \n");
                    exit(1);
                }
                else{
                    printf("Los archivos se cargaron correctamente!! \n\n");

                    char linea[1024];

                    while (fgets (linea, 1023, archivo) != NULL){
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
                        insertMap(tipopkmn, c->tipo, c);
                        list_push_back (pkmnn, c);
                    }


                    fclose(archivo);

                    int submenu_opcion;
                    printf("¿Desea ver la lista de Pokemon disponibles?\n");
                    printf("1.-Si.\n");
                    printf("2.-No.\n");
                    scanf("%d",&submenu_opcion);
                    printf("\n");


                    switch(submenu_opcion){

                        case 1:{
                            pokemon *lista = list_first (pkmnn);
                            lista=list_next(pkmnn);
                            while (lista != NULL){
                                printf("Nombre: %s\nTipo: %s  Tipo 2: %s \nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n\n", lista->nombre, lista->tipo, lista->tipo2, lista->hp, lista->atk, lista->def, lista->atkesp , lista->defesp, lista->vel);
                                lista= list_next (pkmnn);
                            }
                            char nombre_pokemon [20];
                            printf("Escriba el nombre del pokemon que desea:");
                            scanf("%s", nombre_pokemon);
                            int i;
                            nombre_pokemon[0]= toupper(nombre_pokemon[0]);
                            for (i = 1; i < strlen(nombre_pokemon) ; i++){
                                if (nombre_pokemon[i]!=' ') nombre_pokemon[i]= tolower (nombre_pokemon[i]);

                                else toupper (nombre_pokemon[i++]);
                            }


                            pokemon*u = searchMap(pkmn,nombre_pokemon);

                            pokemon *primer = u;


                        }
                        break;


                        case 2: {
                            char nombre_pokemon [20];
                            printf("Escriba el nombre del pokemon que desea:");
                            scanf("%s", nombre_pokemon);

                            int i;
                            nombre_pokemon[0]= toupper(nombre_pokemon[0]);
                            for (i = 1; i < strlen(nombre_pokemon) ; i++){
                                if (nombre_pokemon[i]!=' ') nombre_pokemon[i]= tolower (nombre_pokemon[i]);

                                else toupper (nombre_pokemon[i++]);
                            }

                            pokemon*u = searchMap(pkmn,nombre_pokemon);

                            pokemon *primer = u;

                        }
                        break;

                        default:printf("Seleccion Invalida!!!\n");
                        break;

                    }
                }
                flag++;
            }
            break;


            case 2:
            break;


            case 3:{            //Entrega datos de un pokemon especifiado por el usuario
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

                if( archivo==NULL ) printf("Error al abrir el fichero\n");

                else
                {
                    printf("\n");
                    while( !feof(archivo)) printf("%c",getc(archivo));    //Imprime
                }
                printf("\n");

                if(flag>0){     //si la opcion 1 fue ingresada anteriormente, el usuario podra ver estadisticas del pokemon
                    pokemon*u = searchMap(pkmn,nombre);
                    printf("\nTipo: %s  Tipo 2: %s \n\nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n", u->tipo, u->tipo2, u->hp, u->atk, u->def, u->atkesp , u->defesp, u->vel);
                }
                printf("\n");
                fclose(archivo);
            }
            break;


            case 4:{   //imprime por panntalla el texto de ayuda

                FILE*archivo;
                archivo=fopen("Ayuda.txt","r");
                if( archivo==NULL )
                    printf("Error al abrir el fichero\n");

                else
                {
                    printf("\n");

                    while( !feof(archivo)) printf("%c",getc(archivo));
                }

                fclose(archivo);
            }
                break;
            case 5:
                break;

            default:printf("Seleccion Invalida!!!");
                break;
        }
        system("pause");
        system("cls");
    }while(menu_opcion != 5);

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




