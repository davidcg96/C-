/*
Nombre y apellidos: David Calabrés González
DNI:77373594-F
Grado:Sistemas Electrónicos
Grupo:B

*/

#include <iostream>
#include <string>
#include <array>
using namespace std;

const int Nintentos=3;
const int Maximo=100;
typedef array <float,Nintentos>Tintentos;
struct TSaltador
{
  string nombre;
  string nacionalidad;
  Tintentos resultados;
};
typedef array <TSaltador,Maximo>TSaltadores;
// typedef TCompeticion ...
struct TCompeticion
{
  TSaltadores saltadores;
  int nsaltadores;
};
//funciones añadidas
bool Buscar(const TCompeticion & lista,const string &Pnombre,int &pos);
void rellenar(TSaltador &s,const string &Pnombre,const string &Pnacion);
void CopiarSaltador(TCompeticion &lista,int pos);
int Maxima_altura(const TCompeticion &lista);
void intercambia(TSaltador &uno,TSaltador &dos);
bool Insertar_Ordenado(const TSaltador & per,TCompeticion &lista);//,const string&Pnombre,const string&Pnacion);
bool Descalificar_Ordenado(TCompeticion&lista,const string&Pnombre);
bool BuscarOrdenado(string nom, const TCompeticion& ag, int &pos);
bool Llena (const TCompeticion& ag);
//funciones
int Menu ();
void MostrarDep(const TSaltador &c);
void Mostrar(const TCompeticion &c);
void Vaciar(TCompeticion & lista);
bool Inscribir(TCompeticion & lista,const string &Pnombre,const string &Pnacion);
bool Prueba(TCompeticion &lista,const string &Pnombre,float salto1,float salto2,float salto3);
bool Descalificar(TCompeticion & lista,const string &Pnombre);
bool Ganador(const TCompeticion &lista,string &Pnombre,string &Pnacion);
bool Nacionalidad(const TCompeticion &lista,TCompeticion &copia,const string &Pnacion,string &nom_gan,string &nac_gan);
void Ordenar(TCompeticion &lista);
// -- Principal --------
int main () {
    TCompeticion c,c1;
    TSaltador s;
    int opcion;
    string nom,nom_dep,nac_dep,nacion,nom_ganador,nom_gc,nac_gc,nac_ganador,nom_desc;
    Vaciar(c);
    Vaciar(c1);
    do {

        opcion = Menu();
        switch (opcion) {
        case 1:   // Mostrar toda la estructura
                Mostrar(c);

            break;
        case 2:    // Inscribir deportista
                cout<<"introducir nombre deportista: ";
                cin>>nom_dep;
                cout<<endl;
                cout<<"introducir nacion deportista: ";
                cin>>nac_dep;
                cout<<endl;
                rellenar(s,nom_dep,nac_dep);
                cout<<Insertar_Ordenado(s,c);

            break;

        case 3:   // Realizar la prueba
                float s1,s2,s3;
                cout<<"introducir nombre deportista: ";
                cin>>nom;
                cout<<endl;
                cout<<"introducir salto 1: ";
                cin>>s1;
                cout<<endl;
                cout<<"introducir salto 2: ";
                cin>>s2;
                cout<<endl;
                cout<<"introducir salto 3: ";
                cin>>s3;
                cout<<endl;
                Prueba(c,nom,s1,s2,s3);

            break;

        case 4:  // Ganador
                Ganador(c,nom_ganador,nac_ganador);
                cout<<"nombre ganador: "<<nom_ganador<<endl;
                cout<<"nacion ganador: "<<nac_ganador<<endl;
            break;

        case 5:  // Nacionalidad
                cout<<"introducir nacion: ";
                cin>>nacion;
                cout<<endl;
                Nacionalidad(c,c1,nacion,nom_gc,nac_gc);
                if(c1.nsaltadores>0)
                {
                  Mostrar(c1);
                  cout<<"nombre ganador: "<<nom_gc<<endl;
                  cout<<"nacion ganador: "<<nac_gc<<endl;
                }
            break;

        case 6:  // descalificar
                cout<<"introducir nombre para descalificar: ";
                cin>>nom_desc;
                cout<<endl;
                Descalificar_Ordenado(c,nom_desc);
            break;
        case 7: Ordenar(c);
                break;

          }
    } while (opcion != 0 );
}

