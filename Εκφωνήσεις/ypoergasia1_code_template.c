/*
 * E������ 4.1 
 */
 
 
/* ��� ����� �� ���������� ������ ������������ */

const int DIMX = 20;
const int DIMY = 10;
float EnterTemperature(const char prompt[51]);
void InitializeTable(float T[DIMY][DIMX]);
void PrintTable(float T[DIMY][DIMX]);
float CalculateNextTemperature(float T[DIMY][DIMX], float C[DIMY][DIMX]);

/* ��� ����� �������� ���������� ����������� (AN ������� ����������) */

/* ����� ��������� ����������� ��������� ������������ */

int main() 
{
    /* ����������� ��� ������ Plate ���� ����� ������������ � �����������
    �� ���������� ������� */
    
    float Plate[DIMY][DIMX];
    int time;   /* ��������� ��� ���������� ������ ��������� */

	/* BA��� ��� ��� ������ ��� ��� ������ ���������� ���������� */
	
    /* �������� ��������� ���������� */
    system("chcp 1253>nul");
	time = 0;
    InitializeTable(Plate); /* A����������� ������ Plate */
    
    /* BA��� ��� ��� ������ ��� ��� ������������ �������� ��� ������ Plate 
	���� ������� ��� ���������� CalculateNextTemperature ��� PrintTable  */

    printf("O ������ ��� �� ������ � ����� �� ������ ��������� �����: %d ������������\n",time);
    return 0;
    
}

/* ��� ������ ���������� ����������� (AN ������� ����������) */


float EnterTemperature(const char prompt[51])
{
	/* �������� ������������ ��� ��� ������ �� ������ ��������� ���� ������ �� prompt */
	
	  /* ����� ��� ��� ������ ���*/
	
}

void InitializeTable(float T[DIMY][DIMX])
{
	/*  ������ ������� ������������ ��� ��� ������ ��� ������������ ������ */
	
	  /* ����� ��� ��� ������ ���*/
	
}

void PrintTable(float T[DIMY][DIMX])
{
	/* �������� ������ */
	
	  /* ����� ��� ��� ������ ���*/
}


float CalculateNextTemperature(float T[DIMY][DIMX], float C[DIMY][DIMX])
{
	/* ����������� ������������ �� ������� ������ t �� ���� �� ������� ������ t-1 */
	
	  /* ����� ��� ��� ������ ��� */
}
