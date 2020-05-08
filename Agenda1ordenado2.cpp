/*

    Ejercicio de trabajo en clase.
    Agenda según el método 1.

    Todas las operaciones del menú devuelven si han podido realizarse o no,
    incluso ImprimirAgenda que siempre se puede hacer.

*/


#include <iostream>
#include <string>
#include <array>
using namespace std;
// -- Constantes -------
const unsigned MAX_PERSONAS = 5;

// -- Tipos ------------
typedef struct
{
    unsigned num;
    string calle;
    string piso;
    unsigned cp;
    string ciudad;
} TDireccion;
typedef struct
{
    string nombre;
    string tel;
    TDireccion dir;
} TPersona;
typedef array <TPersona,MAX_PERSONAS> TListPers;
typedef struct
{
    unsigned nPers;
    TListPers pers;
} TAgenda;

// -- Prototipos --------

void Inicializar (TAgenda& ag);
bool Llena (const TAgenda& ag);
void LeerDireccion (TDireccion& dir);
void LeerPersona (TPersona& per);
void EscribirDireccion (const TDireccion &dir);
void EscribirPersona (const TPersona &per);
unsigned BuscarPersona (string nombre, const TAgenda& ag);
bool InsertarOrdenado3(const TPersona &per, TAgenda& ag);
bool EliminarOrdenado(string nombre, TAgenda& ag);
bool BuscarOrdenado(string nom, const TAgenda& ag, unsigned &pos);
bool ModificarPersona (const TPersona &nuevo, TAgenda& ag);
bool ModificarPersona2 (const TPersona &nuevo, TAgenda& ag);
bool DevolverPersona (string nombre, const TAgenda& ag, TPersona& per);
void ImprimirAgenda (const TAgenda& ag);
unsigned Menu ();

// -- Principal --------
int main ()
{
    TAgenda ag;
    unsigned opcion;
    TPersona per;
    string nombre;
    bool ok;
    Inicializar(ag);
    do
    {
        ok= true;
        opcion = Menu();
        switch (opcion)
        {
        case 1:
            cout << "Introduzca los datos de la TPersona" << endl;
            LeerPersona(per);
            ok = InsertarOrdenado3(per, ag);
            break;
        case 2:
            cout << "Introduzca Nombre" << endl;
            cin >> nombre;
            ok = DevolverPersona(nombre, ag, per);
            if (ok)
            {
                EscribirPersona(per);
            }
            break;

        case 3:
            cout << "Introduzca Nombre" << endl;
            cin >> nombre;
            ok = EliminarOrdenado(nombre, ag);
            break;
        case 4:
            cout << "Nuevos datos de la TPersona" << endl;
            LeerPersona(per);
            ok = ModificarPersona2(per, ag);
            break;
        case 5:
            ImprimirAgenda(ag);
            ok = true;
            break;
        }
        if (!ok)
        {
            cout<<"\n La operación no se ha podido realizar\n";
        }
    }
    while (opcion != 0 );
}




// -- Subalgoritmos ----
void Inicializar (TAgenda& ag)
{
    ag.nPers = 0;
}

void LeerDireccion (TDireccion& dir)
{
    cout<<" Calle: ";
    cin >> dir.calle;
    cout<<" num: ";
    cin >> dir.num;
    cout<<" piso: ";
    cin >> dir.piso;
    cout<<" CP: ";
    cin >> dir.cp;
    cout<<" Ciudad: ";
    cin >> dir.ciudad;
}

void LeerPersona (TPersona& per)
{
    cout<<" Nombre: ";
    cin >> per.nombre;
    cout<<" telefono: ";
    cin >> per.tel;
    LeerDireccion(per.dir);
}

void EscribirDireccion (const TDireccion &dir)
{
    cout << "\nDirección: ";
    cout << dir.calle << " ";
    cout << dir.num << " ";
    cout << dir.piso << " ";
    cout << dir.cp << " ";
    cout << dir.ciudad << " ";
}

void EscribirPersona (const TPersona &per)
{
    cout << per.nombre << " ";
    cout << per.tel << " ";
    EscribirDireccion(per.dir);
    cout << endl;
}

