#define UNICODE
//constant difinitions
//#define BLACK 30;
enum COLORS{BLACK=30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
#define bg(c) (c+10) //macro difinition
//function difinition
void barChart(int []);
void clearScreen(void);
void setColors(short, short);
void resetColors(void);
