#include <stdio.h>
#include <string.h>
#include "funciones.h"

void leerCadena(char *cadena, int n){
    fflush(stdin);
    fgets(cadena,n,stdin);
    int len = strlen(cadena) - 1;
    cadena[len] = '\0';
}

int leerEnteroConRango(int inicio, int fin){
    int num;
    int val;
    do{
        val = scanf("%d",&num);
        if (val!=1 || num < inicio || num > fin){
            printf("El valor ingresado es incorrecto\n");
        }
    }while(val!=1 || num < inicio || num > fin);
    return num;
}

float leerFlotanteConRango(float inicio, float fin){
    float num;
    int val;
    do{
        val = scanf("%f",&num);
        if (val!=1 || num < inicio || num > fin){
            printf("El valor ingresado es incorrecto\n");
        }
    }while(val!=1 || num < inicio || num > fin);
    return num;
}

int menu(){
    int opc;
    printf("Seleccione una opcion:\n");
    printf("1.Crear cliente\n");
    printf("2.Mostrar clientes\n");
    printf("3.Crear producto\n");
    printf("4.Mostrar productos\n");
    printf("5.Editar producto\n");
    printf("6.Crear factura\n");
    printf("7.Mostrar facturas\n");
    printf("8.Salir\n");
    printf(">> ");
    opc = leerEnteroConRango(1,8);
    return opc;
}

void crearCliente(){
    Cliente cliente;
    printf("Ingrese el nombre del cliente: ");
    leerCadena(cliente.nombre,20);
    printf("Ingrese la cedula del cliente: ");
    cliente.cedula = leerEnteroConRango(1,999999);
    printf("Ingrese la direccion del cliente: ");
    leerCadena(cliente.direccion,50);
    guardarCliente(&cliente);

}

void crearProducto(){
    Producto producto;
    printf("Ingrese el ID del producto (1-10): ");
    producto.id=leerEnteroConRango(1,10);
    printf("Ingrese el nombre del producto: ");
    leerCadena(producto.nombre,50);
    printf("Ingrese el precio del producto (1-1000): ");
    producto.precio = leerFlotanteConRango(1,1000);
    producto.activo=1;
    //printf("Ingrese la cantidad del producto (1-100): ");
    producto.cantidad = 0;
    guardarProducto(&producto);
}

void crearFactura(){
    int opc;
    Factura factura;
    printf("Seleccione el cliente: \n");
    Cliente clientes[5];
    listarClientes(clientes);
    printf(">> ");
    opc=leerEnteroConRango(0,5);
    factura.cliente=clientes[opc];
    printf("Cuantos productos desea incluir en la factura: ");
    factura.numProd = leerEnteroConRango(0,4);
    Producto productos[5];
    printf("Seleccione el producto: \n");
    listarProductos(productos);
    for (int i = 0; i < factura.numProd; i++)
    {
        printf(">> ");
        opc = leerEnteroConRango(0,4);
        factura.productos[i]=productos[opc];
    }
    printf("----------Factura-----------\n");
    printf("Nombre: %s\n",factura.cliente.nombre);
    printf("Cedula: %d\n",factura.cliente.cedula);
    printf("Direccion: %s\n",factura.cliente.direccion);
    printf("#\tID\t\tNombre\t\tPrecio\n");
    for (int i = 0; i < factura.numProd; i++)
    {
        printf("%d\t%d\t\t%s\t\t%.2f\n",i,
            factura.productos[i].id,
            factura.productos[i].nombre,
            factura.productos[i].precio);
    }
    guardarFactura(&factura);
}

void listarClientes(Cliente *clientes){
    //Cliente clientes[5];
    int c = obtenerClientes(clientes);
    printf("#\tCedula\t\tNombre\t\tDireccion\n");
    for (int i = 0; i < c; i++)
    {
        printf("%d\t%d\t\t%s\t\t%s\n",i,
                              clientes[i].cedula,
                              clientes[i].nombre,
                              clientes[i].direccion);
    }
}

void listarProductos(Producto *productos){
    int c = obtenerProductos(productos);
    printf("#\tID\t\tNombre\t\tPrecio\n");
    for (int i = 0; i < c; i++)
    {
        if(productos[i].activo==1){
            printf("%d\t%d\t\t%s\t\t%.2f\n",i,
                                            productos[i].id,
                                            productos[i].nombre,
                                            productos[i].precio);
        }
    }
    
}


void guardarCliente(Cliente *cliente){
    FILE *f;
    f = fopen("clientes.dat","ab+");
    if (f==NULL)
    {
        printf("No se puede abrir el archivo\n");
        return;
    }
    fwrite(cliente,sizeof(Cliente),1,f);
    fclose(f);
}

void guardarProducto(Producto *producto){
    FILE *f;
    f = fopen("productos.dat","ab+");
    if (f==NULL)
    {
        printf("No se puede abrir el archivo\n");
        return;
    }
    fwrite(producto,sizeof(Producto),1,f);
    fclose(f);
}

void guardarFactura(Factura *factura){
    FILE *f;
    f = fopen("facturas.dat","ab+");
    if (f==NULL)
    {
        printf("No se puede abrir el archivo\n");
        return;
    }
    fwrite(factura,sizeof(Factura),1,f);
    fclose(f);
}

int obtenerClientes(Cliente *clientes){
    FILE *f;
    f = fopen("clientes.dat","rb");
    if (f==NULL)
    {
        printf("No se puede abrir el archivo\n");
        return 0;
    }
    int count = fread(clientes,sizeof(Cliente),5,f);
    fclose(f);
    return count;
}

int obtenerProductos(Producto *productos){
    FILE *f;
    f = fopen("productos.dat","rb");
    if (f==NULL)
    {
        printf("No se puede abrir el archivo\n");
        return 0;
    }
    int count = fread(productos,sizeof(Producto),5,f);
    fclose(f);
    return count;
}