#define WAIT_TIME 2000
#include <iostream>
#include "Serial.h"
using namespace std;
bool conectado;
HANDLE hcom;
HANDLE hSerial;         // Manipulador de comunicação serial
COMSTAT status;         // Obtenha várias informações sobre a conexão
DWORD errors ;
void conectar(char *nome){
    conectado = false;
    hcom = CreateFile(nome, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING,  FILE_ATTRIBUTE_NORMAL, 0);
    if(hcom == INVALID_HANDLE_VALUE){
        cout << "erro ao abrir porta " << GetLastError() << endl;
    }else{
        DCB p = {0};
        if(!GetCommState(hcom, &p)){
            cout << "falha!" << endl;
        }else{
            p.BaudRate = CBR_9600;
            p.ByteSize = 8;
            p.StopBits = ONESTOPBIT;
            p.Parity   = NOPARITY;
            p.fDtrControl = DTR_CONTROL_ENABLE;
            if(!SetCommState(hcom, &p)){
                cout << "falha!" << endl;
            }else{
                conectado = true;
                PurgeComm(hcom, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(WAIT_TIME);

            }
        }
    }
}

Serial::~Serial()
{
    //Check if we are connected before trying to disconnect
    if(conectado)
    {
        //We're no longer connected
        conectado = false;
        //Close the serial handler
        CloseHandle(hcom);
    }
}

int ReadData(char *buffer, unsigned int nbChar){
    DWORD bytesRead;
    unsigned int toRead;
    //ClearCommError(hcom, &errors, &status);
    if(status.cbInQue > 0){
        if(status.cbInQue > nbChar){
            toRead = nbChar;
        }else{
            toRead = status.cbInQue;
        }
        if(ReadFile(hcom, buffer, toRead, &bytesRead, NULL)){
            return bytesRead;
        }
    }
    return 0;
}
bool WriteData(char *buffer, unsigned int nbChar){
    DWORD bytesSend;
    if(!WriteFile(hcom, (void *)buffer, nbChar, &bytesSend, 0)){
        ClearCommError(hcom, &errors, &status);
        return false;
    }else
        return true;
}

int main(){
    cout << "Ae guerreiro!" << endl;
    conectar("COM3");           //cria conexao, caso a COM seja maior que 10, usar \\\\.\\COM10
    if(conectado)
		cout << "estou conectado na UARRT!! ihuul " << endl;

    char data[10] = "";
    int dataLength = 10;
	bool readResult = 0;
	char writeresult[10];

	while(conectado){
        cout << "digite 1 para acender ou qualquer tecla para apagar:" << endl;
        cin >> writeresult;
        if(!WriteData(writeresult, strlen(writeresult))){
            cout << "erro ao enviar!" << endl;
	    }
		readResult = ReadData(data,dataLength);
        data[readResult] = 0;
        cout << "resposta: " << data << endl;
        Sleep(500);
	}
	return 0;
}