int Menu () {
    int opcion;
    cout << endl;
    cout << "1. - Mostrar todo" << endl;
    cout << "2. - Inscribir_ordenado" << endl;
    cout << "3. - Realizar la prueba" << endl;
    cout << "4. - Ganador" << endl;
    cout << "5. - Nacionalidad" << endl;
    cout << "6. - Descalificar_Ordenado" << endl;
    cout << "7. - Ordenar lista por salto" << endl;
    cout << "0. - Salir" << endl;
    do {
        cout << "Introduzca Opcion: ";
        cin >> opcion;
    } while ( ! ((opcion >= 0) && (opcion <= 7)) );
    return opcion;
}
void MostrarDep(const TSaltador& c)
{
  cout<<"nombre corredor: "<<c.nombre<<endl;
  cout<<"nacionalidad saltador: "<<c.nacionalidad<<endl;
  for(int i=0;i<Nintentos;i++)
  {
    cout<<"salto "<<i<<":"<<c.resultados[i]<<endl;
  }
}

void Mostrar(const TCompeticion &c) {
    int i;

    for(i=0; i< c.nsaltadores ; i++) {
        MostrarDep(c.saltadores[i]); // Muestra un deportista
    }

}
bool Llena (const TCompeticion& ag)
{

    return (ag.nsaltadores == Maximo);

}
void Vaciar(TCompeticion & lista)
{
  lista.nsaltadores=0;
}
bool Buscar(const TCompeticion &lista,const string &Pnombre,int &pos)
{
  int indice=0;
  while(indice<lista.nsaltadores && Pnombre!=lista.saltadores[indice].nombre)
  {
    indice++;
  }
  if(indice<lista.nsaltadores)
  {
    pos=indice;
    //indice=0;
    return true;
  }
  else
    return false;
}
bool BuscarOrdenado(string nom, const TCompeticion& ag, int &pos)
{
    bool ok = false;
    pos = 0;
    while ((pos<ag.nsaltadores)&&(ag.saltadores[pos].nombre<nom))
    {
        pos++;
    }
    if ((pos<ag.nsaltadores)&&(ag.saltadores[pos].nombre==nom))   //La persona existe
    {
        ok = true;
    }
    return ok;
}
void rellenar(TSaltador &s,const string &Pnombre,const string &Pnacion)
{
  s.nombre=Pnombre;
  s.nacionalidad=Pnacion;
  for(int i=0;i<Nintentos;i++)
  {
    s.resultados[i]=0.0;
  }
}
bool Insertar_Ordenado(const TSaltador &per, TCompeticion& ag)
{
    int i,pos=0;
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
            for(i=ag.nsaltadores; i>pos; i--)
            {
                ag.saltadores[i] = ag.saltadores[i-1];
            }
            ag.saltadores[pos]=per;
            ag.nsaltadores++;
        }
        ok = !existe;

    }
    return ok;
}

