//cambiar en windows: C y W
/*
    Proyecto Final
    Seminario  de Problemas de Programación
    Elaborado por Luis Angel Muñoz Franco
*/
//cabeceras
#include <stdio.h>
#include <stdlib.h>

//definicion de constantes
#define W 0//1 windows, 0 linux
#define LP 100
#define C "clear"////////////////cambiar a cls en windows
#define M 73 //lineas de margen
#define L 97 //limite de array
#define T 27

//definicion de estructuras
struct usuario{
    char nombre[T];
    char pass[T];
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
int revisarPedidos(struct pedidos pedido[], int contador);
int preguntarPedido(int m1, struct pedidos pedido[], int contador);
void esperar();
void margen(int m);
int autenticacion(struct usuario real);
int revisarString(char real[], char nuevo[]);
int menuP();
int datosCliente(int datoMod, struct pedidos pedido[], int contador);
int datosProducto(int datoMod, struct pedidos pedido[], int contador, int i);
int nuevoProducto(struct pedidos pedido[], int contador);
void pinta(int x, int y);
void dibujarPedido(struct pedidos pedido, int contador);
int alta(struct pedidos pedido[], int contador);
int baja(struct pedidos pedido[], int contador[]);
int consulta(struct pedidos pedido[]);
int modifica(struct pedidos pedido[], int contador[]);
int eliminarProducto(struct pedidos pedido[], int contador, int pi);

int main(void){//inicia main
    struct usuario real={"a","a"};
    struct pedidos pedido[L];
    int m1=0, i=1, contador[3]={0,0,0};
    //contador[0]=consecutivo de folio, contador[1]=pedidos vigentes, contador[2]=eleccion de pedido del usuario
    for(i=0;i<L;i++)
        pedido[i].codigoPedido=0;
    autenticacion(real);
    while(m1!=5){
        m1=menuP();
        if(m1>0 && m1<5){
            do{
                system(C);
                contador[1]=revisarPedidos(pedido, contador[0]);
                margen(M);
                if(m1==1){
                    i=alta(pedido, contador[0]);
                    contador[0]++;
                }else if(contador[1] || (m1==3 && contador[0])){
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
                    printf("\n\t\tNo hay pedidos disponibles para ingresar a esta opcion");
                    margen(M);
                    esperar();
                    i=0;
                }
            }while(i);
        }else if(m1 != 5){
            margen(M);
            printf("\n\t\tOpcion incorrecta, vuelva a intentarlo");
            esperar();
        }
    }
    return 0;
}//fin main
//funciones
int revisarPedidos(struct pedidos pedido[], int contador){
    int i=0, consec=0, sec=0;
    margen(M);
    printf("\n\t\tPedidos vigentes: ");
    for(i=0;i<contador;i++)
        if(pedido[i].codigoPedido){
            if(consec%9==0 && consec)
                printf("\n\t\t\t ");
            printf("[%d], ",pedido[i].codigoPedido);
            consec++;
        }
    if(!consec)
        printf("Sin pedidos vigentes");
    if(consec != contador){
        margen(M);
        printf("\n\t\tPedidos cancelados: ");
        for(i=0;i<contador;i++)
            if(!pedido[i].codigoPedido){
                if(sec%9==0 && sec)
                    printf("\n\t\t\t ");
                printf("[%d], ",i+1);
                sec++;
            }
    }
    return consec;
}//fin revisar pedido
int preguntarPedido(int m1, struct pedidos pedido[], int contador){
//retorna 0 si se quiere salir, -1 si esta cancelado, -2 si no es valido, o el numero de pedido
    int r=0;
    if(m1==2) printf("\n\t\t\t\tBaja de Pedidos");
    if(m1==3) printf("\n\t\t\t\tConsulta de Pedidos");
    if(m1==4) printf("\n\t\t\t\tModificacion de Pedidos");
    margen(M);
    printf("\n\t\tPuedes presionar 0 para regresar al menu principal");
    margen(M);
    printf("\n\t\tCual pedido quieres: ");
    fflush(stdin);
    scanf("%d",&r);
    margen(M);
    if(r>0 && r <= contador){
        dibujarPedido(pedido[r-1],r-1);
        if(!pedido[r-1].codigoPedido) r=-1;
    }else if(r > contador){
        margen(M);
        printf("\n\t\tPedido no valido, aun no se llega a ese numero de pedido");
        r=-2;
        esperar();
    }
    return r;
}//fin preguntar pedido
void margen(int m){
    int i=0;
    printf("\n\t");
    for(i=0;i<m;i++)
        printf("_");
    printf("\n");
}//fin margen
void esperar(){
    fflush(stdin);
    margen(M);
    printf("\n\n\t\t\tPresiona enter para continuar: ");
    getchar();
    if(!W) getchar();
    system(C);
}//fin esperar
int autenticacion(struct usuario real){
    struct usuario nuevo;
    int cont=1, nom=0, pas=0;
    system(C);
    while(cont){
        margen(M);
        printf("\n\t\t\t\t\tFenix 1.1");
        margen(M);
        printf("\n\n\t\t\t\tHola, Bienvenido al sistema:");
        printf("\n\t\t\t___________________________________________");
        printf("\n\n\n\t\tUsuario: ");
        fflush(stdin);
        scanf("%s", nuevo.nombre);
        nom=revisarString(real.nombre,nuevo.nombre);
        if(nom){
            printf("\n\n\t\tPassword: ");
            fflush(stdin);
            scanf("%s", nuevo.pass);
            pas=revisarString(real.pass,nuevo.pass);
        }
        margen(M);
        if(!nom)
            printf("\n\t\t\tUsuario incorrecto, vuelva a intentarlo");
        else if(!pas)
            printf("\n\t\t\tPassword incorrecto, vuelva a intentarlo");
        else if( nom && pas){
            cont=0;
            printf("\n\t\t\tDatos correctos, Bienvenido %s.",real.nombre);
        }
        esperar();
    }
    return 1;
}//fin autenticacion
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
}//fin revisa string
int menuP(void){
    int op=0;
    system(C);
    margen(M);
    printf("\n\t\t\t\tFenix 1.1");
    margen(M);
    printf("\n\n\t\t1-Altas\n\t\t2-Bajas\n\t\t3-Consultas\n\t\t4-Modificaciones\n\t\t5-Salir");
    margen(M);
    printf("\n\n\t\t\tElige una opcion: ");
    scanf("%d",&op);
    system(C);
    return op;
}//fin menu principal
void cin(char variable[]){
    fflush(stdin);
    if(W)
        gets(variable);
    else
        scanf("%s",variable);
}//fin cin
int datosCliente(int datoMod, struct pedidos pedido[], int contador){
    margen(M);
    if(!datoMod || datoMod==1){
        printf("\n\n\t\tCodigo del cliente: ");
        cin(pedido[contador].cliente.codigoCliente);
    }if(!datoMod || datoMod==2){
        printf("\n\t\tNombre de la empresa: ");
        cin(pedido[contador].cliente.nombreEmpresa);
    }if(!datoMod || datoMod==3){
        printf("\n\t\tNombre del cliente: ");
        cin(pedido[contador].cliente.nombreCliente);
    }if(!datoMod || datoMod==4){
        printf("\n\t\tPuesto: ");
        cin(pedido[contador].cliente.puesto);
    }
    return 0;
}//fin datos clientes
int datosProducto(int datoMod, struct pedidos pedido[], int contador, int i){
    margen(M);
    if(!datoMod || datoMod==1){
        printf("\n\t  %d\tCodigo: ",i);
        cin(pedido[contador].producto[i-1].codigoProducto);
    }if(!datoMod || datoMod==2){
        printf("\n\t\tNombre: ");
        cin(pedido[contador].producto[i-1].nombreProducto);
    }if(!datoMod || datoMod==3){
        printf("\n\t\tPrecio por Unidad: ");
        fflush(stdin);
        scanf("%f",&pedido[contador].producto[i-1].precioUnidad);
    }if(!datoMod || datoMod==4){
        printf("\n\t\tNo. de Unidades: ");
        fflush(stdin);
        scanf("%f",&pedido[contador].producto[i-1].numeroUnidades);
    }
    return 0;
}//fin datos producto
int nuevoProducto(struct pedidos pedido[], int contador){
    char cont='s';
    while(cont=='s'){
        dibujarPedido(pedido[contador], contador);
        pedido[contador].contProd++;
        printf("\n\t\t\t\tNuevo Producto: ");
        datosProducto(0, pedido, contador, pedido[contador].contProd);
        margen(M);
        printf("\n\t\t Agregar otro producto? s/n: ");
        fflush(stdin);
        if(!W) getchar();
        scanf("%c",&cont);
    }
    return 0;
}//fin muevo producto
int alta(struct pedidos pedido[], int contador){
    int i=0;
    char cont='s';
    pedido[contador].contProd=0;
    pedido[contador].codigoPedido=contador+1;
    printf("\n\t\tPedido Nuevo N.- %d",contador+1);
    margen(M);
    printf("\n\t\t\t\tAlta de Cliente: ");
    datosCliente(0, pedido, contador);
    for(i=0;i<L;i++)//inicializar productos en 0
        pedido[contador].producto[i].codigoProducto[0]='\0';
    nuevoProducto(pedido, contador);
    margen(M);
    printf("\t\tQuieres dar de alta un nuevo pedido? s/n: ");
    fflush(stdin);
    if(!W) getchar();
    scanf("%c",&cont);
    if(cont=='s') return 1;
    else return 0;
}//fin alta pedido
void pinta(int x, int y){
printf("%c[%d;%df",0x1B,y,x);
}//fin pinta
void dibujarPedido(struct pedidos pedido, int contador){
    int i=0;
    system(C);
    for(i=3;i<20;i++){
        pinta(9,i);
        printf("|");
        pinta(81,i);
        printf("|");
    }
    pinta(1,1);
    if(!pedido.codigoPedido){
        margen(M);
        printf("\n\t\t\t\tPEDIDO CANCELADO");
    }
    margen(M);
    printf("\n\t\tPedido N.- %d",contador+1);
    margen(M);
    printf("\n\t\t\t\tDatos del cliente:\n");
    printf("\n\t\tCodigo: \t\t\tNombre empresa: ");
    printf("\n\n\t\t%s",pedido.cliente.codigoCliente);
    pinta(49,11);
    printf("%s",pedido.cliente.nombreEmpresa);
    printf("\n\t\t_______________________\t\t________________________");
    printf("\n\n\t\tNombre Cliente:\t\t\tPuesto:");
    printf("\n\n\t\t%s",pedido.cliente.nombreCliente);
    pinta(49,16);
    printf("%s",pedido.cliente.puesto);
    printf("\n\t\t_______________________\t\t________________________");
    margen(M);
    printf("\t|  #  | Codigo:      | Nombre:            | Precio:      | Cantidad:");
    margen(M);
    /*
    codigo:19
    nombre:35
    precio:51
    cantidad:67
    */
    for(i=0;i<pedido.contProd;i++){
        if(pedido.producto[i].codigoProducto[0] != '\0'){
            printf("\n\t|  %d",i+1);
            pinta(15,22+i);
            printf("| %s",pedido.producto[i].codigoProducto);
            pinta(30,22+i);
            printf("| %s",pedido.producto[i].nombreProducto);
            pinta(51,22+i);
            printf("| %.2f",pedido.producto[i].precioUnidad);
            pinta(66,22+i);
            printf("| %.2f",pedido.producto[i].numeroUnidades);
            pinta(81,22+i);
            printf("|");
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
    printf("\n\t\t Revisa el pedido..., Aun quieres eliminarlo? s/n: ");
    fflush(stdin);
    if(!W) getchar();
    scanf("%c",&cont);
    if(cont=='s'){
        pedido[contador[2]-1].codigoPedido=0;
        margen(M);
        printf("\n\t\t\t\tPedido eliminado.");
    }
    margen(M);
    printf("\n\t\tDesea dar otro pedido de baja? s/n: ");
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
    int i=0, num[4]={-1,-1,-1,-1};
    char cont='s';
    do{
        dibujarPedido(pedido[contador[2]-1],contador[2]-1);
        margen(M);
        if(num[0]==-1){
            printf("\n\n\t\t Que quieres modificar?");
            printf("\n\t\t_________________________________");
            printf("\n\n\t\t\t1-Datos del cliente.\n\t\t\t2-Productos.\n\t\t\t3-Regresar.");
            printf("\n\t\t_________________________________");
            printf("\n\n\t\t Elige una opcion: ");
            fflush(stdin);
            scanf("%d",&num[0]);
        }else if(num[0] == 1){ //cliente
            if(num[1]==-1){
                printf("\n\n\t\t Que quieres modificar?");
                printf("\n\t\t_________________________________");
                printf("\n\n\t\t\t1-Codigo del cliente.\n\t\t\t2-Nombre de la empresa.\n\t\t\t3-Nombre del cliente.\n\t\t\t4-Puesto\n\t\t\t5-Regresar");
                printf("\n\t\t_________________________________");
                printf("\n\n\t\t Elige una opcion: ");
                fflush(stdin);
                if(!W) getchar();
                scanf("%d",&num[1]); 
            }else if(num[1] > 0 && num[1] <5){
                datosCliente(num[1], pedido, contador[2]-1);
                num[1]=-1;
            }else if(num[1] == 5){
                num[1]=-1;
                num[0]=-1;
            }else 
                num[1]=-2;
        }else if(num[0] == 2){//producto
            if(num[1]==-1){
                printf("\n\n\t\t Opciones: ");
                printf("\n\t\t_________________________________");
                printf("\n\n\t\t\t1-Modificar Producto\n\t\t\t2-Agregar producto\n\t\t\t3-Eliminar producto\n\t\t\t4-Regresar");
                printf("\n\t\t_________________________________");
                printf("\n\n\t\t Elige una opcion: ");
                fflush(stdin);
                scanf("%d",&num[1]);
            }else if(num[1] > 0 && num[1] < 4){
            //ver si es modificacion o eliminacion de producto revisar primero que haya producto
                    if(num[1] == 1 || num[1] == 3){
                        if(num[2] == -1){
                            if(!pedido[contador[2]-1].contProd){
                                printf("\n\t\t Este pedido no tiene productos para realizar esta opcion");
                                num[1]=-1;
                                esperar();
                            }else{
                                printf("\n\t\tPuedes presionar 0 para regresar.");
                                margen(M);
                                printf("\n\t\tProductos disponibles: \n\n\t\t");
                                for(i=0;i<pedido[contador[2]-1].contProd;i++)
                                    if(pedido[contador[2]-1].producto[i].codigoProducto[0] != '\0')
                                        printf("[%d], ",i+1);
                                margen(M);
                                printf("\n\n\t\tElige un numero de producto: ");
                                fflush(stdin);
                                scanf("%d",&num[2]);
                            }
                        }else if(num[2]>0 && num[2]<=pedido[contador[2]-1].contProd){
                            if(num[1]==1){
                                if(num[3]==-1){
                                    printf("\n\t\t\tQue quieres modificar?");
                                    printf("\n\t\t_________________________________");
                                    printf("\n\n\t\t1-Codigo\n\t\t2-Nombre\n\t\t3-Precio\n\t\t4-Cantidad\n\t\t5-Regresar");
                                    printf("\n\t\t_________________________________");
                                    printf("\n\n\t\t\t Elige una opcion: ");
                                    fflush(stdin);
                                    scanf("%d",&num[3]);
                                }else if(num[3]>0 && num[3]<5){ //modificar producto
                                    datosProducto(num[3], pedido, contador[2]-1, num[2]);
                                    num[3]=-1;
                                }else if(num[3] == 5){
                                    num[3]=-1;
                                    num[2]=-1;
                                }else
                                    num[3]=-2;
                            }else if(num[1]==3){
                                eliminarProducto(pedido, contador[2]-1, num[2]);
                                num[2]=-1;
                            }
                        }else if(!num[2]){
                            num[2]=-1;
                            num[1]=-1;
                        }else
                            num[2]=-2;
                    }else if(num[1]==2){ //agregar nuevo producto
                        nuevoProducto(pedido, contador[2]-1);
                        num[1]=-1;
                    }else if(num[2] ==5){
                        num[2]=-1;
                        num[1]=-1;
                        num[0]=-1;
                    }else
                        num[2]=-2;
            }else if(num[1] == 4){
                num[1]=-1;
                num[0]=-1;
            }else 
                num[1]=-2;
        }else if(num[0] != 3){
            num[0]=-2;
        }
        for(i=0;i<4;i++)
            if(num[i]==-2){
                margen(M);
                printf("\n\t\tOpcion invalida, vuelve a intentarlo.");
                esperar();
                num[i]=-1;
            }
    }while(num[0] != 3);
    margen(M);
    printf("\n\t\tQuieres modificar otro pedido? s/n: ");
    fflush(stdin);
    if(!W) getchar();
    scanf("%c",&cont);
    if(cont=='s')
        return 1;
    return 0;
}//termina modifica
int eliminarProducto(struct pedidos pedido[], int contador, int pi){
    int i=0;
    pedido[contador].contProd--;
    for(;i<pedido[contador].contProd;i++){
        if( i >= pi-1 ){
            pedido[contador].producto[i]=pedido[contador].producto[i+1];
        }
    }
    pedido[contador].producto[pedido[contador].contProd].codigoProducto[0]='\0';
    return 0;
}//termina eliminarProducto
//////////////////////////////termina programa
