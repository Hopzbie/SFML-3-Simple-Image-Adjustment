// library
#include <SFML/Graphics.hpp>
#include <cmath>

// main program
int main()
{
    // create window
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Title");

    // load image
    sf::Image image("Images/Girl.png");
    unsigned int image_w = image.getSize().x;
    unsigned int image_h = image.getSize().y;

    // image editing
    for (unsigned int y = 0;  y < image_h;  y++)
    {
        for (unsigned int x = 0;  x < image_w;  x++)
        {
            // get color of pixel
            sf::Color color = image.getPixel({x, y});

            // RGB (0-1)
            float r = static_cast<float>(color.r) / 255;
            float g = static_cast<float>(color.g) / 255;
            float b = static_cast<float>(color.b) / 255;

            // grayscale
            float l = 0.2f*r + 0.7f*g + 0.1f*b;

            // exposure, contrast, brightness, saturation, level
            float exposure   =  0.5f;
            float contrast   = -0.2f;
            float brightness = -0.1f;
            float saturation =  0.4f;
            float level_1    = -0.1f;
            float level_2    =  1.1f;
            exposure    = std::pow(2, exposure);
            contrast   += 1;
            saturation += 1;
            level_2    -= level_1;
            r = ((l + (r - l)*saturation)*exposure*contrast + brightness - level_1) / level_2;
            g = ((l + (g - l)*saturation)*exposure*contrast + brightness - level_1) / level_2;
            b = ((l + (b - l)*saturation)*exposure*contrast + brightness - level_1) / level_2;

            // clamp to 0-1
            r = (r < 0.f) ? 0.f : ((r > 1.f) ? 1.f : r);
            g = (g < 0.f) ? 0.f : ((g > 1.f) ? 1.f : g);
            b = (b < 0.f) ? 0.f : ((b > 1.f) ? 1.f : b);

            // update color
            color.r = r * 255;
            color.g = g * 255;
            color.b = b * 255;

            // set color of pixel
            image.setPixel({x, y}, color);
        }
    }

    // save image to file
    // bool success = image.saveToFile("Images/Girl 2.png");

    // create texture from image
    sf::Texture texture(image);
    texture.setSmooth(true);

    // create sprite from texture
    sf::Sprite sprite(texture);
    float scale = static_cast<float>(window.getSize().x) / image_w;
    sprite.setScale({scale, scale});

    // window loop
    while (window.isOpen())
    {
        // handle events
        while (auto event = window.pollEvent())
        {
            // on close button release
            if (event->is<sf::Event::Closed>())
            {
                // close window
                window.close();
            }

            // when window is resized
            else if (event->is<sf::Event::Resized>())
            {
                // update view
                window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
            }
        }

        // fill background color
        window.clear(sf::Color(64, 64, 64));

        // draw sprite
        window.draw(sprite);
        
        // display
        window.display();
    }

    // program end successfully
    return 0;
}