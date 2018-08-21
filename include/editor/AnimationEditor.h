//
// Created by Jie on 2018/8/10.
//

#ifndef UNTITLED_ANIMATIONEDITOR_H
#define UNTITLED_ANIMATIONEDITOR_H

#include "Object.h"
#include "Sprite.h"

class AnimationEditor : public Object {
public:
    AnimationEditor();
    ~AnimationEditor();

    void Draw(const char *title, bool *p_open,float dt);

private:
    bool isShow;
    int selected = 0;
    int lastSelected = -1;
    Sprite* sprite;
    std::vector<std::string> fileList;

    int animaSelected = 0;
    int lastAnimaSelected = -1;
    std::vector<std::string> animaList;

    void OnSelectChange();
    void OnAnimationChange();
};

#endif //UNTITLED_ANIMATIONEDITOR_H
