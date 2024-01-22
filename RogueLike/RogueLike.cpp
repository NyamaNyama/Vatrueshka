#include <curses.h>
// maxy = 30 maxx =120
int main() {
    initscr(); // Инициализация экрана
    noecho(); // Отключение отображения вводимых символов
    curs_set(0); // Скрытие курсора
    timeout(0); // Неблокирующий режим ввода

    int x = 0;
    int y = LINES / 2; // Положение по вертикали

    while (true) {
        clear(); // Очистка экрана
        mvaddch(y, x, 'X'); // Помещение символа 'X' в позицию (x, y)
       
        switch (getch()) {
            case KEY_UP:
                y--;
                break;
            case 's':
                y++;
                break;
            case 'a':
                x--;
                break;
            case 'd':
                x++;
                break;
        }
        
        refresh();
    }

    endwin();
	return 0;
}