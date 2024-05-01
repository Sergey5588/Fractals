#include <SFML/Graphics.hpp>
#include <ccomplex>
#include <iostream>
#include <string>
#include <Windows.h>
#include <atlstr.h>
#include <random>





using namespace sf;

std::complex<double> mandelbrot(std::complex<double> z, std::complex<double> c)
{
    
    std::complex<double> z1(0, 0);
    z1 = z * z + c;



    return z1;
}


int IsM(std::complex<double> c, int mx)
{
    std::complex<double> z(0, 0);

    for (std::int16_t i = 0; i < mx; i++)
    {
        z = mandelbrot(z, c);

        if (abs(z) >= 2)
        {
            return (int)(i * 255 / mx);
        }
    }

    return 255;
}

int IsJ(std::complex<double> z, int mx, std::complex<double> c)
{
    std::complex<double> f(-0.7514f, -0.826f);
    //std::complex<double> z(0, 0);

    for (std::int16_t i = 0; i < mx; i++)
    {
        z = mandelbrot(z, c);

        if (abs(z) >= 2)
        {
            return (int)(i * 255 / mx);
        }
    }

    return 255;
}

void update(int WIDTH, int HEIGHT, double ofX, double ofY, RenderWindow& window, RectangleShape shape, double scale, int maxIt, int Fnum, std::complex<double> cForJ)
{

    window.clear();
    
    for (double i = 0; i <= WIDTH; i++)
    {
        for (double j = 0; j <= HEIGHT; j++)
        {
            double x = (i - WIDTH / 2 + ofX) * scale;
            double y = (j - HEIGHT / 2 + ofY) * scale;

            y = -y;
            if (Fnum==0)
            {
                Uint8 clr = IsM(std::complex<double>(x, y), maxIt);
                auto color = sf::Color{ clr, clr, clr };
                shape.setFillColor(color);
                shape.setPosition(i, j);
                window.draw(shape);
            }
            else if(Fnum == 1)
            {
                Uint8 clr = IsJ(std::complex<double>(x, y), maxIt, cForJ);
                auto color = sf::Color{ clr, clr, clr };
                shape.setFillColor(color);
                shape.setPosition(i, j);
                window.draw(shape);
            }


            
            /*if (IsM(std::complex<double>(x, y), 100))
            {
                shape.setPosition(i, j);
                window.draw(shape);
            }*/
        }
    }


    window.display();
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int MaxIt = 50;
    bool start = true;
    int m = 0;
    
    std::complex<double> cForJ(-0.64, 0.39);
    if (start)
    {
        std::cout << "Генератор фракталов\n";
        std::cout << "Максимум итераций (меньше - лучше производительность, но хуже точность и ярче градиент): ";
        std::cin >> MaxIt;
        std::cout << "Доступные фракталы:\n";
        std::cout << "Множество Мондельброта: 0\n";
        std::cout << "Множество Жюлиа: 1\n";
        std::cout << "Выберите множество: ";
        std::cin >> m;
        std::cout << "Управление\nСтрелочки: перемещение\nЛевый Shift: увеличение\nЛевый Alt: уменьшение\nU: обновить экран\n";
        std::cout << "Программа сделана в рамках проектной деятельности\nШкола №1580, 2024 г.";
        
        
    }
    std::complex<double> z(0, 0);
    std::int32_t WIDTH = 200;
    std::int32_t HEIGHT = 200;
    double Y=0;
    double X=0;

    double ofX = 0;
    double ofY = 0;
    double scale = 0.01f;
    RenderWindow window(VideoMode(WIDTH, HEIGHT), L"Фрактал", Style::Default);
    RenderWindow test(VideoMode(WIDTH, HEIGHT), L"Выбор точки", Style::Titlebar);
    
    Vector2i pos = window.getPosition();
    pos.x += WIDTH;

    test.setPosition(pos);
    
    if (m!=1) 
    {
        test.close();             
    }
    

    window.setVerticalSyncEnabled(true);
    

    CircleShape sh;
    sh.setScale({ 1.f,1.f });
    sh.setRadius(0.5f);
    sh.setFillColor(Color::Black);
    
    for (double i = 0; i <= WIDTH; i++)
    {
        for (double j = 0; j <= HEIGHT; j++)
        {
            double x = (i - WIDTH / 2)/50;
            double y = (j - HEIGHT / 2)/50;

            y = -y;
            
            Uint8 c = IsM(std::complex<double>(x,y),MaxIt)/2;
            auto GREY = Color{c, c, c };
            sh.setFillColor(GREY);
            sh.setPosition(i, j);
            test.draw(sh);
            sh.setFillColor(Color::Black);
            if (i == WIDTH/2 || j == HEIGHT/2)
            {
                sh.setFillColor(Color::White);
                sh.setPosition(i, j);
                test.draw(sh);
                
            }

        }
    }
    test.display();


    RectangleShape shape;
    shape.setSize({ 1.f, 1.f });
    shape.setFillColor(Color::White);

    


    update(WIDTH, HEIGHT, ofX, ofY, window, shape, scale, MaxIt, m, cForJ);
    while (window.isOpen())
    {
        if (window.hasFocus())
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                ofX -= 50;
                update(WIDTH, HEIGHT, ofX, ofY, window, shape, scale, MaxIt, m, cForJ);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                ofX += 50;
                update(WIDTH, HEIGHT, ofX, ofY, window, shape, scale, MaxIt, m, cForJ);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                ofY -= 50;
                update(WIDTH, HEIGHT, ofX, ofY, window, shape, scale, MaxIt, m, cForJ);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                ofY += 50;
                update(WIDTH, HEIGHT, ofX, ofY, window, shape, scale, MaxIt, m, cForJ);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                
                scale *= 0.95;
                ofX /= 0.95;
                ofY /= 0.95;

                update(WIDTH, HEIGHT, ofX, ofY, window, shape, scale, MaxIt, m, cForJ);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
            {
                scale /= 0.95;
                ofX *= 0.95;
                ofY *= 0.95;
                update(WIDTH, HEIGHT, ofX, ofY, window, shape, scale, MaxIt, m, cForJ);
            }
           
        }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
            {
                cForJ = std::complex<double>(X, Y);
                update(WIDTH, HEIGHT, ofX, ofY, window, shape, scale, MaxIt, m, cForJ);
            }
        
        Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::Resized)
            {
                sf::FloatRect Area(0, 0, event.size.width, event.size.height);
                WIDTH = event.size.width;
                HEIGHT = event.size.height;
                window.setView(sf::View(Area));
                update(WIDTH, HEIGHT, ofX, ofY, window, shape, scale, MaxIt, m, cForJ);

            }

            
            
        }

        Event event1;

        
        while (test.pollEvent(event1))
        {
            if (event1.type == Event::MouseMoved)
            {
                
                X = event1.mouseMove.x;
                Y = event1.mouseMove.y;

                X = X - WIDTH / 2;
                Y = Y - HEIGHT / 2;
                Y = -Y;
                X = X / 50;
                Y = Y / 50;
                

                
                
                
                
                
            }

            
        }

        



        //shape.setPosition(0.f, 0.f);
        //window.draw(shape);
        //shape.setPosition(0.f, 1.f);
        //window.draw(shape);



    }
    return 0;
}


