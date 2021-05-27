#include "game.h"




int x=10, y=10;
int direction;
int game_state = BEFORE_START;
int score;
int lives;
bool snake_displayed =false;

void start_game()
{
    init_snake();
    init_food();
    score =0;
    lives = INITIAL_LIVES;
    direction = UP;
    game_state = STARTED;

}


void end_game()
{
    game_state = ENDED;
}

void paint_status()
{
    move(0,5);
    attron(A_BOLD);
    printw("SCORE %d", score);// string formatting w -> window
    attroff(A_BOLD);
    move(0,COLS - 10);
    for(int i=0; i<lives; i++)
    {
        attron(COLOR_PAIR(4));
        attron(A_BOLD);
        addstr("O");
        attroff(COLOR_PAIR(4));
        attroff(A_BOLD);
    }
    
    if(game_state== BEFORE_START)
    {
        move(LINES-1,5);
        attron(A_BOLD);
        addstr("press sPaCe kEy tO start");
        attroff(A_BOLD);

    }else if(game_state == STARTED)
    {

    }
    else if(game_state == SNAKE_RESET)
    {
        move(LINES - 1, 5);
        attron(A_BOLD);
        addstr("yOu lOsT a lIfE and press space key to continue");
        attroff(A_BOLD);

    }
    else
    {
        move(LINES - 1,5);
        attron(A_BOLD);
        addstr("press sPaCe to rEsTaRt and Q tO qUiT");
        attroff(A_BOLD);

    }

}

bool execute_frame()
{
    paint_border();
    paint_status();
    char key = getch(); //because of getch aroows, escape keys are ignored
    if(game_state == BEFORE_START)
    {
       
        if(key == 32)
        {
            start_game();
        }
    }
    else if(game_state == STARTED)
    {
        if(key == UP && direction != DOWN)
        {
            direction = UP;
        } else if(key == DOWN && direction != UP)
        {
            direction = DOWN;
        } else if(key == LEFT && direction != RIGHT)
        {
            direction = LEFT;
        } else if(key == RIGHT && direction != LEFT)
        {
            direction = RIGHT;
        }
        // if any key has to presseed it should react if not also

        pair<int, int> head=move_snake(direction);
        if(try_consume_food(head))
        {
            grow_snake();
            score++;
        }
        if(has_collision())
        {
            
            lives=lives-1;
            reset_snake();
            
            game_state= SNAKE_RESET;

            if(lives==-1)
            {
                end_game();
            }
            
        }
        paint_snake();
        paint_food(); 

    }   else if(game_state == SNAKE_RESET)
        {
            
            if(key == 32)
            {
                game_state = STARTED;
            }
            if(snake_displayed)
            {
                paint_snake();
            }
            snake_displayed = !snake_displayed;
            paint_food();
        }   

        else 
        {
            paint_snake();
            paint_food();
            

            if(key==32)
            {
                start_game();
            }
            if(key== QUIT)
            {
                return true;

            }


        }  
    
    
     
    return false;

}




