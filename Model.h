#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

class Model{
public:
    Image model_image;
    Texture model_texture;
    Sprite model_sprite;
Model(string File){
    model_image.loadFromFile("images/" + File);
    model_image.createMaskFromColor(Color(0, 0, 0));
    model_texture.loadFromImage(model_image);
    model_sprite.setTexture(model_texture);
}
/*void Draw_sprite(){
    sf::RenderWindow window;
    window.draw(model_sprite);
    window.display();
}*/
};
#endif
