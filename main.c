#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    int opc1, opc2, opc3;

    do{

        int opc = menu();

        switch (opc)
        {
        case 1:
            crearCliente();
            break;
        case 2:
            Cliente clientes[5];
            listarClientes(clientes);
            break;
        case 3:
            
            crearProducto();
            break;
        case 4:
            Producto productos[5];
            listarProductos(productos);
            break;
        case 6:
            crearFactura();
            break;
        case 7:
            Factura facturas[5];
            listarFacturas(facturas);
            break;
        default:
            break;
        }
        printf("Desea seleccionar otra opcion 1.Si/2.No: ");
        opc2 = leerEnteroConRango(1,2);
    }while(opc2==1);



    return 0;
}