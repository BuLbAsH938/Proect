#include "Settings.h" 
using namespace sf;

int main()
{
    // Объект, который, собственно, является главным окном приложения 


    RenderWindow window(VideoMode(WINDOW_X, WINDOW_Y), WINDOW_NAME);
    window.setFramerateLimit(FPS);
    srand(time(nullptr));
    CircleShape c; //мяч 
    RectangleShape r; //ракетки 
    float ball_speedx = 2.f;
    float ball_speedy = 3.f;

    // счетчик
    int BestScore = 0;
    int ScoreInt = 0;
    int menu = 1;
    int PlayMenu = 1;
    int ExitMenu = 0;
    // тексты
    Font font;
    font.loadFromFile("DS-DIGIB.ttf");
    
    Text ScoreText(std::to_string(ScoreInt), font, 64);
    ScoreText.setPosition(WINDOW_X / 2, 10);

    Text PlayText(Play, font, TextSize);
    PlayText.setPosition(WINDOW_X / 2 - TextSize, WINDOW_Y / 2 - TextSize2*2);
    PlayText.setFillColor(Color::Green);
   
    Text ExitText(Exit, font, TextSize2);
    ExitText.setPosition(WINDOW_X / 2 - TextSize2, WINDOW_Y - TextSize*2 );
    
    Text BestScoreText(BestScoreString+std::to_string(BestScore), font, TextSize3);
    BestScoreText.setPosition(WINDOW_X - TextSize * 2, 1);

    //установка цвета 
    r.setFillColor(Color{
       (Uint8)(rand() % 256), (Uint8)(rand() % 256), (Uint8)(rand() % 256) });
    c.setFillColor(Color{
     (Uint8)(rand() % 256), (Uint8)(rand() % 256), (Uint8)(rand() % 256) });
    
    //установка позиции 
    r.setPosition((WINDOW_X / 2) - (BAT_WIDHT / 2), WINDOW_Y - BAT_HEIGHT - 5);
    c.setPosition((WINDOW_X - 2 * radius) / 2, (WINDOW_Y - 2 * radius) / 2);
    //установка размера 
    r.setSize(Vector2f(BAT_WIDHT, BAT_HEIGHT));
    c.setRadius(radius);
    // Главный цикл приложения. Выполняется, пока открыто окно 

    while (window.isOpen())
    {
        
        // Обрабатываем очередь событий в цикле 
        Event event;
        while (window.pollEvent(event))
        {
            // Пользователь нажал на «крестик» и хочет закрыть окно? 
            if (event.type == Event::Closed)
                // тогда закрываем его 
                window.close();
        }
        // обновление объектов игры 
        
        //меню
        while (menu == 1) {
            window.clear();
            window.draw(PlayText);
            window.draw(ExitText);
            window.draw(BestScoreText);
            
            window.display();
            if (Keyboard::isKeyPressed(Keyboard::H) ) {
                menu++;
            }
            if (Keyboard::isKeyPressed(Keyboard::W) && ExitMenu == 1) {
                ExitMenu = ExitMenu - 1;
                PlayMenu = PlayMenu + 1;
                PlayText.setFillColor(Color::Green);
                ExitText.setFillColor(Color::White);
            }
            if (Keyboard::isKeyPressed(Keyboard::S) && PlayMenu == 1) {
                ExitMenu = ExitMenu + 1;
                PlayMenu = PlayMenu - 1;
                PlayText.setFillColor(Color::White);
                ExitText.setFillColor(Color::Green);
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter) && PlayMenu == 1) {
                menu--;
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter) && ExitMenu == 1) {
                window.close();
            }
            
        }

        c.move(ball_speedx, ball_speedy);
        if (c.getPosition().x <= 0 || c.getPosition().x + 2 * radius >= WINDOW_X) {
            ball_speedx = -ball_speedx;
        }
        if (c.getPosition().y <= 0 || c.getPosition().y + 2 * radius >= WINDOW_Y) {
            ball_speedy = -ball_speedy;

        }
        if (c.getPosition().y + 2 * radius >= WINDOW_Y) {
            menu++;
            c.setPosition((WINDOW_X - 2 * radius) / 2, (WINDOW_Y - 2 * radius) / 2);
            if (BestScore < ScoreInt) {
                BestScore = ScoreInt;
                BestScoreText.setString(BestScoreString + std::to_string(BestScore));
            }
            ScoreInt = 0;
            ScoreText.setString(std::to_string(ScoreInt));
        }
        
        if (Keyboard::isKeyPressed(Keyboard::A) && r.getPosition().x >= 0) {
            r.move(-d2, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::D) && r.getPosition().x + BAT_WIDHT <= WINDOW_X ) {
            r.move(d2, 0);
        }
        //отскок
        float ballX = c.getPosition().x;
        float ballY = c.getPosition().y;
        Vector2f midTop{ ballX + radius, ballY };
        Vector2f midLeft{ ballX , ballY + radius };
        Vector2f midBottom{ ballX + radius, ballY + 2 * radius };
        float midLeftX = c.getPosition().x;
        float midLeftY = c.getPosition().y + radius;
        if (pointInRect(r, midLeft)) ball_speedx = -ball_speedx;
        if (pointInRect(r, midBottom) || pointInRect(r, midTop)) {
            ball_speedy = -ball_speedy;
            ScoreInt++;
            ScoreText.setString(std::to_string(ScoreInt));
        }
            
       
        
        
          // Отрисовка окна  


        window.clear();
        window.draw(ScoreText);
        window.draw(r);
        window.draw(c);
        window.display();
    }


    //отрисовка объектов и окна 

    return 0;
}