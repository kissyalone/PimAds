#include <iostream>
#include <fstream>
#include<istream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <locale.h>
#include <iomanip>
using namespace std;
constexpr auto MAX = 50;

/*
	Projeto: ADS SEM PIZZA
	Turma: DS2A17				  __
	Grupo: Dp ao podio:			// ""--.._
	 -Jhonata S.				||  (_)  _ "-._
	 -Gabriel R.				||    _ (_)    '-.
	 -Enzo R.					||   (_)   __..-'
	 -Maycon L.					\\__..--""
	 -Reinaldo S.				
*/

//------------------- DECLARACAO DE FUNCOES ------------------------ //
/*data*/char dataSistema[13];
//-----------------------------LOGIN--------------------------------
bool verificaLogin();
int NumeroLoja = 0; string usuarioAtivo = ""; int nivelLoja = 0;
//-----------------------------MAINS-------------------------------
int main();
void menuInicial();     // op: 1 2 3 4 5 = //

//----------------------1-CONTROLE DE CAIXA------------------------
void controleDeCaixa();								//SUB-MENU
void aberturaCaixa();								//  [1]
void fechamentoCaixa();								//  [2]
void sangriaCaixa();								//  [3]
void reforcoCaixa();								//  [4]
bool verificaCaixa();								// funcao

//-------------2-CONTROLE DE ESTOQUE E PRODUTOS--------------------
void controleCadastroEstoque();						//SUB-MENU
void entradaDeMercadoria();							//  [1]
void removeMercadoria();							//  [2]
void cadastroProduto();		                        //  [3]
void removeProduto();								//  [4]
void alteraPrecoProduto();							//  [5]

//-------------------------3-RELATORIOS------------------------------
void relatorioMenu();								//SUB-MENU
void relatorioVendas();								// [1]
void relatorioDetalhadoCaixa();						// [2]
void relatorioDetalhadoPedido();					// [3]
void relatorioEstoque();							// [4]
void relatorioProdutos();							// [5]
void pesquisaNome();							// (
void pesquisaData();							// sub funcao [5]
void pesquisaTotal();							// )

//-------------------------4-BALCAO----------------------------------m
void balcaoSacola();

//------------------------5-TROCA DE USUARIO-------------------------
void trocaUsuario();

//---------------------------subfuncao-------------------------------

int intLength(int i);
void gotoxy(int x, int y);
//-----------------------FIM DE DECLARACOES--------------------------//

bool verificaLogin() {
	setlocale(LC_ALL, "Portuguese");
	ifstream procurador;
	string password = "", usuarioDigitado = "", recebeLinha;
	cout << "                       ____                   " << endl;
	cout << "                     /     \\			" << endl;
	cout << "                        u  u|      _______" << endl;
	cout << "                           \\|  .-''#%&#&%#``-.   " << endl;
	cout << "                         = /  ((%&#&#&%&VK&%&)) " << endl;
	cout << "                         |     `-._#%&##&%_.-' " << endl;
	cout << "                      /\\/\\`--.   `-."".-'"" " << endl;
	cout << "                      |  |    \\    /`./  " << endl << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                     Pizzaria New York                    |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                           ENTRAR" << endl;
	cout << "                      Usuário: "; 
	cin >> usuarioDigitado;
	cout << "                      Senha: (Digitação oculta)";
	
	do {
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode = 0;
		GetConsoleMode(hStdin, &mode);
		SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
		getline(cin, password);
	} while (password == "");
	procurador.open("loginBDS.txt", ios::in);
	do {
		getline(procurador, recebeLinha);
		if (recebeLinha == usuarioDigitado) {
			getline(procurador, recebeLinha); // pega senha
			if (recebeLinha == password) {
				usuarioAtivo = usuarioDigitado;
				getline(procurador, recebeLinha); // pega nivel de loja
				nivelLoja = stoi(recebeLinha);
				getline(procurador, recebeLinha); // pega loja
				NumeroLoja = stoi(recebeLinha);
				procurador.close();
				return true;
			}
			else {
				system("cls");
				gotoxy(0, 5);
				cout << "+----------------------------------------------------------+" << endl;
				cout << "|                 Usuário ou Senha inválida!               |" << endl;
				cout << "+----------------------------------------------------------+" << endl;
				Sleep(999);
				return false;
			}
		}
	} while (procurador.eof() == NULL);
	system("cls");
	gotoxy(0, 5);
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                 Usuário ou Senha inválida!               |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	Sleep(999);
	return false;
};

int main() {
	setlocale(LC_ALL, "Portuguese");
	system("mode con:lines=25 cols=60");
	_strdate_s(dataSistema);
	bool validacao = verificaLogin();
	if (validacao == true)
	{	
		
		system("cls");
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                       Seja Bem Vindo!                    |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(600);
	}
	else
	{
		return main();
	};
	menuInicial();
	return 0;
}

void menuInicial() {
	system("mode con:lines=25 cols=60");
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	int escolhaMenu;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left <<setw(7) << left << usuarioAtivo <<" || loja : " << NumeroLoja <<"       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                 Menu Inicial Do Programa                 |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "| [1] Controle De Caixa                                    |" << endl;
	cout << "| [2] Controle E Cadastro De Estoque                       |" << endl;
	cout << "| [3] Relatórios                                           |" << endl;
	cout << "| [4] Balcão De Pedido                                     |" << endl;
	cout << "| [5] Trocar Usuário                                       |" << endl;
	cout << "| [6] Sair Do Programa                                     |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	do {
		
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
		};
		system("cls");
		switch (escolhaMenu) {

		case 59: //f1
			menuInicial();
			break;
		case 60: //f2
			usuarioAtivo = "";
			NumeroLoja = 0;
			main();
			break;
		case 61: //f3
			menuInicial();
			break;
		case '1':
			controleDeCaixa();
			break;
		case '2':
			controleCadastroEstoque();
			break;
		case '3':
			relatorioMenu();
			break;
		case '4':
			balcaoSacola();
			break;
		case '5':
			trocaUsuario();
			break;
		case '6':
			int op;
			gotoxy(0, 5);
			cout << "+----------------------------------------------------------+" << endl;
			cout << "| Fechando programa! Aperte [1] para cancelar fechamento...|" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			op = _getch();
			switch (op)
			{
			case '1': 
				return menuInicial();
			default:
				exit(0);
				break;
			}
			break;
		default:
			return menuInicial();
			break;
		}
	} while (escolhaMenu == 0);
}

//[1] Controle de Caixa
//submenu
void controleDeCaixa() {
	system("cls");
	setlocale(LC_ALL, "Portuguese");
	if (nivelLoja < 2) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|              Usuário sem permissão de acesso             |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return menuInicial();
	}
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	int escolhaMenu;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu Inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                 Menu De Controle De Caixa                |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "| [1] Abertura De Caixa                                    |" << endl;
	cout << "| [2] Fechamento de Caixa                                  |" << endl;
	cout << "| [3] Sangria De Caixa                                     |" << endl;
	cout << "| [4] Reforço De Caixa                                     |" << endl;
	cout << "| [5] Sair Do Programa                                     |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	do {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
		};
		system("cls");
		switch (escolhaMenu) {

		case 59: //f1
			menuInicial();
			break;
		case 60: //f2
			menuInicial();
			break;
		case 61: //f3
			controleDeCaixa();
			break;
		case '1':
			aberturaCaixa();
			break;
		case '2':
			fechamentoCaixa();
			break;
		case '3':
			sangriaCaixa();
			break;
		case '4':
			reforcoCaixa();
			break;
		case '5':
			int op;
			gotoxy(0, 5);
			cout << "+----------------------------------------------------------+" << endl;
			cout << "| Fechando programa! Aperte [1] para cancelar fechamento...|" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			op = _getch();
			switch (op)
			{
			case '1':
				return controleDeCaixa();
			default:
				exit(0);
				break;
			}
			break;
		default:
			return controleDeCaixa();
			break;
		}
	} while (escolhaMenu == 0);
} 
//-1
void aberturaCaixa() {
	system("cls");
	setlocale(LC_ALL, "Portuguese");
	if (verificaCaixa()) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|              Abertura de caixa já realizada              |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return controleDeCaixa();
	}
	string cabecalho = "=============Registro de Caixa=============\n Horas    | Atidade Realizada   | Valor"; //cabecalho de abertura
	char timeStr[128];
	char dateStr[13];
	_strtime_s(timeStr, 128);
	_strdate_s(dateStr);
	for (int i = 0; i < 9; i++) {
		if (dateStr[i] == '/') { //substitui mm/dd por mm.dd
			dateStr[i] = '.';
		}
	};
	int escolhaMenu = 0;
	string valorAbertura = "";
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                    Abertura De Caixa                     |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Data de abertura: " << dateStr << endl;
	cout << "                Valor: " << valorAbertura << endl;
	bool enterApertado = false;
	int i = 0;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleDeCaixa();
					break;
				case 61: //f3
					fechamentoCaixa();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu == 46) || (escolhaMenu == 44)) {
			if (escolhaMenu == 44) {
				escolhaMenu = '.';
			}
			valorAbertura += escolhaMenu;
			i = escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = valorAbertura.length();
			if (i <= 0) {
				continue;
			};
			i--;
			valorAbertura.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " << setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                    Abertura De Caixa                     |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Data de abertura: " << dateStr << endl;
		cout << "                Valor: " << valorAbertura << endl;
		if (enterApertado) {
			break;
		}
	};

	string arq;
	_strtime_s(timeStr, 128);
	_strdate_s(dateStr);
	for (int i = 0; i < 9; i++) {
		if (dateStr[i] == '/') { //substitui mm/dd por mm.dd
			dateStr[i] = '.';
		}
	};

	arq += dateStr;
	arq += ".txt";
	if (NumeroLoja == 1) {
		arq = "1\\" + arq;
	}
	else if (NumeroLoja == 2) {
		arq = "2\\" + arq;
	}
	else if (NumeroLoja == 3) {
		arq = "3\\" + arq;
	}
	else {
		 menuInicial();
	}
	ofstream gravador;
	gravador.open(arq);
	gravador << cabecalho << endl;
	gravador << " " << timeStr << " | "<< "ABERTURA DE CAIXA" <<  "   | " << valorAbertura << endl;

	gravador.close();
	system("cls");
	gotoxy(0, 5);
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                Caixa aberto com sucesso!                 |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	Sleep(1000);
	return controleDeCaixa();
}
//-2
void fechamentoCaixa(){
	system("cls");
	setlocale(LC_ALL, "Portuguese");
	if (!verificaCaixa()) {
		return controleDeCaixa();
	};
	double valorFechamento = 0.0, diferencaCaixa = 0.0, totPedidos = 0.0;
	int contPedidos = 0;
	string recebeLinha = "";

	// nome do caixa .txt
	char timeStr[128];
	char dateStr[13];
	string arq;

	_strtime_s(timeStr, 128);
	_strdate_s(dateStr);
	for (int i = 0; i < 9; i++) {
		if (dateStr[i] == '/') { //substitui mm/dd por mm.dd
			dateStr[i] = '.';
		}
	};
	arq += dateStr;
	arq += ".txt";
	if (NumeroLoja == 1) {
		arq = "1\\" + arq;
	}
	else if (NumeroLoja == 2) {
		arq = "2\\" + arq;
	}
	else if (NumeroLoja == 3) {
		arq = "3\\" + arq;
	}
	else {
		 menuInicial();
	}

	//SOMA FECHAMENTO
	string valorDigitado;
	int escolhaMenu = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                   Fechamento De Caixa                    |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Data de Fechamento: " << dateStr << endl;
	cout << "                Valor: ";
	bool enterApertado = false;
	int i = 0;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleDeCaixa();
					break;
				case 61: //f3
					fechamentoCaixa();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu == 46) || (escolhaMenu == 44)) {
			if (escolhaMenu == 44) {
				escolhaMenu = '.';
			}
			valorDigitado += escolhaMenu;
			i = escolhaMenu;
		}
		else if (escolhaMenu == 8) {

			i = valorDigitado.length();
			if (i <= 0) {
				continue;
			};
			i--;
			valorDigitado.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                   Fechamento De Caixa                    |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Data de Fechamento: " << dateStr << endl;
		cout << "                Valor: ";
		cout << valorDigitado;
		if (enterApertado) {
			break;
		};
	}
	 //convertendo valor digitado para float.
	double valorFloat = 0.0;
	stringstream ss;
	string s = valorDigitado;
	ss << s;
	ss >> valorFloat;
	

	ifstream procurador;
	procurador.open(arq, ios::in);
	getline(procurador, recebeLinha); //PULA CABECALHO
	getline(procurador, recebeLinha);
	do {
		getline(procurador, recebeLinha);
		if (recebeLinha[33] == '$') {
			recebeLinha.erase(0, 34);
			if (recebeLinha == "\0") {
				break;
			}
			//convertendo valor digitado para float. 
			double totTemp = 0.0;
			stringstream ss;
			string s = recebeLinha;
			ss << s;
			ss >> totTemp;
			totPedidos += totTemp;
		}
		else {
			recebeLinha.erase(0, 34);
			if (recebeLinha == "\0") {
				break;
			};
		}
		double totTemp2 = 0.0;
		//convertendo valor digitado para float. 
		stringstream ss;
		string s = recebeLinha;
		ss << s;
		ss >> totTemp2;
		valorFechamento += totTemp2;
	} while (procurador.eof() == NULL);
	procurador.close();
	procurador.open(arq, ios::in);
	do {
		getline(procurador, recebeLinha, ' ');
		if (recebeLinha == "PEDIDO") {
			contPedidos++;

		}
	} while (procurador.eof() == NULL);
	procurador.close();
	diferencaCaixa = valorFloat - valorFechamento;

	//LANCA FECHAMENTO
	ofstream gravador;
	gravador.open(arq, ios::app);
	gravador << " " << timeStr << " | " << "!!!!!FECHAMENTO!!!!" << " | " << 0 << endl;
	gravador << "TOTAL VENDIDO.................... " << totPedidos << endl;
	gravador << "TOTAL DE PEDIDOS................. " << contPedidos << endl;
	gravador << "TOTAL DE CAIXA................... " << valorFechamento << endl;
	gravador << "VALOR DIGITADO PELO USUARIO...... " << valorFloat << endl;
	gravador << "DIFERENCA DE CAIXA DE............ " << diferencaCaixa << endl;
	gravador << "=============Fim de Registro==============" << endl;
	gravador.close();

	//LANCA TOTAL DO DIA NO REGISTRO DE CAIXA
	if (NumeroLoja == 1) {
		gravador.open("1\\registroVendas.txt", ios::app);
	}
	else if (NumeroLoja == 2) {
		gravador.open("2\\registroVendas.txt", ios::app);
	}
	else if (NumeroLoja == 3) {
		gravador.open("3\\registroVendas.txt", ios::app);
	}
	else {
		menuInicial();
	}
	gravador << "!!!fim dia " << dateStr << " !!!" << endl;
	gravador << "total vendas do dia: " << totPedidos << endl;
	gravador.close();

	// exibe relatorio de fechamento de caixa
	system("cls");
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                   Fechamento De Caixa                    |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|              Resumo de fechamento de caixa               |" << endl;
	cout << "| Total vendido  " << fixed << setprecision(2) << totPedidos << setw(40 - intLength(totPedidos)) << right << "|" << endl;
	cout << "| Numero de pedidos " << contPedidos << setw(40- intLength(contPedidos)) << right << "|" << endl;
	cout << "| Total de caixa " << fixed << setprecision(2) << valorFechamento  << setw(40- intLength(valorFechamento)) << right << "|" << endl;
	cout << "| Valor inserido pelo usuário "  << fixed << setprecision(2) <<valorFloat << setw(27- intLength(valorFloat)) << right << "|" << endl;
	cout << "| Diferença de caixa " << fixed << setprecision(2) << diferencaCaixa  << setw(36- intLength(diferencaCaixa)) << right << "|" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "            Imprimir Fechamento? <ENTER> ou <ESC>           " << endl;
	escolhaMenu = 0;
	do {
		escolhaMenu = _getch();
		if (escolhaMenu == 13) {
			break;
		}
		else if (escolhaMenu == 27) {
			return controleDeCaixa();
		}
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
		};
		system("cls");
		switch (escolhaMenu) {

		case 59: //f1
			menuInicial();
			break;
		case 60: //f2
			controleDeCaixa();
			break;
		case 61: //f3
			fechamentoCaixa();
			break;
		default:
			break;
		};

	} while (escolhaMenu == 0);
	remove("impressao.txt");
	ofstream imprimi;
	imprimi.open("impressao.txt");
	imprimi << "+---------------------------------------------------+" << endl;
	imprimi << "|          Resumo de Fechamento de Caixa            |" << endl;
	imprimi << "| Total vendido: " << fixed << setprecision(2) << setw(10) << left << totPedidos << setw(26) << right << "|" << endl;
	imprimi << "| Numero de pedidos: " << setw(4) << left << contPedidos << setw(28) << right << "|" << endl;
	imprimi << "| Total de caixa: " << fixed << setprecision(2) << setw(10) << left << valorFechamento << setw(25) << right << "|" << endl;
	imprimi << "| Valor inserido pelo usuário: " << fixed << setprecision(2) << setw(10) << left << valorFloat << setw(12) << right << "|" << endl;
	imprimi << "| Diferença de caixa: " << fixed << setprecision(2) << setw(10) << left << diferencaCaixa << setw(21) << right << "|" << endl;
	imprimi << "+---------------------------------------------------+" << endl;
	imprimi << "| Assinatura Do Responsável: _______________________|" << endl;
	imprimi << "+---------------------------------------------------+" << endl;
	imprimi.close();
	system("notepad /p impressao.txt");

