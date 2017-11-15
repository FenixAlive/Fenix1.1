//Proyecto Final
//Seminario  de Problemas de Programación
//Elaborado por Luis Angel Muñoz Franco
/*

*Autenticación de usuario para que pueda usar el sistema de administración de pedidos.

*Para cada una de las opciones del menu, se deben de mostrar en la parte superior los pedidos registrados hasta el momento.

El sistema será un menu de:
Altas
Bajas
Consultas
Modificaciones
Salir

tablas:
clientes
	codigo_cliente
	Nombre_empresa
	Nombre_cliente
	puesto

productos
	codigo_producto
	nombre_producto
	precio_unidad
	numero_unidades

pedidos
	codigo_pedidos
	struct clientes cliente
	struct productos producto[100]
*/
#include <stdio.h>

#define LP 100
//definicion de estructuras
struct usuario{
    char nombre[20];
    int pass;
};
//definición de funciones
void esperar();
int autenticacion(struct usuario real);
int revisarUsuario(struct usuario real, struct usuario nuevo);
int menuP();

int main(void){
    //declaracion
    struct usuario real={"admin",1234};
    int m1=0;
    autenticacion(real);
    while(m1!=5){
        m1=menuP();
        switch(m1){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                printf("Opcion incorrecta, vuelva a intentarlo");
        }
    }


    return 0;
}
//funciones
void esperar(){
    fflush(stdin);
    printf("\n\n\tPresiona una tecla para continuar: ");
    getchar();
    system("cls");
}
int autenticacion(struct usuario real){
    struct usuario nuevo;
    int cont=1, nom=0;
    while(cont){
        printf("\t\t\tSistema Fenix 1.1");
        printf("\n\n\t\tHola, Bienvenido al sistema:");
        printf("\n\n\tUsuario: ");
        fflush(stdin);
        scanf("%s", nuevo.nombre);
        nom=revisarUsuario(real,nuevo);
        printf("\n\n\tPassword: ");
        fflush(stdin);
        scanf("%d", &nuevo.pass);
        if(!nom)
            printf("\n\n\tUsuario incorrecto, vuelva a intentarlo");
        else if(nuevo.pass != real.pass)
            printf("\n\n\tPassword incorrecto, vuelva a intentarlo");
        else if( nom && nuevo.pass == real.pass){
            cont=0;
            printf("\n\n\tDatos correctos, Bienvenido %s.",real.nombre);
        }
        esperar();
    }
    return 1;
};
int revisarUsuario(struct usuario real, struct usuario nuevo){
    int i=0;
    char a='a', b='b';
    while(a!='\0'){
        a=real.nombre[i];
        b=nuevo.nombre[i];
        if(a!=b) return 0;
        i++;
    }
    return 1;
}
int menuP(){
    int op=0;
    printf("\t\t\tSistema Fenix 1.1");
    printf("\n\n\t1-Altas\n\t2-Bajas\n\t3-Consultas\n\t4-Modificaciones\n\t5-Salir");
    printf("\n\n\t\tElige una opcion: ");
    scanf("%d",&op);
    system("cls");
    return op;
}
