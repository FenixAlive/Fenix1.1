//hacer funcion cliente y producto
//terminar modificar producto y dar opcion de agregar nuevo producto
//cambiar en windows: C y W
/*Proyecto Final
    Seminario  de Problemas de Programaci�n
    Elaborado por Luis Angel Mu�oz Franco
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
    int contProd;
};
//prototipo de funciones
int revisarPedidos(struct pedidos pedido[]);
int preguntarPedido(int m1, struct pedidos pedido[], int contador);
void esperar();
void margen(int m);
int autenticacion(struct usuario real);
int revisarString(char real[], char nuevo[]);
int menuP();
int datosCliente(int datoMod, struct pedidos pedido[], int contador);
int datosProducto(int datoMod, struct pedidos pedido[], int contador);
void dibujarPedido(struct pedidos pedido);
int alta(struct pedidos pedido[], int contador);
int baja(struct pedidos pedido[], int contador[]);
int consulta(struct pedidos pedido[]);
int modifica(struct pedidos pedido[], int contador[]);

//inicia main
int main(void){
    struct usuario real={"admin",1234};
    struct pedidos pedido[L];
    int m1=0, i=1, contador[3]={0,0,0};
    //contador[0]=consecutivo de folio, contador[1]=pedidos vigentes, contador[2]=eleccion de pedido del usuario
    for(i=0;i<L;i++)
        pedido[i].codigoPedido=0;
    //autenticacion(real);/////////////////////////////////quitar comentario al final
    while(m1!=5){
        m1=menuP();
        if(m1>0 && m1<5){
            do{
                system(C);
                contador[1]=revisarPedidos(pedido);
                margen(M);
                if(m1==1){
                    i=alta(pedido, contador[0]);
                    contador[0]++;
                }else if(contador[1] || m1==3){
                    contador[2]=preguntarPedido(m1,pedido,contador[0]);
                    if(contador[2] && contador[2] != -2){
                        if(contador[2] != -1){
                            if(m1==2)
                                i=baja(pedido,contador);
                            if(m1==4)
                                i=modifica(pedido, contador);
                        }else if(m1 != 3){
                            printf("\n\t\tNo es posible realizar esta accion con este pedido");
                            esperar();
                        }
                        if(m1==3)
                            i=consulta(pedido);
                    }else if(contador[2]==-2) i=1;
                    else if(!contador[2]) i=0;
                }else{                        
                    margen(M);
                    printf("\n\tNo hay pedidos disponibles para ingresar a esta opcion");
                    margen(M);
                    esperar();
                    i=0;
                }
            }while(i);
        }else if(m1 != 5){
            margen(M);
            printf("\n\tOpcion incorrecta, vuelva a intentarlo");
            esperar();
        }
    }
    return 0;
}
//funciones
int revisarPedidos(struct pedidos pedido[]){
    int i=0, contador=0;
    margen(M);
    printf("\n\tPedidos actuales: ");
    for(i=0;i<L;i++)//revisar pedidos
        if(pedido[i].codigoPedido){
            if(contador%9==0 && contador)
                printf("\n\t\t\t ");
            printf("[%d], ",pedido[i].codigoPedido);
            contador++;
        }
    if(!contador)
        printf("Sin pedidos");
    return contador;
}
int preguntarPedido(int m1, struct pedidos pedido[], int contador){
//retorna 0 si se quiere salir, -1 si esta cancelado, -2 si no es valido, o el numero de pedido
    int r=0;
    if(m1==2) printf("\n\t\t\tBaja de Pedidos");
    if(m1==3) printf("\n\t\t\tConsulta de Pedidos");
    if(m1==4) printf("\n\t\t\tModificacion de Pedidos");
    margen(M);
    printf("\n\tPuedes presionar 0 para regresar al menu principal");
    margen(M);
    printf("\n\tCual pedido quieres: ");
    fflush(stdin);
    scanf("%d",&r);
    margen(M);
    if(r>0 && r <= contador){
        dibujarPedido(pedido[r-1]);
        if(!pedido[r-1].codigoPedido) r=-1;
    }else if(r > contador){
        margen(M);
        printf("\n\tPedido no valido, aun no se llega a ese numero de pedido");
        r=-2;
        esperar();
    }
    return r;
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
        nom=revisarString(real.nombre,nuevo.nombre);
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
int revisarString(char real[], char nuevo[]){
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
int datosCliente(int datoMod, struct pedidos pedido[], int contador){
//hacer////////////////////////////////////////////////////////////////
}
int datosProducto(int datoMod, struct pedidos pedido[], int contador){

//hacer////////////////////////////////////////////////////////////////
}
int alta(struct pedidos pedido[], int contador){
    int i=0;
    char cont='s';
    pedido[contador].contProd=0;
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
        dibujarPedido(pedido[contador]);
        pedido[contador].contProd++;
        margen(M);
        printf("\n\tPedido Nuevo N.- %d",contador+1);
        margen(M);
        printf("\n\tPaso 2: Alta del Producto: ");
        margen(M);
        printf("\n\t %d\tCodigo: ",i+1);
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
        margen(M);
        printf("\n\t Agregar otro producto? s/n: ");
        fflush(stdin);
        if(!W) getchar();/////////////////////////////////////////////
        scanf("%c",&cont);
        i++;
    }
    margen(M);
    printf("\tQuieres dar de alta un nuevo pedido? s/n: ");
    fflush(stdin);
    if(!W) getchar();/////////////////////quitar en windows
    scanf("%c",&cont);
    contador++;
    if(cont=='s')
        return 1;
    else
        return 0;
}//fin alta pedido
void dibujarPedido(struct pedidos pedido){
    int i=0;
    system(C);
    if(!pedido.codigoPedido){
        margen(M);
        printf("\n\t\t\t\tPEDIDO CANCELADO");
    }
    margen(M);
    printf("\n\t\t\t\tDatos del cliente:\n");
    printf("\n\tCodigo: \t\t\tNombre empresa: ");
    printf("\n\t\t %s\t\t\t\t %s",pedido.cliente.codigoCliente,pedido.cliente.nombreEmpresa);
    printf("\n\tNombre Cliente:\t\t\tPuesto:");
    printf("\n\t\t%s\t\t\t\t%s",pedido.cliente.nombreCliente,pedido.cliente.puesto);
    margen(M);
    printf("\t| #\t| Codigo:\t| Nombre:\t| Precio:\t| Cantidad: ");
    margen(M);
    for(i=0;i<pedido.contProd;i++){
        if(pedido.producto[i].codigoProducto[0] != '\0'){
            printf("\n\t %d\t %s\t\t %s\t\t %.2f\t\t %.2f",i+1,pedido.producto[i].codigoProducto,pedido.producto[i].nombreProducto,pedido.producto[i].precioUnidad,pedido.producto[i].numeroUnidades);
        }
    }
    margen(M);
    if(!pedido.codigoPedido){
        margen(M);
        printf("\n\t\t\t\tPEDIDO CANCELADO");
        margen(M);
    }
}//termina dibujarPedido
int baja(struct pedidos pedido[], int contador[]){
    char cont='s';
    printf("\n\t Revisa el pedido..., Aun quieres eliminarlo? s/n: ");
    fflush(stdin);
    if(!W) getchar();
    scanf("%c",&cont);
    if(cont=='s'){
        pedido[contador[2]-1].codigoPedido=0;
        margen(M);
        printf("\n\tPedido eliminado.");
    }
    margen(M);
    printf("\n\tDesea dar otro pedido de baja? s/n: ");
    fflush(stdin);
    if(!W) getchar();
    scanf("%c",&cont);
    if(cont=='s')
        return 1;
    else
        return 0;
}//termina baja
int consulta(struct pedidos pedido[]){
    char cont='s';
    margen(M);
    printf("\n\tQuieres consultar otro pedido? s/n: ");
    fflush(stdin);
    if(!W) getchar();
    scanf("%c",&cont);
    if(cont=='s')
        return 1;
    return 0;
}//termina consulta
int modifica(struct pedidos pedido[], int contador[]){
    int i=0, num2=-1, num3=-1, num4=-1;
    char cont='s';
    /*
            printf("\n\n\t\tQue quieres modificar?\n\n\t\t\t1-Datos del cliente.\n\t\t\t2-Productos.\n\t\t\t3-Regresar.\n\n\t\tElige una opcion: ");
            fflush(stdin);
            scanf("%d",&num2);
            if(num2>0 && num2<3){
                num3=-1;
                dibujarPedido(pedido[contador[2]-1]);
                margen(M);
                if(num2 == 1){
                    while(num3 != 5){
                        printf("\n\n\t\tQue quieres modificar?\n\n\t\t\t1-Codigo del cliente.\n\t\t\t2-Nombre de la empresa.\n\t\t\t3-Nombre del cliente.\n\t\t\t4-Puesto\n\t\t\t5-Regresar\n\n\t\tElige una opcion: ");
                        fflush(stdin);
                        if(!W) getchar();
                        scanf("%d",&num3);
                        switch(num3){
                            case 1:
                                printf("\n\n\tNuevo codigo del cliente: ");
                                cin(pedido[contador[2]-1].cliente.codigoCliente);
                                num3=5;
                                break;
                            case 2:
                                printf("\n\tNuevo nombre de la empresa: ");
                                cin(pedido[num-1].cliente.nombreEmpresa);
                                num3=5;
                                break;
                            case 3:
                                printf("\n\tNuevo nombre del cliente: ");
                                cin(pedido[num-1].cliente.nombreCliente);
                                num3=5;
                                break;
                            case 4:
                                printf("\n\tNuevo puesto: ");
                                cin(pedido[num-1].cliente.puesto);
                                num3=5;
                                break;
                            case 5:
                                break;
                            default:
                                margen(M);
                                printf("\n\tOpcion no valida, vuelve a intentarlo");
                                break;
                        }
                    }
                }
                if(num2 == 2){
                    while(num3 != 4){
                        dibujarPedido(pedido[num-1]);
                        margen(M);
                        printf("\n\n\t\tOpciones: \n\n\t\t1-Modificar Producto\n\t\t2-Agregar producto\n\t\t3-Eliminar producto\n\t\t4-Regresar\n\n\t\t\tElige una opcion: ");
                        fflush(stdin);
                        if(!W) getchar();
                        scanf("%d",&num3);
                        if(num3 == 1 || num3 == 3){
                            system(C);
                            dibujarPedido(pedido[num-1]);
                            margen(M);
                            if(!pedido[num-1].contProd)
                                printf("\n\t\t Este pedido no tiene productos para realizar esta opcion");
                            else{
                                printf("\n\n\t\tNumero de productos disponibles, puedes presionar 0 para terminar: \n\n\t\t");
                                for(i=0;i<pedido[num-1].contProd;i++)
                                    if(pedido[num-1].producto[i].codigoProducto[0] != '\0')
                                        printf("[%d], ",i+1);
                                margen(M);
                                printf("\n\n\t\tElige el numero de producto: ");
                                fflush(stdin);
                                scanf("%d",&num4);
                                if(num4>0 && num4<=pedido[num-1].contProd){
                                    if(num3==1){
                                        //modificar producto
                                    }else if(num3==3){
                                        //eliminar producto
                                    }
                                }else{
                                    margen(M);
                                    printf("\n\n\t\tNumero de producto no valido, intentalo de nuevo");
                                    esperar();
                                }
                            }
                        }
                         printf("\n\n\t\tNumero de productos a modificar, puedes presionar 0 para terminar: ");
                        margen(M);
                        for(i=0;i<pedido[num-1].numProd;i++)
                            if(pedido[num-1].producto[numProd].codigoProducto[0] != '\0')
                                printf("[%d], ",numProd);
                        if(!numProd){

                        }else{

                        }
                        switch(num3){
                            printf("\t\tNuevo codigo: ");
                            fflush(stdin);
                            cin(pedido[num-1].producto[numProd].codigoProducto);
                            printf("\t\tNuevo Nombre: ");
                            cin(pedido[num-1].producto[numProd].nombreProducto);
                            printf("\t\tNuevo Precio por Unidad: ");
                            fflush(stdin);
                            scanf("%f",&pedido[num-1].producto[numProd].precioUnidad);
                            printf("\t\tNo. de Unidades: ");
                            fflush(stdin);
                            scanf("%f",&pedido[num-1].producto[numProd].numeroUnidades);
                            break;
                            default:
                                margen(M);
                                printf("\n\t\tOpcion no valida, vuelve a intentarlo");
                                break;
                                else if(!pedido[num-1].numProd)
                                    printf("No hay Productos a modificar");
                                    esperar();

                        }
                
                    }

                }            
            }else if(num2<1 || num2 >3){
                margen(M);
                printf("\n\tOpcion no valida, intente de nuevo");
                esperar();
            }
        if (num2==3) return 1;
        */
        margen(M);
        printf("\n\tQuieres modificar otro pedido? s/n: ");
        fflush(stdin);
        if(!W) getchar();
        scanf("%c",&cont);
        if(cont=='s')
            return 1;
    return 0;
}//termina modifica
