#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <cctype>
using namespace std;

typedef enum {NADA,Hombre,Wookie,Hutt,Ewok,Morador_Arena}Tclientela;
struct lista{                     //estructura con los elementos del carrito
    int cod_bebida;
    string nom_bebida;
    string cliente;
    int num_unidades;
    float precio_unidad;
    Tclientela listacliente;
};

typedef array <lista,50> Carrito;   //array de registros para guardar la informacion de lso pedidos

void cadena_a_enum(Carrito &t,string c,int numero_Bebidas,Tclientela &clientes)
{
        if(c=="Hombre") clientes=Hombre;
        else if(c=="Wookie") clientes=Wookie;
        else if(c=="Hutt") clientes=Hutt;
        else if(c=="Ewok") clientes=Ewok;
        else if(c=="Morador_arena") clientes=Morador_Arena;
        else if(c==" ") clientes=NADA;
        else cout<<"error al poner el nombre";
}
void inicializar_carrito(Carrito &t)
{
    for(int j=0;j<50;j++)
    {
        t[j].cod_bebida=0;
        t[j].nom_bebida=" ";
        t[j].cliente=" ";
        t[j].num_unidades=0;
        t[j].precio_unidad=0;
        t[j].listacliente=NADA;
    }
}
void insertar_bebida(string &nombre,int &num_bebidas,Carrito &t) //insertar bebida
{
    cout<<"introduce numero de bebidas"<<endl;
    cin>>num_bebidas;
    cin.ignore();
    for(int i=0; i<num_bebidas;i++)
       {
        if(i>50)cout<<"tamaño maximo del carrito superado"<<endl;
        else
        {
            cout<<"introduce codigo bebida"<<endl;
            cin>> t[i].cod_bebida;
            cin.ignore();
            cout<<"introduce nombre del cliente"<<endl;
            getline(cin,nombre,'\n');
            t[i].cliente=nombre;
            cout<<"introduce nombre bebida"<<endl;
            getline(cin,t[i].nom_bebida,'\n');
            cout<<"introduce numero unidades"<<endl;
            cin>> t[i].num_unidades;
            cin.ignore();
            cout<<"introduce precio bebida"<<endl;
            cin>> t[i].precio_unidad;
            cin.ignore();
            cadena_a_enum(t,t[i].cliente,num_bebidas,t[i].listacliente);
            cout<<"ha finalizado el pedido:"<<i<<endl;
        }
       }
}

void listar_pedidos(Carrito & t)
{
    int comprobar=0, i=0;
    while(t[i].num_unidades!=0 && i<50)
    {
        i++;
        comprobar=comprobar+1;
    }
    cout<<"el numero de elementos es:" << comprobar<<endl;

    cout<<"SU CARRITO CONTINE"<<endl;
    for(int h=0; h<comprobar;h++)
    {
        cout<<"codigo bebida"<<" "<<t[h].cod_bebida<<endl;
        cout<<" nombre del cliente"<<" "<<t[h].cliente<<endl;
        cout<<" nombre bebida"<<" "<<t[h].nom_bebida<<endl;
        cout<<" numero unidades"<<" "<<t[h].num_unidades<<endl;
        cout<<" precio bebida"<<" "<<t[h].precio_unidad<<endl;
        cout<<" enumerado"<<" "<<t[h].listacliente<<endl;
    }
}
int buscar(Carrito & t)
{
    int codigo,i;
    i=0;
    cout<<"introduce el codigo de la bebida: "<<endl;
    cin>>codigo;
    cin.ignore();
    while(t[i].cod_bebida != codigo)
    {
        i++;
    }
    cout<<"posicion del carrito: "<<i<<endl;
    return i;
}
void borrar(Carrito & t,int numero,int pos)
{

    cout<<"introduce nuevo numero unidades de bebida: "<<endl;
    cin>>numero;
    cin.ignore();
    if(numero==0)
    {
        t[pos].cod_bebida=0;
        t[pos].nom_bebida=" ";
        t[pos].cliente=" ";
        t[pos].num_unidades=0;
        t[pos].precio_unidad=0;
        t[pos].listacliente=NADA;
    }
    else
    {
        t[pos].num_unidades=numero;
    }
}
void cambiar_numero_unidades(Carrito &t,int numero_nuevo)
{
    int posicion;
    posicion=buscar(t);
    cout<<"codigo bebida"<<" "<<t[posicion].cod_bebida<<endl;
    cout<<" nombre del cliente"<<" "<<t[posicion].cliente<<endl;
    cout<<" nombre bebida"<<" "<<t[posicion].nom_bebida<<endl;
    cout<<" numero unidades"<<" "<<t[posicion].num_unidades<<endl;
    cout<<" precio bebida"<<" "<<t[posicion].precio_unidad<<endl;
    cout<<" enumerado"<<" "<<t[posicion].listacliente<<endl;
    borrar(t,numero_nuevo,posicion);
    cout<<"codigo bebida"<<" "<<t[posicion].cod_bebida<<endl;
    cout<<" nombre del cliente"<<" "<<t[posicion].cliente<<endl;
    cout<<" nombre bebida"<<" "<<t[posicion].nom_bebida<<endl;
    cout<<" numero unidades"<<" "<<t[posicion].num_unidades<<endl;
    cout<<" precio bebida"<<" "<<t[posicion].precio_unidad<<endl;
    cout<<" enumerado"<<" "<<t[posicion].listacliente<<endl;
}
void pagar_cuenta(Carrito & t,int numero_Bebidas)
{
    int total_compra=0;
    bool x=false;
    char c;
    for(int j=0; j<=numero_Bebidas; j++)
    {
        total_compra=total_compra+(t[j].num_unidades*t[j].precio_unidad);
    }
    cout <<"el precio total de su compra es : "<<total_compra<<endl;
    cout<<"Desea pagar la cuenta y vaciar el carrito (S) o seguir comprando (N)"<<endl;
    cin>>c;
    cin.ignore();
    if(c=='S')
    {
        cout<<"ha pagado su cuenta"<<endl;
        inicializar_carrito(t);
    }
    else    cout<<"continue comprando"<<endl;
}
int main()
{
    cout << "elaborador por : David Calabres Gonzalez  Curso: 1º"<<endl;
    cout << "Fecha: 29/09/1996  Especialidad: GISE"<<endl;
    cout << "Cantina del Puerto Espacial de Mos Easly"<<endl;
    char a;
    int numero_de_bebidas,nuevonumbebida;
    Carrito carrito;
    string nombre_de_cliente;
    inicializar_carrito(carrito);
    do
    {
        cout<<"A. insertar una bebida al carrito"<<endl;
        cout<<"B. lista de todas las bebidas del carrito"<<endl;
        cout<<"C. cambiar numero de unidades de una bebida"<<endl;
        cout<<"D. pagar la cuenta"<<endl;
        cout<<"X. salir del programa"<<endl;
        cin>>a;
        a=toupper(a);
        switch(a)
        {
            case 'A': insertar_bebida(nombre_de_cliente,numero_de_bebidas,carrito); break;
            case 'B': listar_pedidos(carrito); break;
            case 'C': cambiar_numero_unidades(carrito,nuevonumbebida);break;
            case 'D': pagar_cuenta(carrito,numero_de_bebidas);break;
            default: cout<<"invalido"<<endl;
        }
    }while(a!='X');
    return 0;

}
