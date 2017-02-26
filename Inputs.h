//
// Created by arnito on 26/02/17.
//

#ifndef VJ_PRINSE_OF_PERSIA_INPUTS_H
#define VJ_PRINSE_OF_PERSIA_INPUTS_H


#include <vector>
class Inputs
{
public:
    Inputs();
    virtual ~Inputs();

    virtual void Update();
    void UpdateWheel(int delta);
    sf::Vector2i getKey(std::string s);

protected:

    float col_right_dist;

private:
    void UpdateKey(bool pressed, std::string key);
    std::map<std::string, sf::Vector2i> keys;
    int wheelDelta;
};


#endif //VJ_PRINSE_OF_PERSIA_INPUTS_H
