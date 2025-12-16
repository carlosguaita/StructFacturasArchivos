typedef struct{
    char nombre[20];
    int cedula;
    char direccion[50];
}Cliente;

typedef struct{
    int id;
    char nombre[50];
    float precio;
    int activo;
    int cantidad;
}Producto;

typedef struct{
    Cliente cliente;
    int numProd;
    Producto productos[5];
}Factura;

void leerCadena(char *cadena, int n);
int leerEnteroConRango(int inicio, int fin);
float leerFlotanteConRango(float inicio, float fin);
int menu();
void crearCliente();
void listarClientes(Cliente *clientes);
void guardarCliente(Cliente *cliente);
int obtenerClientes(Cliente *clientes);
void crearProducto();
void guardarProducto(Producto *producto);
int obtenerProductos(Producto *productos);
void listarProductos(Producto *productos);
void crearFactura();
void guardarFactura(Factura *factura);