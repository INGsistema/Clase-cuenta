#include <iostream>
#include <stdlib.h>
#include "Cliente.h"
#include "Cuenta.h"
#include "Abono.h"
#define TMI 5

using namespace std;

int Menu(){
    int op;
    cout << "MENU DE OPCIONES\n";
    cout << "1. Agregar cliente a la lista\n";
    cout << "2. Agregar cuenta a la lista.\n";
    cout << "3. Hacer abonos\n";
    cout << "4. Mostrar lista de clientes\n";
    cout << "5. Mostrar lista de cuentas\n";
    cout << "6. Mostrar detalles de la cuenta\n";
    cout << "7. Salir\n";

    cout << "Dijite una opcion : ";
    cin >> op;

    return op;
}

Cliente *BuscarCliente(Cliente *lst[], int cont, int ab){
    bool encontrado = false;
    int contador = 0;
    Cliente *cli = NULL;
    while(contador < cont && !encontrado){
        if(lst[contador]->getIdCliente() == ab){
            encontrado = true;
            cli = lst[contador];
        }
        else{
            contador ++;
        }
    }
    return cli;
}

Cuenta *BuscarCuenta(Cuenta *lst[], int cont, int ab){
    bool encontrado = false;
    int contador=0;
    Cuenta *cuen=NULL;
    while(contador < cont && !encontrado){
          if(lst[contador]->getNumeroCuenta() == ab){
                encontrado = true;
                cuen = lst[contador];
            }
            else{
                contador ++;
            }
        }
        return cuen;
}

void registrarAbono(Cuenta *cuen){
int d, m, a;
Fecha *fa;
float ma;
Abono *ab;
cout << "Digite la fecha de abono (dd,mm,aa) : ";
cin >> d;
cin >> m;
cin >> a;
cout << "Digite el montoa abonar : ";
cin >> ma;
fa = new Fecha(d, m, a);
ab = new Abono(fa, ma);
cuen->agregarAbono(ab);
}

void verDetalles(Cuenta *cuen){
    cout << "Numero : " << cuen->getNumeroCuenta() << endl;
    cout << "Cliente : " << cuen->getCliente()->getNombre() << " " << cuen->getCliente()->getApellido() << endl;
    cout << "Saldo : " << cuen->getSaldo();
    if(cuen->getContadorAbonos() == 0){
        cout << "No tiene abonos realizados\n";
    }
    else{
        Abono **lista = cuen->getLstAbonos();
        cout << "No\tFecha\tMonto\n";
        for(int i; i<cuen->getContadorAbonos();i++){
            cout << (i+1) << "t";
            lista[i]->getfechaAbono()->mostrarFecha();
            cout << lista[i]->getMontoAbono()<< endl;
        }
    }
}
void mostrarClientes(Cliente *lst[], int c){
    if(c==0){
        cout << "La lista esta vacia\n";
    }else{
        cout << "cod\tNombre\tApellido\tSueldo Mensual\n";
        for(int i=0;i<c;i++){
            cout << lst[i]->getIdCliente() << "\t";
            cout << lst[i]->getNombre() << "\t";
            cout << lst[i]->getApellido() << "\t";
        }
    }
}
void mostrarCuentas(Cuenta *lst[], int c){
    if(c==0){
        cout << "La lista esta vacia\n";
    }else{
        cout << "id\tCliente\tCliente\tSaldo\n";
        for(int i=0;i<c;i++){
            cout << lst[i]->getNumeroCuenta() << "\t";
            cout << lst[i]->getCliente()->getNombre() << " " << lst[i]->getCliente()->getApellido() << "\t";
            cout << lst[i]->getSaldo() << "\t";
        }
    }
}

Cliente *AgregarCliente(){
 Cliente *Cli;
    int id;
    string n, a;
        cout << "Dijite el codigo del cliente : ";
        cin >>id;
        cout << "Dijite el nombre del cliente : ";
        cin >> n;
        cout << "Dijite el apellido del cliente : ";
        cin >> a;
        Cli = new Cliente(id, n, a);
        return Cli;
}

Cuenta *AgregarCuenta(Cliente *cli){
    int nc;
    int d, m, a;
    Fecha *fa;
    int ab;
    Cuenta *cuen;
        cout << "Dijite el codigo de la cuenta : ";
        cin >>nc;
        cout << "Dijite la en que se abrio la cuenta(dd/mm/aa) : ";
        cin >> d;
        cin >> m;
        cin >> a;
        fa = new Fecha(d, m, a);
        cout << "Dijite el abono a realizar : ";
        cin >> ab;
        cuen = new Cuenta(nc, cli);
        return cuen;
}


int main()
{
    Cliente *lstClien[TMI];
    Cuenta *lstCuen[TMI];
    Cliente *clien=NULL;
    Cuenta *cuen=NULL;
    int opc, contClien=0, contCuen=0, idClien=0,idCuen=0;
    do{
            system("cls");
            opc = Menu();
            switch(opc){
        case 1:
            ///Agregar Cliente
            if(contClien <TMI){
                lstClien[contClien] = AgregarCliente();
                contClien = contClien + 1;
                cout << "El cliente se agrego con exito\n";
            }else{
            cout << "La lista de clientes esta llena";
            }
            break;
        case 2:
            ///Agregar cuenta
            if(contCuen <TMI){
                cout << "Digite el id del Cliente : ";
                cin >> idClien;
                clien =  BuscarCliente(lstClien, contClien, idClien);
                if(clien){
                    lstCuen[contCuen] = AgregarCuenta(clien);
                    contCuen ++;

                cout << "La cuenta se agrego con exito\n";
            }
            else{
            cout << "La lista de cuentas esta llena";
            }
        }
            break;
        case 3:
            ///Hacer abonos
            cout << "Dijite el numero de la cuenta : ";
            cin >> idCuen;
                cuen = BuscarCuenta(lstCuen, contCuen, idCuen);
            if(cuen){
                registrarAbono(cuen);
                cout << "El abono se registro con exito\n";
            }else{
                cout << "La cuenta no existe, no se puede registrar el abono";
            }
            break;
        case 4:
            ///Mostrar lista de clientes
            mostrarClientes(lstClien, contClien);
            break;
        case 5:
            ///Mostrar lista de cuentas
             mostrarCuentas(lstCuen, contCuen);
            break;
        case 6:
            ///Mostrar detalles de la cuenta
            cout << "Digite el numero de la cuenta : ";
            cin >> idCuen;
            cuen = BuscarCuenta(lstCuen, contCuen, idCuen);
            if(cuen){
                verDetalles(cuen);
            }
            else{
                cout << "La cuenta no existe, no se pueden visualizar los detalles\n";
            }
            break;
        case 7:
            cout << "Saliendo del programa....";
            break;
        default:
            cout<< "Opcion no valida, intente nuevamente";
            break;
            }
            system("pause");

 }while(opc != 7);

    return 0;
}
