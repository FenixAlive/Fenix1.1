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
#include <stdlib.h>

#define LP 100
#define C "clear"////////////////cambiar a cls en windows
#define M 67 //lineas de margen
#define L 97 //limite de array
//definicion de estructuras
struct usuario{
    char nombre[23];
    int pass;
};
struct clientes{
	int codigo_cliente;
	char Nombre_empresa[23];
	char Nombre_cliente[23];
	char puesto[23];
};
struct productos{
	int codigo_producto;
	char nombre_producto[23];
	float precio_unidad;
	float numero_unidades;
};
struct pedidos{
	int codigo_pedidos;
	struct clientes cliente;
	struct productos producto[L];
};
struct tablas{
    struct clientes cliente[L];
    struct productos producto[L];
    struct pedidos pedido[L];
    int contador[4];//contador de clientes, productos, pedidos y producto dentro de pedido
};
//definición de funciones
void esperar();
void margen(int m);
int autenticacion(struct usuario real);
int revisarUsuario(struct usuario real, struct usuario nuevo);
int menuP();
int menuTabla(void);
int alta(struct tablas *tabla);
int baja(struct tablas *tabla);
int consulta(struct tablas *tabla);
int modifica(struct tablas *tabla);
//inicia main
int main(void){
    struct usuario real={"admin",1234};
    struct tablas tabla;
    int m1=0;
    autenticacion(real);
    while(m1!=5){
        m1=menuP();
        switch(m1){
            case 1:
                while(alta(&tabla));
                break;
            case 2:
                while(baja(&tabla));
                break;
            case 3:
                while(consulta(&tabla));
                break;
            case 4:
                while(modifica(&tabla));
                break;
            case 5:
                break;
            default:
                margen(M);
                printf("\n\tOpcion incorrecta, vuelva a intentarlo");
                esperar();
                break;
        }
    }
    return 0;
}
//funciones
void margen(int m){
    int i=0;
    printf("\n\t");
    for(i=0;i<m;i++)
        printf("_");
    printf("\n");
}
void esperar(){
    fflush(stdin);
    margen(M);
    printf("\n\n\t\t\tPresiona una tecla para continuar: ");
    getchar();
    getchar();/////////////////////////////////////////quitar en windows
    system(C);
}
int autenticacion(struct usuario real){
    struct usuario nuevo;
    int cont=1, nom=0;
    system(C);
    while(cont){
        margen(M);
        printf("\n\t\t\t\tFenix 1.1");
        margen(M);
        printf("\n\n\t\tHola, Bienvenido al sistema:");
        printf("\n\n\tUsuario: ");
        fflush(stdin);
        scanf("%s", nuevo.nombre);
        nom=revisarUsuario(real,nuevo);
        printf("\n\n\tPassword: ");
        fflush(stdin);
        scanf("%d", &nuevo.pass);
        margen(M);
        if(!nom)
            printf("\n\n\tUsuario incorrecto, vuelva a intentarlo");
        else if(nuevo.pass != real.pass)
            printf("\n\n\tPassword incorrecto, vuelva a intentarlo");
        else if( nom && nuevo.pass == real.pass){
            cont=0;
            printf("\n\n\t\tDatos correctos, Bienvenido %s.",real.nombre);
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
int menuP(void){
    int op=0;
    margen(M);
    printf("\n\t\t\t\tFenix 1.1");
    margen(M);
    printf("\n\n\t1-Altas\n\t2-Bajas\n\t3-Consultas\n\t4-Modificaciones\n\t5-Salir");
    margen(M);
    printf("\n\n\t\tElige una opcion: ");
    scanf("%d",&op);
    system(C);
    return op;
}
int menuTabla(void){
    int op=0;
    do{
    system(C);
    margen(M);
    printf("\n\t\t\t\tFenix 1.1");
    margen(M);
    printf("\n\n\t1-Clientes\n\t2-Productos\n\t3-Pedidos\n\t4-Regresar");
    margen(M);
    printf("\n\n\t\tElige una opcion: ");
    scanf("%d",&op);
    if(op>4 || op<1){
        margen(M);
        printf("\n\tOpcion Invalida, vuelva a intentarlo");
        esperar();
    }    
    }while(op>4 || op<1);
    return op;
}
int alta(struct tablas *tabla){
    int op=menuTabla();

    system(C);
    return 0;
}
int baja(struct tablas *tabla){
    return 0;
}
int consulta(struct tablas *tabla){
    return 0;
}
int modifica(struct tablas *tabla){
    return 0;
}