return menuInicial();
}
//-3
void sangriaCaixa() {
	system("cls");
	setlocale(LC_ALL, "Portuguese");
	if (!verificaCaixa()) {
		return controleDeCaixa();
	};
	// data
	char timeStr[128];
	char dateStr[13];
	string arq;
	_strtime_s(timeStr, 128);
	_strdate_s(dateStr);
	for (int i = 0; i < 9; i++) {
		if (dateStr[i] == '/') { //substitui mm/dd por mm.dd
			dateStr[i] = '.';
		}
	};

	// input
	string valorDigitado;
	int escolhaMenu = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                     Sangria De Caixa                     |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Data de Sangria: " << dateStr << endl;
	cout << "                Valor: ";
	bool enterApertado = false;
	int i = 0;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleDeCaixa();
					break;
				case 61: //f3
					sangriaCaixa();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu == 46) || (escolhaMenu == 44)) {
			if (escolhaMenu == 44) {
				escolhaMenu = '.';
			}
			valorDigitado += escolhaMenu;
			i = escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = valorDigitado.length();
			if (i <= 0) {
				continue;
			};
			i--;
			valorDigitado.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                     Sangria De Caixa                     |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Data de Sangria: " << dateStr << endl;
		cout << "                Valor: ";
		cout << valorDigitado;
		if (enterApertado) {
			break;
		};


	}
	//convertendo valor digitado para float.
	double valorSangria = 0.0;
	stringstream ss;
	string s = valorDigitado;
	ss << s;
	ss >> valorSangria;
	valorSangria *= -1; // negativa

	// lanca bds
	arq += dateStr;
	arq += ".txt";
	if (NumeroLoja == 1) {
		arq = "1\\" + arq;
	}
	else if (NumeroLoja == 2) {
		arq = "2\\" + arq;
	}
	else if (NumeroLoja == 3) {
		arq = "3\\" + arq;
	}
	else {
		return menuInicial();
	}
	ofstream gravador;
	gravador.open(arq, ios::app);
	gravador << " " << timeStr << " | " << "SANGRIA DE CAIXA" << "    | " << valorSangria << endl;
	gravador.close();
	// sai da funcao
	system("cls");
	gotoxy(0, 5);
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|              Sangria Realizada Com Sucesso               |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	Sleep(1000);
	return controleDeCaixa();
}
//-4
void reforcoCaixa() {
	system("cls");
	setlocale(LC_ALL, "Portuguese");
	if (!verificaCaixa()) {
		return controleDeCaixa();
	};

	// data
	char timeStr[128];
	char dateStr[13];
	string arq;
	_strtime_s(timeStr, 128);
	_strdate_s(dateStr);
	for (int i = 0; i < 9; i++) {
		if (dateStr[i] == '/') { //substitui mm/dd por mm.dd
			dateStr[i] = '.';
		}
	};

	//input
	string valorDigitado;
	int escolhaMenu = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                     Reforço De Caixa                     |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Data de Sangria: " << dateStr << endl;
	cout << "                Valor: ";
	bool enterApertado = false;
	int i = 0;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleDeCaixa();
					break;
				case 61: //f3
					reforcoCaixa();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu == 46) || (escolhaMenu == 44)) {
			if (escolhaMenu == 44) {
				escolhaMenu = '.';
			}
			valorDigitado += escolhaMenu;
			i = escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = valorDigitado.length();
			if (i <= 0) {
				continue;
			};
			i--;
			valorDigitado.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                     Reforço De Caixa                     |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Data de Reforço: " << dateStr << endl;
		cout << "                Valor: ";
		cout << valorDigitado;
		if (enterApertado) {
			break;
		};


	}

	//convertendo valor digitado para float.
	double valorReforco = 0.0;
	stringstream ss;
	string s = valorDigitado;
	ss << s;
	ss >> valorReforco;

	// lanca bds
	arq += dateStr;
	arq += ".txt";
	if (NumeroLoja == 1) {
		arq = "1\\" + arq;
	}
	else if (NumeroLoja == 2) {
		arq = "2\\" + arq;
	}
	else if (NumeroLoja == 3) {
		arq = "3\\" + arq;
	}
	else {
		return menuInicial();
	}
	ofstream gravador;
	gravador.open(arq, ios::app);
	gravador << " " << timeStr << " | " << "REFORCO DE CAIXA" << "    | " << valorReforco << endl;
	gravador.close();
	system("cls");
	gotoxy(0, 5);
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|              Reforço Realizada Com Sucesso               |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	Sleep(1000);
	return controleDeCaixa();
}
//-funcao
bool verificaCaixa() {
	setlocale(LC_ALL, "Portuguese");
	string verificaFechamento;
	char dateStr[13];
	string arq;
	_strdate_s(dateStr);
	for (int i = 0; i < 9; i++) {
		if (dateStr[i] == '/') { //substitui mm/dd por mm.dd
			dateStr[i] = '.';
		}
	};
	arq += dateStr;
	arq += ".txt";
	if (NumeroLoja == 1) {
		arq = "1\\" + arq;
	}
	else if (NumeroLoja == 2) {
		arq = "2\\" + arq;
	}
	else if (NumeroLoja == 3) {
		arq = "3\\" + arq;
	}
	else {
		 menuInicial();
	}
	ifstream verificador;
	verificador.open(arq, ios::in);
	
	if (verificador) {
		do {
			getline(verificador, verificaFechamento, ' ');
			if (verificaFechamento == "!!!!!FECHAMENTO!!!!") {
				gotoxy(0, 5);
				cout << "+----------------------------------------------------------+" << endl;
				cout << "|            Fechamento de caixa já realizado!             |" << endl;
				cout << "+----------------------------------------------------------+" << endl;
				Sleep(1000);
				system("cls");
				verificador.close();
				return false;
			}
		} while (verificador.eof() == NULL);

	}
	else if (!verificador) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|             Não Há Caixa Aberto No Momento!              |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		system("cls");
		verificador.close();
		return false;
	}
	
	
	verificador.close();
	return true;
}