bool Inscribir(TCompeticion &lista,const string &Pnombre,const string &Pnacion)
{
  int pos;
  if(lista.nsaltadores<Maximo && !Buscar(lista,Pnombre,pos))
  {
    rellenar(lista.saltadores[lista.nsaltadores],Pnombre,Pnacion);
    lista.nsaltadores++;
    return true;
  }
  else
    return false;
}
bool Prueba(TCompeticion &lista,const string &Pnombre,float salto1,float salto2,float salto3)
{
  int pos;
  if(Buscar(lista,Pnombre,pos))
  {
    lista.saltadores[pos].resultados[0]=salto1;
    lista.saltadores[pos].resultados[1]=salto2;
    lista.saltadores[pos].resultados[2]=salto3;
    return true;
  }
  else
    return false;
}
void CopiarSaltador(TCompeticion & lista,int pos)
{

  lista.saltadores[pos].nombre=lista.saltadores[lista.nsaltadores-1].nombre;
  lista.saltadores[pos].nacionalidad=lista.saltadores[lista.nsaltadores-1].nacionalidad;
  for(int i=0;i<Nintentos;i++)
  {
    lista.saltadores[pos].resultados[i]=lista.saltadores[lista.nsaltadores-1].resultados[i];
  }
}
bool Descalificar_Ordenado(TCompeticion & lista,const string &Pnombre)
{
  int pos;
  if(Buscar(lista,Pnombre,pos))
  {
    if(pos==lista.nsaltadores-1)
    {
      lista.nsaltadores--;
    }
    else
    {
      for(int i=pos+1;i<lista.nsaltadores;i++)
      {
        lista.saltadores[i-1]=lista.saltadores[i];
      }
      lista.nsaltadores--;
    }
    return true;
  }
  else
  {
    return false;
  }
}
bool Descalificar(TCompeticion & lista,const string &Pnombre)
{
  int pos;
  if(Buscar(lista,Pnombre,pos))
  {
    if(pos==lista.nsaltadores-1)
    {
      lista.nsaltadores--;
    }
    else
    {
      CopiarSaltador(lista,pos);
      lista.nsaltadores--;
    }
    return true;
  }
  else
    return false;
}
int Maxima_altura(const TCompeticion &lista,float &altura)
{
  int i=0;
  int pos=0;
  int max_salto=lista.saltadores[0].resultados[0];
  while(i<lista.nsaltadores)
  {
    for(int j=1;j<Nintentos;j++)
    {
      if(lista.saltadores[i].resultados[j]>max_salto)
      {
        max_salto=lista.saltadores[i].resultados[j];
        pos=i;
      }
    }
    i++;
  }
  altura=max_salto;
  return pos;
}
bool Ganador(const TCompeticion &lista,string &Pnombre,string &Pnacion)
{
  float altura;
  if(lista.nsaltadores>0)
  {
    int posicion=Maxima_altura(lista,altura);
    if(altura!=0.0)
    {
      Pnombre=lista.saltadores[posicion].nombre;
      Pnacion=lista.saltadores[posicion].nacionalidad;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
    return false;
}
bool Nacionalidad(const TCompeticion &lista,TCompeticion &copia,const string &Pnacion,string &nom_gan,string &nac_gan)
{
  Vaciar(copia);
  for(int i=0;i<lista.nsaltadores;i++)
  {
    if(Pnacion==lista.saltadores[i].nacionalidad)
    {
      copia.saltadores[copia.nsaltadores]=lista.saltadores[i];
      copia.nsaltadores++;
    }
  }
  if(copia.nsaltadores>0)
  {
    Ganador(copia,nom_gan,nac_gan);
    return true;
  }
  else
    return false;
}
void intercambia(TSaltador &uno,TSaltador &dos)
{
  TSaltador aux;
  aux.nacionalidad=dos.nacionalidad;
  aux.nombre=dos.nombre;
  for(int i=0;i<Nintentos;i++)
  {
    aux.resultados[i]=dos.resultados[i];
  }

  dos.nacionalidad=uno.nacionalidad;
  uno.nacionalidad=aux.nacionalidad;
  dos.nombre=uno.nombre;
  uno.nombre=aux.nombre;
  for(int i=0;i<Nintentos;i++)
  {
    dos.resultados[i]=uno.resultados[i];
    uno.resultados[i]=aux.resultados[i];
  }
}
void Ordenar(TCompeticion &lista)
{
  int i=0;
  int mayor,mayor2;
  bool intercambio = true;
  while( (i<lista.nsaltadores-1)  && (intercambio) )
  {
    intercambio = false;
    for(int j=0;j<lista.nsaltadores-1;++j)
    {
      mayor=lista.saltadores[j].resultados[0];
      mayor2=lista.saltadores[j+1].resultados[0];
      for(int indice=1;indice<Nintentos;indice++)
      {
        if(lista.saltadores[j].resultados[indice]>mayor)
        {
          mayor=lista.saltadores[j].resultados[indice];
        }
        if(lista.saltadores[j+1].resultados[indice]>mayor2)
        {
          mayor2=lista.saltadores[j+1].resultados[indice];
        }
      }
      if (mayor2>mayor)
      {
        intercambio= true;
        intercambia(lista.saltadores[j],lista.saltadores[j+1]);
      }
    }
  i++;
  }
}
