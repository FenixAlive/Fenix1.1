//cambiar en windows: 18, 20, 218,225
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
*/
#include <stdio.h>
#include <stdlib.h>

#define W 0//1 windows, 0 linux
#define LP 100
#define C "clear"////////////////cambiar a cls en windows
#define M 67 //lineas de margen
#define L 97 //limite de array
#define T 23
//definicion de estructuras
struct usuario{
    char nombre[T];
    int pass;
};
struct clientes{
	char codigoCliente[T];
	char nombreEmpresa[T];
	char nombreCliente[T];
	char puesto[T];
};
struct productos{
	char codigoProducto[T];
	char nombreProducto[T];
	float precioUnidad;
	float numeroUnidades;
};
struct pedidos{
	int codigoPedido;
	struct clientes cliente;
	struct productos producto[L];
};
//definición de funciones
void revisarPedidos(struct pedidos pedido[]);
void esperar();
void margen(int m);
int autenticacion(struct usuario real);
int revisarUsuario(char real[], char nuevo[]);
int menuP();
void dibujarPedido(struct pedidos pedido);
int alta(struct pedidos pedido[],int contador);
int baja(struct pedidos pedido[]);
int consulta(struct pedidos pedido[]);
int modifica(struct pedidos pedido[]);

//inicia main
int main(void){
    struct usuario real={"admin",1234};
    struct pedidos pedido[L];
    int m1=0, i=0, contador=0;
    for(i=0;i<L;i++){
        pedido[i].codigoPedido=0;
    }
    //autenticacion(real);/////////////////////////////////quitar comentario al final
    while(m1!=5){
        m1=menuP();
        if(m1 != 5){
            if(m1>0 && m1<5){
                if(m1==1){//dar de alta producto
                    i=1;
                    while(i){
                        i=alta(pedido,contador);
                        contador++;
                    }
                }else{//preguntar cual producto

                }
            }else{
                margen(M);
                printf("\n\tOpcion incorrecta, vuelva a intentarlo");
                esperar();
            }
        }
    }
    return 0;
}
//funciones
void revisarPedidos(struct pedidos pedido[]){
    int i=0;
    margen(M);
    printf("\n\tPedidos actuales: ");
    for(i=0;i<L;i++)//revisar pedidos
        if(pedido[i].codigoPedido)
            printf("[%d], ",pedido[i].codigoPedido);
}
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
    printf("\n\n\t\t\tPresiona enter para continuar: ");
    getchar();
    if(!W) getchar();/////////////////////////////////////////quitar en windows
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
        nom=revisarUsuario(real.nombre,nuevo.nombre);
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
}
int revisarUsuario(char real[], char nuevo[]){
    int i=0;
    char a='a', b='b';
    while(a!='\0'){
        a=real[i];
        b=nuevo[i];
        if(a!=b) return 0;
        i++;
    }
    return 1;
}
int menuP(void){
    int op=0;
    system(C);
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
void cin(char variable[]){
    fflush(stdin);
    if(W)
        gets(variable);//////////////////////poner en windows
    else
        scanf("%s",variable);
}
int alta(struct pedidos pedido[], int contador){
    int i=0;
    char cont='s';
    revisarPedidos(pedido);
    margen(M);
    pedido[contador].codigoPedido=contador+1;
    printf("\n\tPedido Nuevo N.- %d",contador+1);
    margen(M);
    printf("\n\tPaso 1: Alta del Cliente: ");
    margen(M);
    printf("\n\n\tCodigo del cliente: ");
    fflush(stdin);
    cin(pedido[contador].cliente.codigoCliente);
    printf("\n\tNombre de la empresa: ");
    cin(pedido[contador].cliente.nombreEmpresa);
    printf("\n\tNombre del cliente: ");
    cin(pedido[contador].cliente.nombreCliente);
    printf("\n\tPuesto: ");
    cin(pedido[contador].cliente.puesto);
    //inicializar productos en 0
    for(i=0;i<L;i++)
        pedido[contador].producto[i].codigoProducto[0]='\0';
    i=0;
    while(cont=='s'){
        system(C);
        margen(M);
        printf("\n\tPedido Nuevo N.- %d",contador+1);
        margen(M);
        printf("\n\tPaso 2: Alta del Producto: ");
        margen(M);
        dibujarPedido(pedido[contador]);
        printf("\t %d\tCodigo: ",i+1);
        fflush(stdin);
        cin(pedido[contador].producto[i].codigoProducto);
        printf("\t\tNombre: ");
        cin(pedido[contador].producto[i].nombreProducto);
        printf("\t\tPrecio por Unidad: ");
        fflush(stdin);
        scanf("%f",&pedido[contador].producto[i].precioUnidad);
        printf("\t\tNo. de Unidades: ");
        fflush(stdin);
        scanf("%f",&pedido[contador].producto[i].numeroUnidades);
        printf("\n\t Agregar otro producto? s/n: ");
        fflush(stdin);
        if(!W) getchar();/////////////////////quitar en windows
        scanf("%c",&cont);
        i++;
    }
    margen(M);
    printf("\tQuieres dar de alta un nuevo pedido? s/n: ");
    fflush(stdin);
    if(!W) getchar();/////////////////////quitar en windows
    scanf("%c",&cont);
    contador++;
    system(C);
    if(cont=='s')
        return 1;
    else
        return 0;
}//fin alta pedido
void dibujarPedido(struct pedidos pedido){
    margen(M);
    printf("\n\t\t\t\tDatos del cliente: ");
    printf("\n\tCodigo: \t\t\tNombre empresa: ");
    printf("\n\t\t %s\t\t\t\t %s",pedido.cliente.codigoCliente,pedido.cliente.nombreEmpresa);
    printf("\n\tNombre Cliente:\t\t\tPuesto:");
    printf("\n\t\t%s\t\t\t\t%s",pedido.cliente.nombreCliente,pedido.cliente.puesto);
    margen(M);
    printf("\t| #\t| Codigo:\t| Nombre:\t| Precio:\t| Cantidad: ");
    margen(M);
    int i=0;
    for(i=0;i<L;i++){
        if(pedido.producto[i].codigoProducto[0] != '\0'){
            printf("\n\t %d\t %s\t\t %s\t\t %.2f\t\t %.2f",i+1,pedido.producto[i].codigoProducto,pedido.producto[i].nombreProducto,pedido.producto[i].precioUnidad,pedido.producto[i].numeroUnidades);
        }
    }
    margen(M);
}