//[2] Controle e Cadastro de Estoque
//submenu
void controleCadastroEstoque() {
	system("mode con:lines=25 cols=60");
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	int escolhaMenu;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|          Menu De Controle E Cadastro De Estoque          |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "| [1] Entrada De Mercadoria No Estoque                     |" << endl;
	cout << "| [2] Remover Mercadoria Do Estoque                        |" << endl;
	cout << "| [3] Cadastrar Produto                                    |" << endl;
	cout << "| [4] Remover Produto Cadastrado                           |" << endl;
	cout << "| [5] Alterar Preço De Produto                             |" << endl;
	cout << "| [6] Sair Do Programa                                     |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	do {

		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
		};
		system("cls");
		switch (escolhaMenu) {

		case 59: //f1
			menuInicial();
			break;
		case 60: //f2
			menuInicial();
			break;
		case 61: //f3
			controleCadastroEstoque();
			break;
		case '1':
			entradaDeMercadoria();
			break;
		case '2':
			removeMercadoria();
			break;
		case '3':
			cadastroProduto();
			break;
		case '4':
			removeProduto();
			break;
		case '5':
			alteraPrecoProduto();
			break;
		case '6':
			int op;
			gotoxy(0, 5);
			cout << "+----------------------------------------------------------+" << endl;
			cout << "| Fechando programa! Aperte [1] para cancelar fechamento...|" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			op = _getch();
			switch (op)
			{
			case '1':
				return controleCadastroEstoque();
			default:
				exit(0);
				break;
			}
			break;
		default:
			return menuInicial();
			break;
		}
	} while (escolhaMenu == 0);
}
//-1
void entradaDeMercadoria() {
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	string produtosDoBds; // recebe banco de dados
	int novoEstoque, realQuantidade = 0;
	// entrada de nome de prod e quantidadade
	string nomeDigitado = "";
	string quantidadeProduto = "";
	int escolhaMenu = 0;
	bool enterApertado = false;
	int i = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                  Entrada De Mercadoria                   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Nome do produto: " << nomeDigitado << endl;
	cout << "                Quantidade: " << quantidadeProduto << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleCadastroEstoque();
					break;
				case 61: //f3
					entradaDeMercadoria();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu >=97) && (escolhaMenu <= 122) || (escolhaMenu == 32)) {
			
			nomeDigitado += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = nomeDigitado.length();
			if (i <= 0) {
				continue;
			};
			i--;
			nomeDigitado.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                  Entrada De Mercadoria                   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Nome do produto: " << nomeDigitado << endl;
		cout << "                Quantidade: " << quantidadeProduto << endl;
		if (enterApertado) {
			break;
		};
	}
	/////////////// quantidade ////////////////
	escolhaMenu = 0;
	enterApertado = false;
	i = 0;
	system("cls");
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                  Entrada De Mercadoria                   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Nome do produto: " << nomeDigitado << endl;
	cout << "                Quantidade: " << quantidadeProduto << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleCadastroEstoque();
					break;
				case 61: //f3
					entradaDeMercadoria();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {
			quantidadeProduto += escolhaMenu;
			i = escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = quantidadeProduto.length();
			if (i <= 0) {
				continue;
			};
			i--;
			quantidadeProduto.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                  Entrada De Mercadoria                   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Nome do produto: " << nomeDigitado << endl;
		cout << "                Quantidade: " << quantidadeProduto << endl;
		if (enterApertado) {
			break;
		};
	}

	// converte nome 
	nomeDigitado = "nome: " + nomeDigitado;

	// lanca bds
	ifstream produtoBDS;
	ofstream transfereBDS;
	bool achouSim = false;
	if (NumeroLoja == 1) {
		transfereBDS.open("1\\transfereBDS.txt");
		produtoBDS.open("1\\produtoBDS.txt");
	}
	else if (NumeroLoja == 2) {
		transfereBDS.open("2\\transfereBDS.txt");
		produtoBDS.open("2\\produtoBDS.txt");
	}
	else if (NumeroLoja == 3) {
		transfereBDS.open("3\\transfereBDS.txt");
		produtoBDS.open("3\\produtoBDS.txt");
	}
	else {
	 menuInicial();
	}
	do {
		getline(produtoBDS, produtosDoBds);
		if (produtosDoBds == "\n")
		{
			continue;
		}
		if (nomeDigitado == produtosDoBds) {
			achouSim = true;
			transfereBDS << produtosDoBds << endl; //coloca nome
			getline(produtoBDS, produtosDoBds);
			transfereBDS << produtosDoBds << endl; //coloca preco
			getline(produtoBDS, produtosDoBds);
			
			produtosDoBds.erase(0, 11); 
			realQuantidade = stoi(produtosDoBds); // transforma quantidade string em int

			novoEstoque = realQuantidade + stoi(quantidadeProduto);
			transfereBDS << "quantidade: " << novoEstoque << endl;
			getline(produtoBDS, produtosDoBds);
		}
		transfereBDS << produtosDoBds << endl;
	} while (produtoBDS.eof() == NULL);
	transfereBDS.close();
	produtoBDS.close();
	if (NumeroLoja == 1) {
		remove("1\\produtoBDS.txt");
		rename("1\\transfereBDS.txt", "1\\produtoBDS.txt");
	}
	else if (NumeroLoja == 2) {
		remove("2\\produtoBDS.txt");
		rename("2\\transfereBDS.txt", "2\\produtoBDS.txt");
	}
	else if (NumeroLoja == 3) {
		remove("3\\produtoBDS.txt");
		rename("3\\transfereBDS.txt", "3\\produtoBDS.txt");
	}
	else {
		menuInicial();
	}
	// informa se foi bem sucedido
	system("cls");
	if (!achouSim) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                 Produto não encontrado!                  |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return entradaDeMercadoria();
	}
	else if (achouSim) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|       Entrada de Mercadoria Realizada Com Sucesso!       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return controleCadastroEstoque();
	}
	
	return menuInicial();
}
//-2
void removeMercadoria(){
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	if (nivelLoja < 2) { // verifica nivel de funcionario
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|              Usuário sem permissão de acesso             |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return controleCadastroEstoque();
	}
	string produtosDoBds; // recebe banco de dados
	int novoEstoque, realQuantidade = 0;
	// entrada de nome de prod e quantidadade
	string nomeDigitado = "";
	string quantidadeProduto = "";
	int escolhaMenu = 0;
	bool enterApertado = false;
	int i = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                 Retirada De Mercadoria                   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Nome do produto: " << nomeDigitado << endl;
	cout << "                Quantidade: " << quantidadeProduto << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleCadastroEstoque();
					break;
				case 61: //f3
					removeMercadoria();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu >= 97) && (escolhaMenu <= 122) || (escolhaMenu == 32)) {

			nomeDigitado += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = nomeDigitado.length();
			if (i <= 0) {
				continue;
			};
			i--;
			nomeDigitado.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                 Retirada De Mercadoria                   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Nome do produto: " << nomeDigitado << endl;
		cout << "                Quantidade: " << quantidadeProduto << endl;
		if (enterApertado) {
			break;
		};
	}
	/////////////// quantidade ////////////////
	escolhaMenu = 0;
	enterApertado = false;
	i = 0;
	system("cls");
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                 Retirada De Mercadoria                   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Nome do produto: " << nomeDigitado << endl;
	cout << "                Quantidade: " << quantidadeProduto << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleCadastroEstoque();
					break;
				case 61: //f3
					entradaDeMercadoria();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {
			quantidadeProduto += escolhaMenu;
			i = escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = quantidadeProduto.length();
			if (i <= 0) {
				continue;
			};
			i--;
			quantidadeProduto.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                 Retirada De Mercadoria                   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Nome do produto: " << nomeDigitado << endl;
		cout << "                Quantidade: " << quantidadeProduto << endl;
		if (enterApertado) {
			break;
		};
	}

	// converte nome 
	nomeDigitado = "nome: " + nomeDigitado;

	// lanca bds
	ifstream produtoBDS;
	ofstream transfereBDS;
	bool achouSim = false;
	if (NumeroLoja == 1) {
		transfereBDS.open("1\\transfereBDS.txt");
		produtoBDS.open("1\\produtoBDS.txt");
	}
	else if (NumeroLoja == 2) {
		transfereBDS.open("2\\transfereBDS.txt");
		produtoBDS.open("2\\produtoBDS.txt");
	}
	else if (NumeroLoja == 3) {
		transfereBDS.open("3\\transfereBDS.txt");
		produtoBDS.open("3\\produtoBDS.txt");
	}
	else {
		menuInicial();
	}
	do {
		getline(produtoBDS, produtosDoBds);
		if (produtosDoBds == "\n")
		{
			continue;
		}
		if (nomeDigitado == produtosDoBds) {
			achouSim = true;
			transfereBDS << produtosDoBds << endl; //coloca nome
			getline(produtoBDS, produtosDoBds);
			transfereBDS << produtosDoBds << endl; //coloca preco
			getline(produtoBDS, produtosDoBds);
			
			produtosDoBds.erase(0, 11);
			realQuantidade = stoi(produtosDoBds); // transforma valor em string em int;

			novoEstoque = realQuantidade - stoi(quantidadeProduto);
			transfereBDS << "quantidade: " << novoEstoque << endl;
			getline(produtoBDS, produtosDoBds);
		}
		transfereBDS << produtosDoBds << endl;
	} while (produtoBDS.eof() == NULL);
	transfereBDS.close();
	produtoBDS.close();
	if (NumeroLoja == 1) {
		remove("1\\produtoBDS.txt");
		rename("1\\transfereBDS.txt", "1\\produtoBDS.txt");
	}
	else if (NumeroLoja == 2) {
		remove("2\\produtoBDS.txt");
		rename("2\\transfereBDS.txt", "2\\produtoBDS.txt");
	}
	else if (NumeroLoja == 3) {
		remove("3\\produtoBDS.txt");
		rename("3\\transfereBDS.txt", "3\\produtoBDS.txt");
	}
	else {
		menuInicial();
	}
	// exibi se foi bem sucedido
	system("cls");
	if (!achouSim) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                 Produto não encontrado!                  |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return removeMercadoria();
	}
	else if (achouSim) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|       Retirada de Mercadoria Realizada Com Sucesso!      |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return controleCadastroEstoque();
	}
	return menuInicial();
}
//-3
void cadastroProduto() {
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	if (nivelLoja < 2) { // verifica nivel de funcionario
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|              Usuário sem permissão de acesso             |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return controleCadastroEstoque();
	}
	// var de inputs
	string nomeDigitado = "", quantidadeProduto = "", codigoProduto = "", precoProduto = "", recebeLinha = "";
	int escolhaMenu = 0;
	bool enterApertado = false;
	int i = 0;
	// pega nome
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " << setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                   Cadastro De Produto                    |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Nome do produto: " << nomeDigitado << endl;
	cout << "                Codigo do produto: " << codigoProduto << endl;
	cout << "                Preço: " << precoProduto << endl;
	cout << "                Quantidade: " << quantidadeProduto << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleCadastroEstoque();
					break;
				case 61: //f3
					cadastroProduto();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu >= 97) && (escolhaMenu <= 122) || (escolhaMenu == 32)) {

			nomeDigitado += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = nomeDigitado.length();
			if (i <= 0)
			{
				continue;
			}
			i--;
			nomeDigitado.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " << setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                   Cadastro De Produto                    |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Nome do produto: " << nomeDigitado << endl;
		cout << "                Codigo do produto: " << codigoProduto << endl;
		cout << "                Preço: " << precoProduto << endl;
		cout << "                Quantidade: " << quantidadeProduto << endl;
		if (nomeDigitado.length() > 10) {
			break;
		}
		if (enterApertado) {
			break;
		};
	}
	// pega codigo
	system("cls");
	escolhaMenu = 0;
	enterApertado = false;
	i = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " << setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                   Cadastro De Produto                    |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Nome do produto: " << nomeDigitado << endl;
	cout << "                Codigo do produto: " << codigoProduto << endl;
	cout << "                Preço: " << precoProduto << endl;
	cout << "                Quantidade: " << quantidadeProduto << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleCadastroEstoque();
					break;
				case 61: //f3
					cadastroProduto();
					break;
				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {
			codigoProduto += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = codigoProduto.length();
			if (i <= 0) {
				continue;
			};
			i--;
			codigoProduto.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " << setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                   Cadastro De Produto                    |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Nome do produto: " << nomeDigitado << endl;
		cout << "                Codigo do produto: " << codigoProduto << endl;
		cout << "                Preço: " << precoProduto << endl;
		cout << "                Quantidade: " << quantidadeProduto << endl;
		if (enterApertado) {
			break;
		};
	};
	// pega preco
	system("cls");
	escolhaMenu = 0;
	enterApertado = false;
	i = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " << setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                   Cadastro De Produto                    |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Nome do produto: " << nomeDigitado << endl;
	cout << "                Codigo do produto: " << codigoProduto << endl;
	cout << "                Preço: " << precoProduto << endl;
	cout << "                Quantidade: " << quantidadeProduto << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleCadastroEstoque();
					break;
				case 61: //f3
					cadastroProduto();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu == 46) || (escolhaMenu == 44)) {
			if (escolhaMenu == 44) {
				escolhaMenu = '.';
			}
			precoProduto += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = precoProduto.length();
			if (i <= 0) {
				continue;
			};
			i--;
			precoProduto.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " << setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                   Cadastro De Produto                    |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Nome do produto: " << nomeDigitado << endl;
		cout << "                Codigo do produto: " << codigoProduto << endl;
		cout << "                Preço: " << precoProduto << endl;
		cout << "                Quantidade: " << quantidadeProduto << endl;
		if (enterApertado) {
			break;
		};
	};
	// pega quantidade
	system("cls");
	escolhaMenu = 0;
	enterApertado = false;
	i = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " << setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                   Cadastro De Produto                    |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Nome do produto: " << nomeDigitado << endl;
	cout << "                Codigo do produto: " << codigoProduto << endl;
	cout << "                Preço: " << precoProduto << endl;
	cout << "                Quantidade: " << quantidadeProduto << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleCadastroEstoque();
					break;
				case 61: //f3
					cadastroProduto();
					break;
				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {
			quantidadeProduto += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = quantidadeProduto.length();
			if (i <= 0) {
				continue;
			};
			i--;
			quantidadeProduto.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " << setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                   Cadastro De Produto                    |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Nome do produto: " << nomeDigitado << endl;
		cout << "                Codigo do produto: " << codigoProduto << endl;
		cout << "                Preço: " << precoProduto << endl;
		cout << "                Quantidade: " << quantidadeProduto << endl;
		if (enterApertado) {
			break;
		};
	};
	// abre banco
	ofstream produtoBDS;
	ifstream procurador;
	if (NumeroLoja == 1) {
		procurador.open("1\\produtoBDS.txt", ios::in);
	}
	else if (NumeroLoja == 2) {
		procurador.open("2\\produtoBDS.txt", ios::in);
	}
	else if (NumeroLoja == 3) {
		procurador.open("3\\produtoBDS.txt", ios::in);
	}
	else {
		menuInicial();
	}
	system("cls");
	do {
		getline(procurador, recebeLinha);
		if (recebeLinha == "codigo: " + codigoProduto) {
			gotoxy(0, 5);
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|               Codigo Inserido Já Utilizado!              |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			Sleep(1000);
			procurador.close();
			return cadastroProduto();
		}
		else if (recebeLinha == "nome: " + nomeDigitado) {
			gotoxy(0, 5);
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|                Nome Inserido Já Utilizado!               |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			Sleep(1000);
			procurador.close();
			return cadastroProduto();
		}
		
	} while (procurador.eof() == NULL);
	procurador.close();
	//lanca bds
	if (NumeroLoja == 1) {
		produtoBDS.open("1\\produtoBDS.txt", ios::app);
	}
	else if (NumeroLoja == 2) {
		produtoBDS.open("2\\produtoBDS.txt", ios::app);
	}
	else if (NumeroLoja == 3) {
		produtoBDS.open("3\\produtoBDS.txt", ios::app);
	}
	else {
		menuInicial();
	}
	produtoBDS << "codigo: " << codigoProduto << endl;
	produtoBDS << "nome: " << nomeDigitado << endl;
	produtoBDS << "preco: " << precoProduto << endl;
	produtoBDS << "quantidade: " << quantidadeProduto << endl;
	gotoxy(0, 5);
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|              Produto Adicionado Com Sucesso!             |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	Sleep(1000);
	return cadastroProduto();
}
//-4
void removeProduto() {
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	if (nivelLoja < 2) { // verifica nivel de funcionario
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|              Usuário sem permissão de acesso             |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return controleCadastroEstoque();
	}
	// var inputs
	string codigoDoProduto = "";
	int escolhaMenu = 0;
	bool enterApertado = false;
	int i = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|               Remover Produto Cadastrado                 |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "               Codigo do produto: " << codigoDoProduto << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleCadastroEstoque();
					break;
				case 61: //f3
					removeProduto();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {

			codigoDoProduto += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = codigoDoProduto.length();
			if (i <= 0) {
				continue;
			};
			i--;
			codigoDoProduto.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|               Remover Produto Cadastrado                 |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "               Codigo do produto: " << codigoDoProduto << endl;
		if (enterApertado) {
			break;
		};
	}
	system("cls");
	// converte codigo de produto
	codigoDoProduto = "codigo: " + codigoDoProduto;
	//var bds
	bool achouSim = false;
	string produtosDoBds;
	ifstream procurador;
	ifstream produtoBDS;
	ofstream transfereBDS;
	// resetando escolhas menu
	escolhaMenu = 0;
	enterApertado = false;
	i = 0;
	if (NumeroLoja == 1) {
		procurador.open("1\\produtoBDS.txt", ios::in);
	}
	else if (NumeroLoja == 2) {
		procurador.open("2\\produtoBDS.txt", ios::in);
	}
	else if (NumeroLoja == 3) {
		procurador.open("3\\produtoBDS.txt", ios::in);
	}
	else {
		menuInicial();
	}
	do {
		getline(procurador, produtosDoBds);
		if (produtosDoBds == codigoDoProduto) {
			
			achouSim = true;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|               Remover Produto Cadastrado                 |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "                " << produtosDoBds << endl; //pega codigo
			getline(procurador, produtosDoBds);
			cout << "                " << produtosDoBds << endl; // exibe nome
			getline(procurador, produtosDoBds);
			cout << "                " << produtosDoBds << endl; // exibe preco
			getline(procurador, produtosDoBds);
			cout << "                " << produtosDoBds << endl; // exibe quantidade
			cout << " Confirma remoção de produto: <enter> ou <f3> para cancelar" << endl;
			while (_kbhit || enterApertado) {
				escolhaMenu = _getch();
				if (escolhaMenu == 0) {
					escolhaMenu = _getch();
					if (escolhaMenu != 0) {
						switch (escolhaMenu) {
						case 59: //f1
							procurador.close();
							menuInicial();
							break;
						case 60: //f2
							procurador.close();
							controleCadastroEstoque();
							break;
						case 61: //f3
							procurador.close();
							removeProduto();
							break;
						default:
							break;
						};
					}
				};
				if (escolhaMenu == 13) {
					enterApertado = true;
				};
				if (enterApertado) {
					break;
				};
			};
		};
		if (enterApertado) {
			break;
		};
	} while (procurador.eof() == NULL);
	procurador.close();
	if (!achouSim) {
		system("cls");
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|              Codigo De Produto Não Encontrado!           |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		return removeProduto();
	}
	//lanca bds
	if (NumeroLoja == 1) {
		transfereBDS.open("1\\transfereBDS.txt");
		produtoBDS.open("1\\produtoBDS.txt");
	}
	else if (NumeroLoja == 2) {
		transfereBDS.open("2\\transfereBDS.txt");
		produtoBDS.open("2\\produtoBDS.txt");
	}
	else if (NumeroLoja == 3) {
		transfereBDS.open("3\\transfereBDS.txt");
		produtoBDS.open("3\\produtoBDS.txt");
	}
	else {
		menuInicial();
	}
	do {
		getline(produtoBDS, produtosDoBds);
		if (codigoDoProduto == produtosDoBds) {
			getline(produtoBDS, produtosDoBds); //pula codigo
			getline(produtoBDS, produtosDoBds); //pula nome
			getline(produtoBDS, produtosDoBds); //pula preco
			getline(produtoBDS, produtosDoBds); //pula quantidade
		}
		
		transfereBDS << produtosDoBds << endl;
	}while (produtoBDS.eof() == NULL);
	transfereBDS.close();
	produtoBDS.close();
	if (NumeroLoja == 1) {
		remove("1\\produtoBDS.txt");
		rename("1\\transfereBDS.txt", "1\\produtoBDS.txt");
	}
	else if (NumeroLoja == 2) {
		remove("2\\produtoBDS.txt");
		rename("2\\transfereBDS.txt", "2\\produtoBDS.txt");
	}
	else if (NumeroLoja == 3) {
		remove("3\\produtoBDS.txt");
		rename("3\\transfereBDS.txt", "3\\produtoBDS.txt");
	}
	else {
		menuInicial();
	}
	system("cls");
	gotoxy(0, 5);
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|              Produto Removido Com Sucesso!               |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	Sleep(1000);
	return controleCadastroEstoque();

	return menuInicial();
}
//-5
void alteraPrecoProduto(){
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	if (nivelLoja < 2) { // verifica nivel de funcionario
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|              Usuário sem permissão de acesso             |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return controleCadastroEstoque();
	}
	// var de inputs
	string nomeDigitado = "",novoPreco = "", recebeLinha = "";
	int escolhaMenu = 0;
	bool enterApertado = false;
	int i = 0;
	// pega nome
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                 Alterar Preço De Produto                 |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Nome do produto: " << nomeDigitado << endl;
	cout << "                Novo Preço: " << novoPreco << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleCadastroEstoque();
					break;
				case 61: //f3
					alteraPrecoProduto();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu >= 97) && (escolhaMenu <= 122) || (escolhaMenu == 32)) {

			nomeDigitado += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = nomeDigitado.length();
			if (i <= 0) {
				continue;
			};
			i--;
			nomeDigitado.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                 Alterar Preço De Produto                 |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Nome do produto: " << nomeDigitado << endl;
		cout << "                Novo Preço: " << novoPreco << endl;
		if (enterApertado) {
			break;
		};
	}
	//pega preco
	system("cls");
	escolhaMenu = 0;
	enterApertado = false;
	i = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                 Alterar Preço De Produto                 |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                Nome do produto: " << nomeDigitado << endl;
	cout << "                Novo Preço: " << novoPreco << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					controleCadastroEstoque();
					break;
				case 61: //f3
					alteraPrecoProduto();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu == 46) || (escolhaMenu == 44)) {
			if (escolhaMenu == 44) {
				escolhaMenu = '.';
			}
			novoPreco += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = novoPreco.length();
			if (i <= 0) {
				continue;
			};
			i--;
			novoPreco.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                 Alterar Preço De Produto                 |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                Nome do produto: " << nomeDigitado << endl;
		cout << "                Novo Preço: " << novoPreco << endl;
		if (enterApertado) {
			break;
		};
	};
	//converte nome e preço
	nomeDigitado = "nome: " + nomeDigitado;
	novoPreco = "preco: " + novoPreco;

	ifstream produtoBDS;
	ofstream transfereBDS;
	if (NumeroLoja == 1) {
		transfereBDS.open("1\\transfereBDS.txt");
		produtoBDS.open("1\\produtoBDS.txt");
	}
	else if (NumeroLoja == 2) {
		transfereBDS.open("2\\transfereBDS.txt");
		produtoBDS.open("2\\produtoBDS.txt");
	}
	else if (NumeroLoja == 3) {
		transfereBDS.open("3\\transfereBDS.txt");
		produtoBDS.open("3\\produtoBDS.txt");
	}
	else {
		menuInicial();
	}
	bool achouSim = false;
	do {
		getline(produtoBDS, recebeLinha);
		if (nomeDigitado == recebeLinha) {
			achouSim = true;
			transfereBDS << recebeLinha << endl; //coloca nome
			getline(produtoBDS, recebeLinha);
			transfereBDS << novoPreco << endl; //altera preco
			getline(produtoBDS, recebeLinha);
		}
		transfereBDS << recebeLinha << endl;
	} while (produtoBDS.eof() == NULL);
	transfereBDS.close();
	produtoBDS.close();
	if (NumeroLoja == 1) {
		remove("1\\produtoBDS.txt");
		rename("1\\transfereBDS.txt", "1\\produtoBDS.txt");
	}
	else if (NumeroLoja == 2) {
		remove("2\\produtoBDS.txt");
		rename("2\\transfereBDS.txt", "2\\produtoBDS.txt");
	}
	else if (NumeroLoja == 3) {
		remove("3\\produtoBDS.txt");
		rename("3\\transfereBDS.txt", "3\\produtoBDS.txt");
	}
	else {
		menuInicial();
	}
	system("cls");
	if (!achouSim) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                  Produto Não Encontrado!                 |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return alteraPrecoProduto();
	}
	else if (achouSim) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|          Preço De Produto Alterado Com Sucesso!          |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return controleCadastroEstoque();
	}
	return menuInicial();
}

