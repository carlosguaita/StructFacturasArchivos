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
    printf("Ingrese la stock del producto (1-100): ");
    producto.cantidad = leerEnteroConRango(1,100);
    guardarProducto(&producto);
}

void crearFactura(){
    Factura factura;
    Cliente clientes[5];
    Producto productos[5];
    int cClientes = obtenerClientes(clientes);
    int cProductos = obtenerProductos(productos);

    printf("Seleccione un cliente:\n");
    for (int i = 0; i < cClientes; i++)
    {
        printf("%d. %s\n",i+1,clientes[i].nombre);
    }
    int opcCliente = leerEnteroConRango(1,cClientes);
    factura.cliente = clientes[opcCliente-1];

    printf("Ingrese el numero de productos en la factura (1-5): ");
    factura.numProd = leerEnteroConRango(1,5);

    for (int i = 0; i < factura.numProd; i++)
    {
        printf("Seleccione el producto %d:\n",i+1);
        for (int j = 0; j < cProductos; j++)
        {
            if(productos[j].activo==1){
                printf("%d. %s\n",j+1,productos[j].nombre);
            }
        }
        int opcProducto = leerEnteroConRango(1,cProductos);
        strcpy(factura.item[i].nombre,productos[opcProducto-1].nombre);
        factura.item[i].precio = productos[opcProducto-1].precio;
        printf("Ingrese la cantidad del producto %s (1-%d): ",productos[opcProducto-1].nombre,productos[opcProducto-1].cantidad);
        factura.item[i].cantidad = leerEnteroConRango(1,productos[opcProducto-1].cantidad);
        editarProducto(productos[opcProducto-1].id,factura.item[i].cantidad);
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

void listarFacturas(Factura *facturas){
    int c = obtenerFacturas(facturas);
    for (int i = 0; i < c; i++)
    {
        printf("Factura #%d\n",i+1);
        printf("Cliente: %s\n",facturas[i].cliente.nombre);
        printf("Items:\n");
        printf("Nombre\t\tPrecio\t\tCantidad\t\tTotal\n");
        float totalFactura = 0;
        for (int j = 0; j < facturas[i].numProd; j++)
        {
            float totalItem = facturas[i].item[j].precio * facturas[i].item[j].cantidad;
            totalFactura += totalItem;
            printf("%s\t\t%.2f\t\t%d\t\t%.2f\n",
                   facturas[i].item[j].nombre,
                   facturas[i].item[j].precio,
                   facturas[i].item[j].cantidad,
                   totalItem);
        }
        printf("Total Factura: %.2f\n",totalFactura);
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

int obtenerFacturas(Factura *facturas){
    FILE *f;
    f = fopen("facturas.dat","rb");
    if (f==NULL)
    {
        printf("No se puede abrir el archivo\n");
        return 0;
    }
    int count = fread(facturas,sizeof(Factura),5,f);
    fclose(f);
    return count;
}

int buscarProducto(Producto *producto, int id){
    int posicion = -1;
    int flag=0;
    FILE *f = fopen("productos.dat","rb");

    while(fread(producto,sizeof(Producto),1,f)==1){
        if(producto->id == id){
            flag=1;
            break;
        }
        posicion=ftell(f);
    }
    if (flag==0)
    {
        posicion=-1;
    }
    fclose(f);
    return posicion;
}

void editarProducto(int id, int cantidad){
    Producto producto;
    int posicion = buscarProducto(&producto,id);
    if (posicion==-1)
    {
        printf("Producto no encontrado\n");
        return;
    }
    if (producto.cantidad < cantidad)
    {
        printf("No hay suficiente stock\n");
        return;
    }
    producto.cantidad -= cantidad;

    FILE *f = fopen("productos.dat","rb+");
    fseek(f,posicion,SEEK_SET);
    fwrite(&producto,sizeof(Producto),1,f);
    fclose(f);
}