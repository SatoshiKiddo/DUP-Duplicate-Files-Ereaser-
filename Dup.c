#include "ListaCompatibles.h"
#include <sys/stat.h>

#define ESC 27
#define ENTER 13
#define DER 77
#define IZQ 75
#define UP 38
#define DWN 40

char RAIZ[1024];
listaCompatibles *Compatibles= NULL;
listaArchivos *ArchivosEncontrados= NULL;

void lecturaDirectorio();
void ComparadorArchivos();

int main(int argc, char *argv[]){
    getcwd(RAIZ, 1024);
    DIR *principal= opendir(RAIZ);
    if (principal == NULL){
        printf("Bash: Error de pathname colocado.\n");
        return -1;
    }
    else{
        strcat(RAIZ, "/");
        lecturaDirectorio(principal, RAIZ);
        ComparadorArchivos(&ArchivosEncontrados);
        char opcion= ' ';
        char *Aviso= "El archivo fue eliminado";
        int flag= 0,i=0;
        listaCompatibles *Recorredor= Compatibles;
        if (ListaCLength(Compatibles)==0)
            printf("Bash: No hay archivos duplicados\n");
        while ((opcion != ESC) && (Recorredor != NULL)){
            ArchivosEncontrados = Recorredor->Compat;
            system("clear");
            printf("\nBash:\n----------Archivos Repetidos-----------\n\n");
            i=0;
            while (ArchivosEncontrados != NULL){
                printf("%d.- %s\n",i,ArchivosEncontrados->fd);
                ArchivosEncontrados= ArchivosEncontrados->siguiente;
                i++;
            }
            printf("---------------------------------------\n");
            printf("-Nro para borrar  -(s) para siguiente\n%s\n", (flag)? Aviso: "");
            opcion= getc(stdin);
            switch(opcion){
                case 's':   if(Recorredor->siguiente != NULL)
                                Recorredor= Recorredor->siguiente;
                            else
                                opcion= ESC;
                            break;
                default:    if ((opcion >= 48) && (opcion <= 57)){
                                remove(getPath(Recorredor->Compat, opcion - 48));
                                eliminarArchivo(&Recorredor->Compat, opcion - 48);
                                flag++;
                            }
                            break;
            }
            if (Recorredor->Compat == NULL){
                eliminarCompatible2(&Compatibles,Recorredor);
                Recorredor = Compatibles;
            }
        }
    }
    return 0;
}

void lecturaDirectorio(DIR *principal, char *raiz){
    struct dirent *Buffer= NULL;
    char PathC[1024];
    DIR *recursivo= NULL;
    while (1){
        Buffer=readdir(principal);
        strcpy(PathC, raiz);
        if(Buffer == NULL)
            break;
        if ((strcmp(Buffer->d_name,".") != 0) && (strcmp(Buffer->d_name,"..") != 0)){
            if(Buffer->d_type == DT_DIR){
                strcat(PathC,Buffer->d_name);
                recursivo=opendir(PathC);
                strcat(PathC,"/");
                lecturaDirectorio(recursivo, PathC);
            }
            else{ 
                if( Buffer->d_type == DT_REG){
                    strcat(PathC, Buffer->d_name);
                    ingresarArchivo(&ArchivosEncontrados, PathC);
                }
            }
        }
    }
    closedir(principal);
}

void ComparadorArchivos(){
    FILE *fd1=NULL;
    FILE *fd2=NULL;
    int x,a,b,flag;
    listaArchivos *aux= NULL;
    char Buffer1;
    char Buffer2;
    struct stat ArchivoPrincipal;
    struct stat ArchivoSecundario;
    listaArchivos *listaPrincipal;
    listaArchivos *P= ArchivosEncontrados;
    while (P != NULL){
        flag = 0;
        aux= (P)->siguiente;
        listaPrincipal = NULL;
        stat(P->fd, &ArchivoPrincipal);
        while(aux != NULL){
            fd1= fopen((P)->fd, "rb");
            stat(aux->fd, &ArchivoSecundario);
            fd2= fopen(aux->fd, "rb");
            if ((fd2 != NULL) && (ArchivoPrincipal.st_size == ArchivoSecundario.st_size)){
                    x=0;
                    while (x == 0){
                        a=fread(&Buffer1, 1, 1, fd1);
                        b=fread(&Buffer2, 1, 1, fd2);
                        if(Buffer1 != Buffer2){
                            x++;
                            break;
                        }
                        if ((a==0) && (b==0)){
                            break;
                        }
                        else if ((a == 0 ) || (b == 0)){
                            x++;
                            break;
                        }
                    }
                    if (x == 0){
                        ingresarArchivo(&listaPrincipal, aux->fd);
                        flag++;
                        eliminarArchivo2(&ArchivosEncontrados, aux->fd);
                    }
            }
            if (fd1 != NULL)
                fclose(fd2);
            if (fd2 != NULL)
                fclose(fd1);
            aux=aux->siguiente;
        }
        if (flag != 0){
            ingresarArchivo(&listaPrincipal, (P)->fd);
            ingresarArchivos(&listaPrincipal, &Compatibles);
        }
        P=P->siguiente;
    }
    eliminarListaArchivo(&ArchivosEncontrados);
}