/*[3] Relatorios
 submenu */
void relatorioMenu() {
	system("mode con:lines=25 cols=60");
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	int escolhaMenu;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                    Menu De Relatórios                    |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "| [1] Relatório De Vendas Por Data                         |" << endl;
	cout << "| [2] Relatório Detalhado De Caixa                         |" << endl;
	cout << "| [3] Relatório Detalhado De Pedido                        |" << endl;
	cout << "| [4] Relatório De Mercadoria Em Estoque                   |" << endl;
	cout << "| [5] Relatório De Produtos Mais Vendidos                  |" << endl;
	cout << "| [6] Sair Do Programa                                     |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	do {

		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
		};
		system("cls");
		switch (escolhaMenu) {

		case 59: //f1
			menuInicial();
			break;
		case 60: //f2
			menuInicial();
			break;
		case 61: //f3
			relatorioMenu();
			break;
		case '1':
			relatorioVendas();
			break;
		case '2':
			relatorioDetalhadoCaixa();
			break;
		case '3':
			relatorioDetalhadoPedido();
			break;
		case '4':
			relatorioEstoque();
			break;
		case '5':
			relatorioProdutos();
			break;
		case '6':
			int op;
			gotoxy(0, 5);
			cout << "+----------------------------------------------------------+" << endl;
			cout << "| Fechando programa! Aperte [1] para cancelar fechamento...|" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			op = _getch();
			switch (op)
			{
			case '1':
				return relatorioMenu();
			default:
				exit(0);
				break;
			}
			break;
		default:
			relatorioMenu();
			break;
		}
	} while (escolhaMenu == 0);
}
//-1
void relatorioVendas() {
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	if (nivelLoja < 2) { // verifica nivel de funcionario
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|              Usuário sem permissão de acesso             |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return relatorioMenu();
	}
	// var de inputs
	string dataPartida = "", dataFinal = "";
	int escolhaMenu = 0;
	bool enterApertado = false;
	int i = 0;
	int cont = 0;
	// pega dataPartida
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                   Relatório Por Datas                    |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                  Data Inicial: " << dataPartida << endl;
	cout << "                  Data Final: " << dataFinal << endl;
	cout << "                               <Enter>";
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioMenu();
					break;
				case 61: //f3
					relatorioVendas();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {
			cont++;
			if (cont == 3 || cont == 6) {
				dataPartida += ".";
				cont++;
			}
			dataPartida += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = dataPartida.length();
			if (i <= 0) {
				continue;
			};
			i--;
			cont--;
			dataPartida.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                   Relatório Por Datas                    |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                  Data Inicial: " << dataPartida << endl;
		cout << "                  Data Final: " << dataFinal << endl;
		cout << "                               <Enter>";
		if (enterApertado) {
			break;
		};
	}
	// pega dataFinal
	system("cls");
	escolhaMenu = 0;
	enterApertado = false;
	i = 0;
	cont = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                   Relatório Por Datas                    |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                  Data Inicial: " << dataPartida << endl;
	cout << "                  Data Final: " << dataFinal << endl;
	cout << "                               <Enter>";
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioMenu();
					break;
				case 61: //f3
					relatorioVendas();
					break;
				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {
			cont++;
			if (cont == 3 || cont == 6) {
				dataFinal += ".";
				cont++;
			}
			dataFinal += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = dataFinal.length();
			if (i <= 0) {
				continue;
			};
			i--;
			cont--;
			dataFinal.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                   Relatório Por Datas                    |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                  Data Inicial: " << dataPartida << endl;
		cout << "                  Data Final: " << dataFinal << endl;
		cout << "                               <Enter>";
		if (enterApertado) {
			break;
		};
	};
	system("cls");
	//procura BdS
	ifstream procurador;
	string dataTemp = "",valorTemp = "", recebeLinha = "";
	bool achouSim = false;
	float ttValor = 0;
	cont = 0;
	if (NumeroLoja == 1) {
		procurador.open("1\\registroVendas.txt", ios::in);
	}
	else if (NumeroLoja == 2) {
		procurador.open("2\\registroVendas.txt", ios::in);
	}
	else if (NumeroLoja == 3) {
		procurador.open("3\\registroVendas.txt", ios::in);
	}
	else {
		menuInicial();
	}
	do {
		getline(procurador, recebeLinha); // só vai achar data de partida
		if (recebeLinha == "!!!fim dia " + dataPartida + " !!!") {
			achouSim = true;
			system("mode con:lines=300 cols=60");
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|                   Relatório Por Datas                    |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|          Datas De Pesqusa: " << dataPartida << " Á " << dataFinal << "           |"<< endl;
			cout << "+----------------------------------------------------------+" << endl;
			do {
				if (recebeLinha[0] == '!') {
					cont++;
					recebeLinha.erase(0, 11);
					recebeLinha.erase(8);
					dataTemp = recebeLinha;
					getline(procurador, recebeLinha);
					recebeLinha.erase(0, 21);
					valorTemp = recebeLinha;
					ttValor += stod(recebeLinha);
					//fixed << setprecision(2) << totPedidos << setw(40 - intLength(totPedidos))
					cout << "|      Data de Caixa: " << dataTemp << " Total Em Vendas: " << setw(11) << left <<valorTemp << "|" << endl;
					cout << "+----------------------------------------------------------+" << endl;
					if (dataTemp == dataFinal) {
						procurador.close();
						break;
					};
				};
			getline(procurador, recebeLinha);
			} while (procurador.eof() == NULL);
		};
		if (achouSim) {
			procurador.close();
			break;
		}
	} while (procurador.eof() == NULL);
	procurador.close();
	if (!achouSim) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|          Não Há Registro De Vendas Entre Datas!          |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return relatorioVendas();
	};
	cout << "|                          Total                           |" << endl;
	cout << "|                    Caixas Contados: " << setw(4) << left << cont << setw(18) << right<< "|" << endl;
	cout << "|                 Total entre datas: " << setw(10) << left << fixed << setprecision(2) << ttValor  << setw(13) << right << "|" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioMenu();
					break;
				case 61: //f3
					relatorioVendas();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			system("mode con:lines=25 cols=60");
			return relatorioVendas();
			break;
		}
	};
	return menuInicial();
}
//-2
void relatorioDetalhadoCaixa() {
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	if (nivelLoja < 2) { // verifica nivel de funcionario
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|              Usuário sem permissão de acesso             |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return relatorioMenu();
	}
	// var de inputs
	string dataPartida = "";
	int escolhaMenu = 0;
	bool enterApertado = false;
	int i = 0;
	int cont = 0;
	// pega dataPartida
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|               Relatório Detalhado De Caixa               |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                  Data De Caixa: " << dataPartida << endl;
	cout << "                               <Enter>";
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioMenu();
					break;
				case 61: //f3
					relatorioDetalhadoCaixa();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {
			cont++;
			if (cont == 3 || cont == 6) {
				dataPartida += ".";
				cont++;
			}
			dataPartida += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = dataPartida.length();
			if (i <= 0) {
				continue;
			};
			i--;
			cont--;
			dataPartida.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|               Relatório Detalhado De Caixa               |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                  Data De Caixa: " << dataPartida << endl;
		cout << "                               <Enter>";
		if (enterApertado) {
			break;
		};
	}
	system("cls");
	//procura bds
	string recebeLinha = "", dataTemp = "";
	ifstream procurador;
	// valida se caixa existe
	dataTemp = dataPartida;
	dataPartida += ".txt";
	if (NumeroLoja == 1) {
		dataPartida = "1\\" + dataPartida;
	}
	else if (NumeroLoja == 2) {
		dataPartida = "2\\" + dataPartida;
	}
	else if (NumeroLoja == 3) {
		dataPartida = "3\\" + dataPartida;
	}
	else {
		menuInicial();
	}

	procurador.open(dataPartida, ios::in);
	if (!procurador) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|               Data De Caixa Não Encontrada!              |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return relatorioDetalhadoCaixa();
	}
	else {
		system("mode con:lines=300 cols=60");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|               Relatório Detalhado De Caixa               |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|               Registro De Caixa: " << dataTemp << "                |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		do {
			getline(procurador, recebeLinha);
			cout << "|        " << setw(44) << left << recebeLinha << setw(7) << right << "|" << endl; // exibe relatorio
			if (recebeLinha == "=============Fim de Registro==============") { break; };
		} while (procurador.eof() == NULL);
		procurador.close();
		cout << "+----------------------------------------------------------+" << endl;
		while (_kbhit || enterApertado) {
			escolhaMenu = _getch();
			if (escolhaMenu == 0) {
				escolhaMenu = _getch();
				if (escolhaMenu != 0) {
					switch (escolhaMenu) {
					case 59: //f1
						menuInicial();
						break;
					case 60: //f2
						relatorioMenu();
						break;
					case 61: //f3
						relatorioDetalhadoCaixa();
						break;

					default:
						break;
					}
				};
			}
			else if (escolhaMenu == 13) {
				system("mode con:lines=25 cols=60");
				return relatorioDetalhadoCaixa();
				break;
			}

		};	
	}
	return menuInicial();
}
//-3
void relatorioDetalhadoPedido() {
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	// var de inputs
	string dataPartida = "", numPedido = "";
	int escolhaMenu = 0;
	bool enterApertado = false;
	int i = 0;
	int cont = 0;
	
	// pega dataPartida
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|               Relatório Detalhado De Pedido              |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                  Data De Caixa: " << dataPartida << endl;
	cout << "                  Numero Pedido: " << numPedido << endl;
	cout << "                               <Enter>";
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioMenu();
					break;
				case 61: //f3
					relatorioDetalhadoPedido();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {
			cont++;
			if (cont == 3 || cont == 6) {
				dataPartida += ".";
				cont++;
			}
			dataPartida += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = dataPartida.length();
			if (i <= 0) {
				continue;
			};
			i--;
			cont--;
			dataPartida.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|               Relatório Detalhado De Pedido              |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                  Data De Caixa: " << dataPartida << endl;
		cout << "                  Numero Pedido: " << numPedido << endl;
		cout << "                               <Enter>";
		if (enterApertado) {
			break;
		};
	}
	system("cls");
	escolhaMenu = 0;
	enterApertado = false;
	i = 0;
	cont = 0;
	// pega Pedido
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|               Relatório Detalhado De Pedido              |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                  Data De Caixa: " << dataPartida << endl;
	cout << "                  Numero Pedido: " << numPedido << endl;
	cout << "                               <Enter>";
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioMenu();
					break;
				case 61: //f3
					relatorioDetalhadoPedido();
					break;

				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {
			numPedido += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = numPedido.length();
			if (i <= 0) {
				continue;
			};
			i--;
			numPedido.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|               Relatório Detalhado De Pedido              |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                  Data De Caixa: " << dataPartida << endl;
		cout << "                  Numero Pedido: " << numPedido << endl;
		cout << "                               <Enter>";
		if (enterApertado) {
			break;
		};
	};


	system("cls");
	//bando de dados
	bool achouSim = false;
	string recebeLinha = "", nomeTemp, quantTemp, precoTemp, ttTemp;
	ifstream procurador;
	// inputs
	if (NumeroLoja == 1) {
		procurador.open("1\\registroVendas.txt", ios::in);
	}
	else if (NumeroLoja == 2) {
		procurador.open("2\\registroVendas.txt", ios::in);
	}
	else if (NumeroLoja == 3) {
		procurador.open("3\\registroVendas.txt", ios::in);
	}
	else {
		menuInicial();
	}
		do {
			getline(procurador, recebeLinha);
			if (recebeLinha == "pedido: " + numPedido) {
				getline(procurador, recebeLinha);   /// acha pedido e data
				if (recebeLinha == "data: " + dataPartida) {
					achouSim = true;
					system("mode con:lines=300 cols=60");
					cout << "+----------------------------------------------------------+" << endl;
					cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
					cout << "+----------------------------------------------------------+" << endl;
					cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
					cout << "+----------------------------------------------------------+" << endl;
					cout << "|               Relatório Detalhado De Pedido              |" << endl;
					cout << "+----------------------------------------------------------+" << endl;
					cout << "|            Registro De Pedido: " << numPedido << " Data: " << dataPartida << "        |" << endl;
					cout << "+----------------------------------------------------------+" << endl;
					getline(procurador, recebeLinha);
					recebeLinha.erase(0, 5);
					cout << "|                      Hora: " << recebeLinha <<"                     |"<< endl; //cabecalho
					cout << "+----------------------------------------------------------+" << endl;
					cout << "|      produto     quantidade     preço     sub total      |" << endl;
					cout << "+----------------------------------------------------------+" << endl;
					do {
						if (recebeLinha[1] == 'e') { // quebra de achar proximo p e dido
							break;
						}
						getline(procurador, recebeLinha); // produto || -----
						if (recebeLinha == "-----------------") {
							getline(procurador, recebeLinha);
							recebeLinha.erase(0, 14);
							//convertendo valor digitado para float. 
							double totTemp = 0.0;
							stringstream ss2;
							string s1 = recebeLinha;
							ss2 << s1;
							ss2 >> totTemp;
							cout << "+----------------------------------------------------------+" << endl;
							cout << "|                  Total Pedido: "<< setw(10) << left << fixed << setprecision(2) << totTemp << setw(17) <<right << "|" << endl;
							cout << "+----------------------------------------------------------+" << endl;
							procurador.close();
							while (_kbhit || enterApertado) {
								escolhaMenu = _getch();
								if (escolhaMenu == 0) {
									escolhaMenu = _getch();
									if (escolhaMenu != 0) {
										switch (escolhaMenu) {
										case 59: //f1
											menuInicial();
											break;
										case 60: //f2
											relatorioMenu();
											break;
										case 61: //f3
											relatorioDetalhadoPedido();
											break;

										default:
											break;
										}
									};
								}
								else if (escolhaMenu == 13) {
									system("mode con:lines=25 cols=60");
									return relatorioDetalhadoPedido();
									break;
								}
								break;
							};
						}
						recebeLinha.erase(0, 9);
						cout <<"|" << setw(17) << left << recebeLinha;
						getline(procurador, recebeLinha); // quantidade
						recebeLinha.erase(0, 12);
						cout << setw(7)<< right << recebeLinha;
						getline(procurador, recebeLinha); // preco
						recebeLinha.erase(0, 7);
						
						//convertendo valor digitado para float. 
						double totTemp2 = 0.0;
						stringstream ss;
						string s = recebeLinha;
						ss << s;
						ss >> totTemp2;
						cout << setw(14) <<right << fixed << setprecision(2) << totTemp2;
						getline(procurador, recebeLinha); // total produto
						recebeLinha.erase(0, 15);

						//convertendo valor digitado para float. 
						double totTemp3 = 0.0;
						stringstream sss;
						string ssss = recebeLinha;
						sss << ssss;
						sss >> totTemp3;
						cout << setw(13)<< right << fixed << setprecision(2) << totTemp3;
						cout << setw(8) << right << "|" << endl;
					} while (procurador.eof() == NULL);
				};
			};
		} while (procurador.eof() == NULL);
	procurador.close();
	if (!achouSim) {
		
	}
	return menuInicial();
}
//-4
void relatorioEstoque() {
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	int escolhaMenu = 0;
	int escolhaSub = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|             Sub-Menu Relatório De Mercadoria             |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "| [1] Procurar Por Nome De Produto                         |" << endl;
	cout << "| [2] Lista De Todos Os Produtos                           |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	do {

		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
		};
		system("cls");
		switch (escolhaMenu) {

		case 59: //f1
			menuInicial();
			break;
		case 60: //f2
			relatorioMenu();
			break;
		case 61: //f3
			relatorioEstoque();
			break;
		case '1':
			escolhaSub = 1;
			break;
		case '2':
			escolhaSub = 2;
			break;
		default:
			relatorioEstoque();
			break;
		}
	} while (escolhaMenu == 0);

	//bando de dados
	ifstream procurador;
	string recebeBds = "", nomeDigitado = "";
	bool achouSim = false, enterApertado = false;
	int i = 0;
	escolhaMenu = 0;
	// //////////////// por nome
	if (escolhaSub == 1) {
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                    Pesquisa Por Nome                     |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                  Nome do produto: " << nomeDigitado << endl;
		cout << "                               <Enter>";
		while (_kbhit || enterApertado) {
			escolhaMenu = _getch();
			if (escolhaMenu == 0) {
				escolhaMenu = _getch();
				if (escolhaMenu != 0) {
					switch (escolhaMenu) {
					case 59: //f1
						menuInicial();
						break;
					case 60: //f2
						relatorioEstoque();
						break;
					case 61: //f3
						relatorioEstoque();
						break;
					default:
						break;
					}
				};
			}
			else if (escolhaMenu == 13) {
				enterApertado = true;
				break;
			}
			else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu >= 97) && (escolhaMenu <= 122) || (escolhaMenu == 32)) {

				nomeDigitado += escolhaMenu;
			}
			else if (escolhaMenu == 8) {
				i = nomeDigitado.length();
				if (i <= 0) {
					continue;
				};
				i--;
				nomeDigitado.erase(i);
			};
			system("cls");
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|                    Pesquisa Por Nome                     |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "                  Nome do produto: " << nomeDigitado << endl;
			cout << "                               <Enter>";
			if (enterApertado) {
				break;
			};
		}
		if (NumeroLoja == 1) {
			procurador.open("1\\produtoBDS.txt", ios::in);
		}
		else if (NumeroLoja == 2) {
			procurador.open("2\\produtoBDS.txt", ios::in);
		}
		else if (NumeroLoja == 3) {
			procurador.open("3\\produtoBDS.txt", ios::in);
		}
		else {
			menuInicial();
		}
		do {
			getline(procurador, recebeBds);
			if (recebeBds == "nome: " + nomeDigitado) {
				achouSim = true;
				system("cls");
				cout << "+----------------------------------------------------------+" << endl;
				cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
				cout << "+----------------------------------------------------------+" << endl;
				cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
				cout << "+----------------------------------------------------------+" << endl;
				cout << "|                    Pesquisa Por Nome                     |" << endl;
				cout << "+----------------------------------------------------------+" << endl;
				cout << "|         Produto         Preço         Quantidade         |" << endl;
				cout << "+----------------------------------------------------------+" << endl; 
				cout << "|" << setw(17) << right << nomeDigitado;
				getline(procurador, recebeBds); // preço
				recebeBds.erase(0, 7);
				cout << setw(12) << right << recebeBds;
				getline(procurador, recebeBds); // quantidade
				recebeBds.erase(0, 12);
				cout << setw(16) << right << recebeBds;
				cout << setw(14) << right << "|" << endl;
				cout << "+----------------------------------------------------------+" << endl;
				break;
			}
		} while (procurador.eof() == NULL);
		if (!achouSim) {
			gotoxy(0, 5);
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|                 Produto não encontrado!                  |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			Sleep(1000);
			return relatorioEstoque();
		}
		procurador.close();
	}
	////////////// todos produtos
	else if (escolhaSub == 2) {
		system("mode con:lines=300 cols=60");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                      Todos Produtos                      |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|     Codigo       Produto       Preço       Quantidade    |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		if (NumeroLoja == 1) {
			procurador.open("1\\produtoBDS.txt", ios::in);
		}
		else if (NumeroLoja == 2) {
			procurador.open("2\\produtoBDS.txt", ios::in);
		}
		else if (NumeroLoja == 3) {
			procurador.open("3\\produtoBDS.txt", ios::in);
		}
		else {
			menuInicial();
		}
		do {
			getline(procurador, recebeBds); // codigo
			if (recebeBds == "\0") {
				continue;
			}
			recebeBds.erase(0, 7);
			cout <<"| "<< setw(8) << right << recebeBds;
			getline(procurador, recebeBds); // nome
			recebeBds.erase(0, 5);
			cout  << setw(17) << right << recebeBds;
			getline(procurador, recebeBds); // preco
			recebeBds.erase(0, 7);
			cout << setw(12) << right <<recebeBds;
			getline(procurador, recebeBds); // quantidade
			recebeBds.erase(0, 12);
			cout << setw(16) << right << recebeBds;
			cout << setw(5) << right << "|" << endl;
			cout << "+----------------------------------------------------------+" << endl;
		} while (procurador.eof() == NULL);
		procurador.close();
	}
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioEstoque();
					break;
				case 61: //f3
					relatorioEstoque();
					break;
				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			return relatorioMenu();
			break;
		}
	};

	
}
//-5 
void relatorioProdutos() {
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	int escolhaMenu = 0;
	int escolhaSub = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|             Sub-Menu Produtos Mais Vendidos              |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "| [1] Pesquisar Por Nome De Produto                        |" << endl;
	cout << "| [2] Pesquisar Por Datas                                  |" << endl;
	cout << "| [3] Lista De Todos Os Produtos                           |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	do {

		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
		};
		system("cls");
		switch (escolhaMenu) {

		case 59: //f1
			menuInicial();
			break;
		case 60: //f2
			relatorioMenu();
			break;
		case 61: //f3
			relatorioProdutos();
			break;
		case '1':
			pesquisaNome();
			break;
		case '2':
			pesquisaData();
			break;
		default:
			pesquisaTotal();
			break;
		}
	} while (escolhaMenu == 0);

};
//subfuncao 1 
void pesquisaNome() {
	system("cls");
	int escolhaMenu = 0;
	string nomeDigitado = "";
	bool achouSim = false, enterApertado = false;
	int i = 0;
	escolhaMenu = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                    Pesquisa Por Nome                     |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                  Nome do produto: " << nomeDigitado << endl;
	cout << "                               <Enter>";
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioProdutos();
					break;
				case 61: //f3
					pesquisaNome();
					break;
				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu >= 97) && (escolhaMenu <= 122) || (escolhaMenu == 32)) {

			nomeDigitado += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = nomeDigitado.length();
			if (i <= 0) {
				continue;
			};
			i--;
			nomeDigitado.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                    Pesquisa Por Nome                     |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                  Nome do produto: " << nomeDigitado << endl;
		cout << "                               <Enter>";
		if (enterApertado) {
			break;
		};
	}

	system("cls");
	//bds
	ifstream procurador;
	string recebeLinha = "";
	int quantProd = 0, quantSoma = 0;
	float totalVendido = 0, precoProd = 0;
	if (NumeroLoja == 1) {
		procurador.open("1\\registroVendas.txt", ios::in);
	}
	else if (NumeroLoja == 2) {
		procurador.open("2\\registroVendas.txt", ios::in);
	}
	else if (NumeroLoja == 3) {
		procurador.open("3\\registroVendas.txt", ios::in);
	}
	else {
		menuInicial();
	}
	do {
		getline(procurador, recebeLinha);
		if (recebeLinha == "produto: " + nomeDigitado) {
			achouSim = true;
			getline(procurador, recebeLinha); //  pega quantidade
			recebeLinha.erase(0, 11);
			quantProd += stoi(recebeLinha);
			quantSoma = stoi(recebeLinha);
			getline(procurador, recebeLinha); // pega preco
			recebeLinha.erase(0, 6);
			//convertendo valor digitado para float. 
			double totTemp = 0.0;
			stringstream ss;
			string s = recebeLinha;
			ss << s;
			ss >> totTemp;
			precoProd = totTemp;
			totalVendido += precoProd * quantSoma;
		};
	} while (procurador.eof() == NULL);
	procurador.close();
	if (!achouSim) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|              Produto Sem Registro De Venda               |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return pesquisaNome();
	}
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                    Pesquisa Por Nome                     |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "| Produto: " << setw(17) << left << nomeDigitado << setw(32) << right << "|" << endl;
	cout << "| quantidade vendidas: " << setw(15) << left << fixed << setprecision(2) << quantProd << setw(22) << right << "|" << endl;
	cout << "| total em vendas: " << setw(15) << left << fixed << setprecision(2) << totalVendido << setw(26) << right << "|" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioProdutos();
					break;
				case 61: //f3
					pesquisaNome();
					break;
				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			return pesquisaNome();
			break;
		}
	};
	return menuInicial();
}
//subfuncao 2
void pesquisaData() {
	system("cls");
	string dataPartida = "", dataFinal = "";
	int escolhaMenu = 0;
	bool enterApertado = false;
	int i = 0;
	int cont = 0;
	// pega dataPartida
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                Venda De Produtos Por Data                |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                  Data Inicial: " << dataPartida << endl;
	cout << "                  Data Final: " << dataFinal << endl;
	cout << "                               <Enter>";
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioProdutos();
					break;
				case 61: //f3
					pesquisaData();
					break;
				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {
			cont++;
			if (cont == 3 || cont == 6) {
				dataPartida += ".";
				cont++;
			}
			dataPartida += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = dataPartida.length();
			if (i <= 0) {
				continue;
			};
			i--;
			cont--;
			dataPartida.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                   Relatório Por Datas                    |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                  Data Inicial: " << dataPartida << endl;
		cout << "                  Data Final: " << dataFinal << endl;
		cout << "                               <Enter>";
		if (enterApertado) {
			break;
		};
	}
	// pega dataFinal
	system("cls");
	escolhaMenu = 0;
	enterApertado = false;
	i = 0;
	cont = 0;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                Venda De Produtos Por Data                |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "                  Data Inicial: " << dataPartida << endl;
	cout << "                  Data Final: " << dataFinal << endl;
	cout << "                               <Enter>";
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioMenu();
					break;
				case 61: //f3
					relatorioVendas();
					break;
				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			enterApertado = true;
			break;
		}
		else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {
			cont++;
			if (cont == 3 || cont == 6) {
				dataFinal += ".";
				cont++;
			}
			dataFinal += escolhaMenu;
		}
		else if (escolhaMenu == 8) {
			i = dataFinal.length();
			if (i <= 0) {
				continue;
			};
			i--;
			cont--;
			dataFinal.erase(i);
		};
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                   Relatório Por Datas                    |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "                  Data Inicial: " << dataPartida << endl;
		cout << "                  Data Final: " << dataFinal << endl;
		cout << "                               <Enter>";
		if (enterApertado) {
			break;
		};
	};
	system("cls");
	//procura BdS

	ifstream procurador;
	string recebeLinha = "", nTemp = "";
	string recebeNome[100];
	int recebeQuant[100], somaQuant = 0, qTemp;
	float recebeTp[100], somaTotal = 0, tTemp;
	bool achouSim = false;
	cont = 0;

	if(NumeroLoja == 1) {
	procurador.open("1\\registroVendas.txt", ios::in);
	}
	else if (NumeroLoja == 2) {
	procurador.open("2\\registroVendas.txt", ios::in);
	}
	else if (NumeroLoja == 3) {
	procurador.open("3\\registroVendas.txt", ios::in);
	}
	else {
	menuInicial();
	}
	do {
		getline(procurador, recebeLinha);
		if (recebeLinha == "data: " + dataPartida) {
			achouSim = true;
			do {
				getline(procurador, recebeLinha); // pega nome produto
				if (recebeLinha == "!!! fim dia " + dataFinal + " !!!") { break; }; // quebra na data final
				if ((recebeLinha[0] == 'p') && (recebeLinha[2] == 'o')) {
					recebeNome[cont] = recebeLinha;
					getline(procurador, recebeLinha); // pega quantidade
					recebeLinha.erase(0, 11);
					recebeQuant[cont] = stoi(recebeLinha);
					getline(procurador, recebeLinha); // pula preco
					getline(procurador, recebeLinha); // tt prod
					recebeLinha.erase(0, 14);
					//convertendo valor digitado para float. 
					double totTemp = 0.0;
					stringstream ss2;
					string s1 = recebeLinha;
					ss2 << s1;
					ss2 >> totTemp;
					recebeTp[cont] = totTemp;
					for (int i = 0; i < cont; i++) {
						if (recebeNome[cont] == recebeNome[i]) { // tratamento de produto repetido
							recebeQuant[i] += recebeQuant[cont];
							recebeTp[i] += recebeTp[cont];
							cont--;
						};
					};
					cont++;
				};
			} while (procurador.eof() == NULL);
		};
		if (achouSim) {
			procurador.close();
			break;
		};
	} while (procurador.eof() == NULL);
	procurador.close();
	//////////////////// erro
	if (!achouSim) {
		gotoxy(0, 5);
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|               Data Inserida Não Encontrada!              |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		Sleep(1000);
		return pesquisaData();
	}

	//organiza lista
	for (int i = 0; i < cont; i++) {
		for (int ii = 0; ii < cont; ii++) {
			if (recebeQuant[i] > recebeQuant[ii]) {
				nTemp = recebeNome[i];
				qTemp = recebeQuant[i];
				tTemp = recebeTp[i];
				recebeNome[i] = recebeNome[ii];
				recebeQuant[i] = recebeQuant[ii];
				recebeTp[i] = recebeTp[ii];
				recebeNome[ii] = nTemp;
				recebeQuant[ii] = qTemp;
				recebeTp[ii] = tTemp;
			}
		}
	};

	// exibe lista
	system("mode con:lines=300 cols=60");
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|                Venda De Produtos Por Data                |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|          Datas De Pesqusa: " << dataPartida << " Á " << dataFinal << "           |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	for (int i = 0; i < cont; i++) {
		cout << "| " << setw(26) << left << recebeNome[i] << setw(32) << right << "|" << endl;
		cout << "| Quantidade vendidas: " << setw(15) << left << recebeQuant[i] << setw(22) << right << "|" << endl;
		cout << "| Total em vendas: " << setw(15) << left << fixed << setprecision(2) << recebeTp[i] << setw(26) << right << "|" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		somaQuant += recebeQuant[i];
		somaTotal += recebeTp[i];
	};
	cout << "|          Quantidade de produtos vendidos: " << setw(4) << left << somaQuant << setw(12) << right << "|" << endl;
	cout << "|          Total de vendas durante periodo: "<<setw(10) << left << fixed << setprecision(2)<< somaTotal << setw(6)<< right <<"|"<< endl;
	cout << "+----------------------------------------------------------+" << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioProdutos();
					break;
				case 61: //f3
					pesquisaData();
					break;
				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			return pesquisaData();
			break;
		}
	};
	return menuInicial();
}
//subfuncao 3
void pesquisaTotal() { 
	system("cls");
	ifstream procurador;
	string recebeNome[100], recebeLinha, nTemp;
	int recebeQuant[100], somaQuant = 0, qTemp = 0;
	float recebeTp[100], somaTotal = 0, tTemp = 0;
	int cont = 0;
	int escolhaMenu = 0;
	bool enterApertado = false;
	system("mode con:lines=300 cols=60");
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	cout << "|             Lista De Produtos Mais Vendidos              |" << endl;
	cout << "+----------------------------------------------------------+" << endl;

	//pega lista do bd
	if (NumeroLoja == 1) {
		procurador.open("1\\registroVendas.txt", ios::in);
	}
	else if (NumeroLoja == 2) {
		procurador.open("2\\registroVendas.txt", ios::in);
	}
	else if (NumeroLoja == 3) {
		procurador.open("3\\registroVendas.txt", ios::in);
	}
	else {
		menuInicial();
	}
	do {
		getline(procurador, recebeLinha); // pega nome produto
		if ((recebeLinha[0] == 'p') && (recebeLinha[2] == 'o')) {
			recebeNome[cont] = recebeLinha;
			getline(procurador, recebeLinha); // pega quantidade
			recebeLinha.erase(0, 11);
			recebeQuant[cont] = stoi(recebeLinha);
			getline(procurador, recebeLinha); // pula preco
			getline(procurador, recebeLinha); // tt prod
			recebeLinha.erase(0, 14);
			//convertendo valor digitado para float. 
			double totTemp = 0.0;
			stringstream ss2;
			string s1 = recebeLinha;
			ss2 << s1;
			ss2 >> totTemp;
			recebeTp[cont] = totTemp;
			for (int i = 0; i < cont; i++) {
				if (recebeNome[cont] == recebeNome[i]) { // tratamento de produto repetido
					recebeQuant[i] += recebeQuant[cont];
					recebeTp[i] += recebeTp[cont];
					cont--;
				};
			};
			cont++;
		};
	} while (procurador.eof() == NULL);
	procurador.close();

	//organiza lista
	for (int i = 0; i < cont; i++) {
		for (int ii = 0; ii < cont; ii++) {
			if (recebeQuant[i] > recebeQuant[ii]) {
				nTemp = recebeNome[i];
				qTemp = recebeQuant[i];
				tTemp = recebeTp[i];
				recebeNome[i] = recebeNome[ii];
				recebeQuant[i] = recebeQuant[ii];
				recebeTp[i] = recebeTp[ii];
				recebeNome[ii] = nTemp;
				recebeQuant[ii] = qTemp;
				recebeTp[ii] = tTemp;
			}
		}
	}

	//exibe Lista
	for (int i = 0; i < cont; i++) {
		cout << "| " << setw(26) << left << recebeNome[i] << setw(32) << right << "|" << endl;
		cout << "| Quantidade vendidas: " << setw(15) << left << recebeQuant[i] << setw(22) << right << "|" << endl;
		cout << "| Total em vendas: " << setw(15) << left << fixed << setprecision(2) << recebeTp[i] << setw(26) << right << "|" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		somaQuant += recebeQuant[i];
		somaTotal += recebeTp[i];
	};
	cout << "|          Quantidade de produtos vendidos: " << setw(4) << left << somaQuant << setw(12) << right << "|" << endl;
	cout << "|          Total de vendas durante periodo: " << setw(10) << left << fixed << setprecision(2) << somaTotal << setw(6) << right << "|" << endl;
	cout << "+----------------------------------------------------------+" << endl;
	while (_kbhit || enterApertado) {
		escolhaMenu = _getch();
		if (escolhaMenu == 0) {
			escolhaMenu = _getch();
			if (escolhaMenu != 0) {
				switch (escolhaMenu) {
				case 59: //f1
					menuInicial();
					break;
				case 60: //f2
					relatorioProdutos();
					break;
				case 61: //f3
					pesquisaTotal();
					break;
				default:
					break;
				}
			};
		}
		else if (escolhaMenu == 13) {
			return relatorioProdutos();
			break;
		}
	};
	return menuInicial();
}
//[4] Balcao
void balcaoSacola() {
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	if (!verificaCaixa()) {
		return menuInicial();
	};
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	char timeStr[128];
	char dateStr[13];
	_strtime_s(timeStr, 128);
	_strdate_s(dateStr);

	string codigoDoBds, recebeNome, recebePreco, pedidodoispontos, recebeQuantidade;
	int cont = 0, novoEstoque = 0;
	bool kikatForVirgem = true;
	static int numeroPedido = 0;
	float subTotal = 0; float totalPedido = 0; float trocoPedido = 0;

	struct produtos_balcao {
		int codigo;
		string nome;
		float preco;
		int quantidade;
	} sacola[MAX];

	// var inputs
	system("cls");
	int ii = 0;
	do {
		maisPedido:
		bool achouSim = false;
		string codigoPedido = "";
		int escolhaMenu = 0;
		bool enterApertado = false;
		int i = 0;
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|      Balcão       || Hora: " << timeStr <<"   ||  F5-Pagar       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                    Codigo Do Produto: " << setw(6) << left << codigoPedido << setw(14) << right << "|" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|      Produto      Preço     Quantidade     Sub-Total     |";
		for (int ii = 0; ii < cont;) {
			cout << "| " << setw(17) << left << sacola[ii].nome;
			cout << setw(6) << right <<sacola[ii].preco;
			cout << setw(11) << right << sacola[ii].quantidade;
			cout << setw(16) << right << sacola[ii].preco * sacola[ii].quantidade;
			cout << setw(8) << right << "|" << endl;
			ii++;
		};
		cout << "|                        Total: " << setw(10) << left << totalPedido<< "                 |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		while (_kbhit || escolhaMenu == 63) {
			escolhaMenu = _getch();
			if (escolhaMenu == 0) {
				escolhaMenu = _getch();
				if (escolhaMenu != 0) {
					switch (escolhaMenu) {
					case 59: //f1
						menuInicial();
						break;
					case 60: //f2
						menuInicial();
						break;
					case 61: //f3
						balcaoSacola();
						break;
					case 63:
						goto finaliza;
						break;
					default:
						break;
					}
				};
			}
			else if (escolhaMenu == 13) {
				enterApertado = true;
				break;
			}
			else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57)) {

				codigoPedido += escolhaMenu;
			}
			else if (escolhaMenu == 8) {
				i = codigoPedido.length();
				if (i <= 0) {
					continue;
				};
				i--;
				codigoPedido.erase(i);
			};
			system("cls");
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|      Balcão       || Hora: " << timeStr << "   ||  F5-Pagar       |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|                    Codigo Do Produto: " << setw(6) << left << codigoPedido << setw(14) << right << "|" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			for (int ii = 0; ii < cont;) {
				cout << "| " << setw(17) << left << sacola[ii].nome;
				cout << setw(6) << right << fixed <<setprecision(2) << sacola[ii].preco;
				cout << setw(11) << right << sacola[ii].quantidade;
				cout << setw(16) << right << sacola[ii].preco * sacola[ii].quantidade;
				cout << setw(8) << right << "|" << endl;
				ii++;
			};
			cout << "|                        Total: " << setw(10) << left << fixed << setprecision(2) << totalPedido << "                 |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			if (enterApertado) {
				break;
			};
		};

		codigoPedido = "codigo: " + codigoPedido;
		ifstream procurador;
		if (NumeroLoja == 1) {
			procurador.open("1\\produtoBDS.txt", ios::in);
		}
		else if (NumeroLoja == 2) {
			procurador.open("2\\produtoBDS.txt", ios::in);
		}
		else if (NumeroLoja == 3) {
			procurador.open("3\\produtoBDS.txt", ios::in);
		}
		else {
			menuInicial();
		}
		do {
			// PEGA PRODUTO;
			getline(procurador, codigoDoBds); // pega codigo
			if (codigoDoBds == codigoPedido) {
				achouSim = true;
				getline(procurador, codigoDoBds); // pega nome
				recebeNome = codigoDoBds;
				getline(procurador, codigoDoBds); // pega preco
				recebePreco = codigoDoBds;
				getline(procurador, codigoDoBds); // pega quantidade
				recebeQuantidade = codigoDoBds;
				recebeQuantidade.erase(0, 11);
			};
		} while (procurador.eof() == NULL);
		procurador.close();
		if (!achouSim) {
			system("cls");
			gotoxy(0, 5);
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|               Codigo De Produto Invalido                 |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			Sleep(800);
			continue;
		}
		else if (stoi(recebeQuantidade) <= 0) {
			system("cls");
			gotoxy(0, 5);
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|                  Produto Sem Estoque!                    |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			Sleep(800);
			continue;
		};
		//TRANSFORMADOR
		recebeNome.erase(0, 6); // apaga nome: //
		recebePreco.erase(0, 7); // apaga preco: //
		//REGISTRA NA SACOLA
		int verificaCopia = 0, verificaEstoque = 0;
		do {
			for (int ii = 0; ii <= cont; ii++) {
				if (sacola[ii].nome == recebeNome) {
					sacola[ii].quantidade += 1;
					if (sacola[ii].quantidade > stoi(recebeQuantidade)) { //verifica se acabou o estoque dentro da sacola
						sacola[ii].quantidade -= 1;
						system("cls");
						gotoxy(0, 5);
						cout << "+----------------------------------------------------------+" << endl;
						cout << "|                  Produto Sem Estoque!                    |" << endl;
						cout << "+----------------------------------------------------------+" << endl;
						Sleep(800);
						verificaEstoque = 1;
					};
					verificaCopia = 1;
					continue;
				};
			};
			if (verificaCopia == 1) {
				cont--;
				break;
			}
			else {
				sacola[cont].nome = recebeNome;
				double totTemp2 = 0.0;
				//convertendo valor digitado para float. 
				stringstream ss;
				string s = recebePreco;
				ss << s;
				ss >> totTemp2;
				sacola[cont].preco = totTemp2;
				sacola[cont].quantidade = 1;
				verificaCopia = 1;
			}
		} while (verificaCopia != 1);
		// SOMA SACOLA
		double totTemp2 = 0.0;
		//convertendo valor digitado para float. 
		stringstream ss;
		string s = recebePreco;
		ss << s;
		ss >> totTemp2;
		totalPedido += totTemp2;
		if (verificaEstoque == 1) {
			totalPedido -= totTemp2;
		};
		//chama mais 1 produto
		cont++;
	} while (kikatForVirgem == true);

	// FINALIZA PEDIDO
