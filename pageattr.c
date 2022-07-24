#include <ncurses.h>

#include <stddef.h>
#include <stdint.h>

void drawAddressView(WINDOW* window, uint64_t address)
{
    uint64_t index4, index3, index2, index1;

    uint64_t vaddr = address;

    vaddr >>= 12;
    index1 = vaddr & 0x1FF;
    vaddr >>= 9;
    index2 = vaddr & 0x1FF;
    vaddr >>= 9;
    index3 = vaddr & 0x1FF;
    vaddr >>= 9;
    index4 = vaddr & 0x1FF;

    wclear(window);
    box(window, 0, 0);
    mvwprintw(window, 0, 1, "Address");
    mvwprintw(window, 1, 1, "Address: %p", address);
    mvwprintw(window, 2, 1, "PML Index:   %d", index4);
    mvwprintw(window, 3, 1, "PDPTE Index: %d", index3);
    mvwprintw(window, 4, 1, "PDE Index:   %d", index2);
    mvwprintw(window, 5, 1, "PTE Index:   %d", index1);

    wrefresh(window);
}


int main(int argc, char** argv)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW* AddressView = newwin(10, 40, yMax - 15, 1);
    WINDOW* UserInterface = newwin(15, 30, 45, 1);

    uint64_t address = 0;

    while(1)
    {
                
        
        //Draw Windows
        drawAddressView(AddressView, address);


        int input = getch();
        switch(input)
        {
            case 'q':
                goto exit;
            case 'Q':
                goto exit;
            case KEY_IC:
                address += 0x40000000;
                break;
            case KEY_DC:
                address -= 0x40000000;
                break;
            case KEY_PPAGE:
                address += 0x200000;
                break;
            case KEY_NPAGE:
                address -= 0x200000;
                break;
            case KEY_UP:            //go up page
                address+=0x1000;
                break;
            case KEY_DOWN:          //go down page
                address-=0x1000;
                break;
            default:
                break;
        }

    }   

    exit:
    endwin();
    return 0;
}