#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <clocale>

using namespace std;
void instrucciones();
void showboard(const vector<char>& board);
void SumaMatriz();
void TicTacToc();
char Askpar_impar(string question);
char humansymbol();
char opponent(char player);
char winner(vector<char> board);
int PlayerMove(const vector<char>& board);
int askNumber(string question, int high, int low);
bool isLegal(int move, const vector<char>& board);

const char EMPTY = ' '; //Constante global para determinar el valor en los espacios que en este caso es vacio
const char  X = 'X';
const char  O = 'O';
const char NO_ONE = 'N';
const char TIE = 'T';

int main()

{
	char parte;
	do {
		system("cls");
		cout << "bienvenido, elige un apartado porfavor:\n TicTacToc:t \n suma de matrices:s" << endl;
		cin >> parte;
	} while (parte != 't' && parte != 's');

	switch (parte)
	{
	case 't':
		TicTacToc();
		break;
	case 's':
		SumaMatriz();
		break;
	}
}



void instrucciones()

{

	cout << "\nBienvenido: \n";
	cout << "\nElige una posicion entre el 0 y el 8.\n\n";
	cout << "|0|1|2|\n";
	cout << "|3|4|5|\n";
	cout << "|6|7|8|\n";

	cout << "\nQue comience la batalla!\n";
}


char Askpar_impar(string question)
{

	char answer;

	do
	{
		cout << "\n" << question << "(p/i)";
		cin >> answer;

	} while (answer != 'p' && answer != 'i');

	return answer;



}

char humansymbol() //esta funcion es para usar el Yes o No de arriba y asignar OTRO resultado que en este caso son nuestras contsantes globales
{

	char gofirst = Askpar_impar("Deseas ser par o impar?");
	srand(time(NULL));

	int dado = rand() % 6 + 1;
	if (gofirst == 'p')
	{
		cout << dado << endl;
		if (dado % 2 == 0)
		{
			cout << "jugador es X y AI es O" << endl;
			return X;
		}
		else {
			cout << "jugador es O y AI es X" << endl;
			return O;
		}
	}
	else if(gofirst == 'i')
	{
		cout << dado << endl;
		if (dado % 2 == 0)
		{
			cout << "jugador es O y AI es X" << endl;
			return O;
		}
		else {
			cout << "jugador es X y AI es O" << endl;
			return X;
		}		
	}
}

char opponent(char player)
{

	if (player == X)

	{
		return O;

	}

	else
	{
		return X;
	}
}


char winner(vector<char> board)
{
	//Son todas las posibilidades para ganar
	const int WINNING_POS[8][3] = { {0, 1, 2},
									{3, 4, 5},
									{6, 7, 8},
									{0, 3, 6},
									{1, 4, 7},
									{2, 5, 8},
									{2, 4, 6},
									{0, 4, 8}, };

	const int TOTAL_ROWS = 8;

	//Para regresar al ganador.

	for (int row = 0; row < TOTAL_ROWS; row++)
	{

		if ((board[WINNING_POS[row][0]] != EMPTY) && //Para que el espacio no este vacio
			(board[WINNING_POS[row][0]] == board[WINNING_POS[row][1]]) && // [row] es la fila y [] es el numero de la columna
			(board[WINNING_POS[row][1]] == board[WINNING_POS[row][2]])) // [row] es la fila y [] es el numero de la columna
		{
			return board[WINNING_POS[row][0]];

		}
	}



	if (count(board.begin(), board.end(), EMPTY) == 0) //el count es una funcion que se reinicia
	{
		return TIE;
	}

	//regresar que nadie ha ganado todavia

	return NO_ONE;

}

int PlayerMove(const vector<char>& board)
{
	int num;
	do {
		num = askNumber("Elige un espacio", 8, 0);
		isLegal(num, board);
		if (!isLegal(num, board))
		{
			cout << "casilla ya usada, escoge otra" << endl;
		}
	} while (!isLegal(num, board));
	return num;
}

int askNumber(string question, int high, int low)
{
	string input;
	bool isValid = false;
	bool isRangeValid = false;
	int number = 0;

	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	do {
		cout << question << "entre " << low << " y " << high << endl;

		getline(cin, input);

		for (char c : input)
		{
			if (!isdigit(c))
			{
				isValid = false;
				break;
			}
			else
			{
				isValid = true;
				break;
			}
		}

		if (!isValid)
		{
			cout << "\nEntrada inválida, por favor elige solo números.\n";
		}
		else
		{
			number = stoi(input);
			isRangeValid = number <= high && number >= low;
		}

		if (!isRangeValid && isValid)
		{
			cout << "\nEntrada inválida, elige un número dentro del rango establecido.\n";
		}

	} while (!isValid || input.empty() || !isRangeValid);

	return number;
}


bool isLegal(int move, const vector<char>& board)
{
	return board[move] == EMPTY;

}

void showboard(const vector<char>& board)
{
	cout << board[0] << board[1] << board[2] << endl;
	cout << board[3] << board[4] << board[5] << endl;
	cout << board[6] << board[7] << board[8] << endl;
}

void SumaMatriz()
{
	int total = 0;
	int resultpar = 0;
	int resultindic = 0;
	cout << "vamos con la suma" << endl;
	const int  matrizsum[3][4] = { {2, 3, 1, 4}
		                          ,{9, 8, 7, 9}
		                          ,{3, 2, 1, 5}
	};
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << matrizsum[i][j];
		}
		cout << "\n";
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((matrizsum[i][j] % 2) == 0)
			{
				cout << "los siguientes numeros " << matrizsum[i][j] << " son par" << endl;
				resultpar += matrizsum[i][j];
				cout << "su indice son  " << i << j <<endl;
				resultindic += ((i * 10) + j);
			}
		}		
	}
	cout << "el resultado de todos los par es " << resultpar << endl;
	cout << "el resultado de los indices es " << resultindic << endl;
	total = resultpar - resultindic;
	cout << "la resta del indice con la suma de los par es " << total << endl;
}

void TicTacToc()
{
	setlocale(LC_ALL, "spanish");
	char validation;
	char player = humansymbol(); //Para que tome el valor de la funcion que creamos abajo en caso de querer comenzar primero
	char computer = opponent(player); //Para que tome el valor contrario que elija el jugador usando la funcion de opponent
	char turn = X; //porque es mas natural que el juego inicie con la X. Toma su valor de la constante global


	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);


	instrucciones();



	while (winner(board) == NO_ONE)
	{
		int moved = PlayerMove(board);
		board[moved] = player;
		showboard(board);
	}
}