finaliza:
	bool imprimir = false;
	if (totalPedido == 0 || totalPedido < 0) {
		goto maisPedido;
	}
	do {
		string trocoPedido = "";
		int escolhaMenu = 0;
		bool enterApertado = false;
		int i = 0;
		system("cls");
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|      Recebe       || Hora: " << timeStr << "   ||    Sacola       |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		cout << "|                        Total: " << setw(10) << left << fixed << setprecision(2) << totalPedido << "                 |" << endl;
		cout << "|                        Pagar: " << setw(10) << left << fixed << setprecision(2) << trocoPedido << "                 |" << endl;
		cout << "+----------------------------------------------------------+" << endl;
		while (_kbhit || escolhaMenu == 63) {
			escolhaMenu = _getch();
			if (escolhaMenu == 0) {
				escolhaMenu = _getch();
				if (escolhaMenu != 0) {
					switch (escolhaMenu) {
					case 59: //f1
						menuInicial();
						break;
					case 60: //f2
						goto maisPedido;
						break;
					case 61: //f3
						goto finaliza;
						break;
					default:
						break;
					}
				};
			}
			else if (escolhaMenu == 13) {
				enterApertado = true;
				break;
			}
			else if (!enterApertado && (escolhaMenu >= 48) && (escolhaMenu <= 57) || (escolhaMenu == 46) || (escolhaMenu == 44)) {
				if (escolhaMenu == 44) {
					escolhaMenu = '.';
				};
				trocoPedido += escolhaMenu;
			}
			else if (escolhaMenu == 8) {
				i = trocoPedido.length();
				if (i <= 0) {
					continue;
				};
				i--;
				trocoPedido.erase(i);
			};
			system("cls");
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|  Pizzaria New York || Usuário: " <<setw(7) << left << usuarioAtivo << " || loja : " << NumeroLoja << "       |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|  F1-Menu inicial  ||     F2-Voltar    ||  F3-Atualizar   |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|      Recebe       || Hora: " << timeStr << "   ||    Sacola       |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|                        Total: " << setw(10) << left << fixed << setprecision(2) << totalPedido << "                 |" << endl;
			cout << "|                        Pagar: " << setw(10) << left << fixed << setprecision(2) << trocoPedido << "                 |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			if (enterApertado) {
				break;
			};
		};
		double totTemp2 = 0.0;
		//convertendo valor digitado para float. 
		stringstream ss;
		string s = trocoPedido;
		ss << s;
		ss >> totTemp2;
		
		if (totTemp2 < totalPedido) {
			float temp = totTemp2 - totalPedido;
			system("cls");
			gotoxy(0, 5);
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|                       Falta: "<<setw(7) << left<< fixed << setprecision(2)<< temp <<"                     |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			Sleep(800);
		}
		else {
			int op = 0;
			system("cls");
			cout << "                            _....._" << endl;
			cout << "                       _.:`.-- | --.`:._" << endl;
			cout << "                      .: .'\o  | o /'. '." << endl;
			cout << "                     // '.  \ o|  /  o '.\\\\" << endl;
			cout << "                    //'._o'. \ |o/ o_.-'o\\\\" << endl;
			cout << "                    || o '-.'.\|/.-' o   ||" << endl;
			cout << "                PEDIDO REALIZADO COM SUCESSO!!!" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "|                       Troco: " << setw(7) << left << fixed << setprecision(2) << totTemp2 - totalPedido << "                     |" << endl;
			cout << "+----------------------------------------------------------+" << endl;
			cout << "              Imprimir Cupom? <ENTER> ou <ESC>             " << endl;
			op = _getch();
			if (op == 13) {
				imprimir = true;
			}
			numeroPedido++;
			break;
		};
	} while (trocoPedido < totalPedido);
	

	//LANÇA PEDIDO NO BDS
	string arq;
	for (int i = 0; i < 9; i++) {
		if (dateStr[i] == '/') { //substitui mm/dd por mm.dd
			dateStr[i] = '.';
		}
	};
	arq += dateStr;
	arq += ".txt";
	if (NumeroLoja == 1) {
		arq = "1\\" + arq;
	}
	else if (NumeroLoja == 2) {
		arq = "2\\" + arq;
	}
	else if (NumeroLoja == 3) {
		arq = "3\\" + arq;
	}
	else {
		return menuInicial();
	}

	pedidodoispontos = timeStr[1];
	pedidodoispontos += timeStr[4];
	pedidodoispontos += timeStr[7];
	ofstream gravador;
	gravador.open(arq, ios::app);
	gravador << " " << timeStr << " | " << "PEDIDO " << pedidodoispontos << "          |$" << totalPedido << endl;
	gravador.close();
	//ATUALIZA QUANTIDADE
	string recebeTudo;
	ifstream procurador;
	ofstream transfereBDS;
	
	if (NumeroLoja == 1) {
		transfereBDS.open("1\\transfereBDS.txt");
		procurador.open("1\\produtoBDS.txt");
	}
	else if (NumeroLoja == 2) {
		transfereBDS.open("2\\transfereBDS.txt");
		procurador.open("2\\produtoBDS.txt");
	}
	else if (NumeroLoja == 3) {
		transfereBDS.open("3\\transfereBDS.txt");
		procurador.open("3\\produtoBDS.txt");
	}
	else {
		menuInicial();
	}
	int i = 0;
	do {
		getline(procurador, recebeTudo);
		if (recebeTudo == "\n")
		{
			continue;
		}
		if (recebeTudo == "nome: " + sacola[i].nome) {
			int dezena = 0, centena = 0, unidade = 0, realQuantidade = 0;
			transfereBDS << recebeTudo << endl; //coloca nome com nome: //
			getline(procurador, recebeTudo);
			transfereBDS << recebeTudo << endl; // coloca preco
			getline(procurador, recebeTudo); // pega quantidade
			
			recebeTudo.erase(0, 11);
			realQuantidade = stoi(recebeTudo); //transforma sting em int

			novoEstoque = realQuantidade - sacola[i].quantidade;
			transfereBDS << "quantidade: " << novoEstoque << endl;
			getline(procurador, recebeTudo); //CONTINUE;	
			i++;
		};
		transfereBDS << recebeTudo << endl; // coloca todo resto que nao seja o produto selecionado
	} while(procurador.eof() == NULL);
	transfereBDS.close();
	procurador.close();
	if (NumeroLoja == 1) {
		remove("1\\produtoBDS.txt");
		rename("1\\transfereBDS.txt", "1\\produtoBDS.txt");
	}
	else if (NumeroLoja == 2) {
		remove("2\\produtoBDS.txt");
		rename("2\\transfereBDS.txt", "2\\produtoBDS.txt");
	}
	else if (NumeroLoja == 3) {
		remove("3\\produtoBDS.txt");
		rename("3\\transfereBDS.txt", "3\\produtoBDS.txt");
	}
	else {
		menuInicial();
	};
	
	// LANÇA RELATORIO	
	if (NumeroLoja == 1) {
		gravador.open("1\\registroVendas.txt", ios::app);
	}
	else if (NumeroLoja == 2) {
		gravador.open("2\\registroVendas.txt", ios::app);
	}
	else if (NumeroLoja == 3) {
		gravador.open("3\\registroVendas.txt", ios::app);
	}
	else {
		menuInicial();
	}
	gravador << "pedido: " << pedidodoispontos << endl;
	gravador << "data: " << dateStr << endl;
	gravador << "hora: " << timeStr << endl;
	for (int i = 0; i < cont; i++) {
		gravador << "produto: " << sacola[i].nome << endl;
		gravador << "quantidade: " << sacola[i].quantidade << endl;
		gravador << "preco: " << sacola[i].preco << endl;
		gravador << "total produto: " << sacola[i].preco * sacola[i].quantidade << endl;	
	};
	gravador << "-----------------" << endl;
	gravador << "total pedido: " << totalPedido << endl;
	gravador.close();
	if (imprimir) {
		remove("impressao.txt");
		ofstream imprimi;
		imprimi.open("impressao.txt");
		imprimi << "            ~~~~~~~~ New York Pizza ~~~~~~~~" << endl << endl;
		imprimi << "                       Pedido: " << pedidodoispontos << endl;
		imprimi << "           Data: " << dateStr << "    Hora: " << timeStr << endl << endl;
		for (int i = 0; i < cont; i++) {
			imprimi << "                  produto: " << sacola[i].nome << endl;
			imprimi << "                  quantidade: " << sacola[i].quantidade << endl;
			imprimi << "                  preco: " << sacola[i].preco << endl;
			imprimi << "                  total produto: " << sacola[i].preco * sacola[i].quantidade << endl << endl;
		};
		imprimi << "                       TOTAL: " << totalPedido << endl;
		imprimi.close();
		system("notepad /p impressao.txt");
	};
	return balcaoSacola();
};
//[5] Troca de usuario
void trocaUsuario() {
	usuarioAtivo = "";
	nivelLoja = 0;
	NumeroLoja = 0;
	main();
}
//subfuncao 1
int intLength(int i) {
	int l = 0;
	if (i == 0) {
		return 1;
	}
	else if (i < 0) {
		l++;
	}
	for (; i; i /= 10) l++;
	return l == 0 ? 1 : l;
}
//sub funcao 2
void gotoxy(int x, int y)
{
	HANDLE variavel = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(variavel, position);
}