// Busca una TPersona en la TAgenda
// Devuelve su posicion si se encuentra, o bien >= ag.nPers en otro caso
unsigned BuscarPersona (string nombre, const TAgenda& ag) // En listas ordenadas hay formas más eficientes. Lo dejo para comparar, pero no lo uso
{
    unsigned i = 0;
    while ((i < ag.nPers) && (nombre != ag.pers[i].nombre))
    {
        i++;
    }
    return i;
}

//Ojo, búsqueda secuencial, poco eficiente.
bool BuscarOrdenado(string nom, const TAgenda& ag, unsigned &pos)
{
    bool ok = false;
    pos = 0;
    while ((pos<ag.nPers)&&(ag.pers[pos].nombre<nom))
    {
        pos++;
    }
    if ((pos<ag.nPers)&&(ag.pers[pos].nombre==nom))   //La persona existe
    {
        ok = true;
    }
    return ok;
}

bool InsertarOrdenado3(const TPersona &per, TAgenda& ag)
{
    unsigned i,pos=0;
    bool ok = true, existe;
    if (Llena(ag))
    {
        ok = false;
    }
    else
    {
        //Búsqueda de la posición
        existe = BuscarOrdenado(per.nombre, ag, pos);
        if (!existe)
        {
            // No existe. Hay que abrir hueco
            for(i=ag.nPers; i>pos; i--)
            {
                ag.pers[i] = ag.pers[i-1];
            }
            ag.pers[pos]=per;
            ag.nPers++;
        }
        ok = !existe;

    }
    return ok;
}

bool EliminarOrdenado(string nombre, TAgenda& ag)
{
    unsigned pos,i;
    bool ok;
    ok = BuscarOrdenado(nombre, ag, pos); //BuscarPersona funciona pero es menos eficiente. Lo mejor, búsqueda binaria
    if (ok)      // Elimino cerrando el hueco
    {
        for (i=pos; i<ag.nPers-1; i++)
        {
            ag.pers[i]=ag.pers[i+1];
        }
        ag.nPers--;
    }
    return ok;
}



bool ModificarPersona (const TPersona &nuevo, TAgenda& ag) // Poco eficiente
{
    bool ok;
    ok=EliminarOrdenado(nuevo.nombre, ag); // Ok no sirve
    ok=InsertarOrdenado3(nuevo, ag); // se da valor a ok
    return ok;
}

bool Llena (const TAgenda& ag)
{

    return (ag.nPers == MAX_PERSONAS);

}

bool ModificarPersona2 (const TPersona &nuevo, TAgenda& ag) // Más eficiente
{
    bool ok;
    unsigned pos,i;
    ok = BuscarOrdenado(nuevo.nombre, ag, pos);
    if (ok)
    {
        ag.pers[pos]=nuevo; // Está y lo modifico
    }
    else
    {
        if (!Llena(ag))     // hay sitio para añadir
        {
            //abro hueco
            for(i=ag.nPers; i>pos; i--)
            {
                ag.pers[i] = ag.pers[i-1];
            }
            ag.pers[pos]=nuevo;
            ag.nPers++;
            ok = true;
        }
    }
    return ok;
}

bool DevolverPersona (string nombre, const TAgenda& ag, TPersona& per)
{
    unsigned pos;
    bool ok = BuscarOrdenado(nombre, ag, pos);
    if (ok)
    {
        per = ag.pers[pos];
    }
    return ok;
}

void ImprimirAgenda (const TAgenda& ag)
{
    for (unsigned i = 0; i < ag.nPers; i++)
    {
        EscribirPersona(ag.pers[i]);
    }
}

unsigned Menu ()
{
    unsigned opcion;
    cout << endl;
    cout << "1. - Anadir TPersona" << endl;
    cout << "2. - Buscar TPersona" << endl;
    cout << "3. - Borrar TPersona" << endl;
    cout << "4. - Modificar TPersona" << endl;
    cout << "5. - Imprimir TAgenda" << endl;
    cout << "0. - Salir" << endl;
    do
    {
        cout << "Introduzca Opcion: ";
        cin >> opcion;
    }
    while ( ! ((opcion >= 0) && (opcion <= 5)) );
    return opcion;
}

